#include "servidor.h"

void *AtenderCliente (void *args_void){
	
	// Antes de tudo deve selecionar o head em um no aqui
	struct thread_args * args = args_void;
	hnode * lista = args->lista;
	
	int suser = args->a;
	int i;// laco vetor sockets
	int * vetsockets; // ponteiro vetor sockets
	//node ** lista = args->lista;
	show_list(lista);

	char peticion[512], respuesta[512];
	int ret, logado=0, terminar=0, situacao=0, alterlista = 0;
	int codigo;
	char nombre[MAXNOME];
	char *p;
	MYSQL *conn;
	conn=mysql_init(NULL);
	char senha[MAXNOME];
	
	if(conn==NULL){
		printf("Error ao criar conexao: %u %s\n",mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	
	conn=mysql_real_connect(conn,SERVIDORDADOS,USUARIO,SENHA,BASE,0, NULL, 0);
	
	if(conn==NULL){
		printf("Erro ao iniciar conexao: %u%s\n",mysql_errno(conn),mysql_error(conn));
		exit(1);
	}
	
	while(terminar==0){
		
		// Ahora recibimos la peticion
		ret=read(suser, peticion, sizeof(peticion));
		
		// Tenemos que anadirle la marca de fin de string 
		// para que no escriba lo que hay despues en el buffer
		peticion[ret]='\0';
		
		p = strtok(peticion,"/");
		codigo = atoi(p);
		// Se estiver logado pega os dados do mesmo jeito ao desconectar
		if(codigo !=0){
			p = strtok(NULL,"/");
			strcpy(nombre, p);
			printf("Codigo: %d, Nome: %s\n", codigo, nombre);
		}
		
		if(codigo==0){ // Solicita sair
			
			printf("Solicitou desconectar (fechou form)");
			// Se esta logado desloga
			if(logado){
				p = strtok( NULL, "/");
				strcpy(nombre, p);
				remove_node(lista, search_node(lista,nombre));
				alterlista = 1; // Alteracao na lista
				show_list(lista);
				logado=0;
			}
			
			terminar=1;
			
		}else if(codigo==1){ // Solicita login servico login = 1/
			
			situacao=0;
			printf("Solicitou login");
			p = strtok( NULL, "/");
			strcpy(senha, p);
			
			
			//char * asenha = malloc((MD5_DIGEST_LENGTH*2+1)*sizeof(char));
			//asenha = smd5(senha,asenha);
			
			// Esta ativo em outra sessao
			if(search_node(lista, nombre) != NULL){
				
				sprintf(respuesta, "1/4/%s",nombre);
				
			}else{ // Existe faz tudo normal
				
				// Se usuario ja existe na lista nao pode logar de novo
				situacao=loga_user(nombre,senha,conn);
				
				if (situacao==1){ // Login correto
					logado=1;
					insert_end(lista, new_node(suser,nombre));
					alterlista = 1;
					show_list(lista);
					sprintf(respuesta, "1/1/%s",nombre); // Login correto
				}else if (situacao==3){ 
					sprintf(respuesta, "1/2/%s",nombre); // Credenciais incorretas
				}else if (situacao==0){ 
					sprintf(respuesta, "1/0/%s",nombre); // Erro ao logar
				}else{ 
					sprintf(respuesta, "1/3/%s",nombre); // Erro ao logar
				}
			}
			
			//free(asenha);
			
		}else if(codigo==2){ // Solicita deslogar servico = 2/
			
			printf("Solicitou deslogar");
			remove_node(lista, search_node(lista, nombre));
			alterlista = 1;
			logado=0;
			show_list(lista);
			sprintf(respuesta, "2/1/%s",nombre); // Deslogin correto
			
			
		}else if(codigo==3){ //Solicita excluir USUARIO servico = 3/
			// Somente se estiver logado
			if(logado){
				situacao=remove_user(nombre,conn);
				if(situacao == 1){
					sprintf(respuesta,"3/1%s",nombre); // Deletado corretamente
					
					
					remove_node(lista, search_node(lista,nombre));
					
					//elimina(lista, nombre,tamanho);
					//mostra(*lista);
					show_list(lista);
					alterlista = 1;
					logado=0;
				}else if(situacao == 2){
					sprintf(respuesta,"3/2%s",nombre); // Erro ao excluir
				}
			}else{ // Praticamente impossivel de cair nesse caso
				sprintf(respuesta,"3/3%s",nombre); // Erro ao excluir
			}
			
		}else if(codigo==4){ // Envia mensagens
			
			// Vai ter tamanho maximo de 150 a mensagem
			// Assim que:
			
			// 4/nombre_quien_envia/0/mensagem -> todos os conectados
			// 4/nombre_quien_envia/1/mensagem -> todos da partida
			// Aloca espaco mensagem que tem maximo de 150 chars
			// Falta separar 
			char tipo_envio[2];
			char persona_especifica[MAXNOME];
			p = strtok(NULL, "/");
			strcpy(tipo_envio, p);
			int tipo_envios = atoi(tipo_envio);
			// Agora separa a mensagem em Si
			char * texto_mensagem = (char*)malloc((MAXMENSAGEM+MAXNOME+5)*sizeof(char));
			char * somente_mensagem = (char*)malloc((MAXMENSAGEM+1)*sizeof(char));
			// Antes concatena assim:
			// Metodo pode ser 0 1 2 3(no futuro)
			// 10/quem_enviou/metodo/mensagem
			
			if(tipo_envios == 0){
				printf("Mensagem para todos os conectados\n");
				
				vetsockets = vetor_socket(lista);
				
			}else if(tipo_envios == 1){
				printf("Mensagem para todos da partida");
				vetsockets = vetor_socket_partida(lista,get_partida(lista, nombre));
				
			}else{// tipo 2 coleta pessoa aqui
				printf("Mensagem para pessoa especifica");
				p=strtok(NULL,"/");
				strcpy(persona_especifica, p);
				
			}
			
			
			p=strtok(NULL,"/");
			strcpy(somente_mensagem, p);
			sprintf(texto_mensagem,"10/%s/%d/%s",nombre,tipo_envios,somente_mensagem);
			printf("Mensagem = %s\n",somente_mensagem);
			
			free(somente_mensagem);
			
			
			if(tipo_envios == 0 || tipo_envios == 1){
				
				i = 1;
				
				while(vetsockets[0]>0){
					write(vetsockets[i],texto_mensagem, strlen(texto_mensagem));
					vetsockets[0]-=1;
					i++;
				}
				
				free(vetsockets);
				
			}else{ // uma pessoa so
				int socket_especifica = get_socket(lista,persona_especifica);
				write(socket_especifica,texto_mensagem, strlen(texto_mensagem));
				write(suser,texto_mensagem, strlen(texto_mensagem));
			}
			
			free(texto_mensagem);
			strcpy(respuesta,"11/1"); // Mensagens enviadas
			
			
		}else if (codigo==5){ // insere USUARIO servico = 5/
			
			char senha[20];
			p = strtok( NULL, "/");
			strcpy(senha, p);
			
			//char *hsenha = malloc((MD5_DIGEST_LENGTH*2+1)*sizeof( char));
			
			//hsenha = smd5(senha,hsenha);
			
			printf("%s\n",senha);
			
			
			situacao=insere_user(nombre,senha,conn);
			
			if(situacao == 1){
				sprintf(respuesta,"5/1%s",nombre); // Inserido correto
			}else if(situacao == 2){
				sprintf(respuesta,"5/2%s",nombre); // Usuario ja existe
			}else{
				sprintf(respuesta,"5/3%s",nombre); // Erro ao inserir
			}
			
			//free(hsenha);
			
		}else if(codigo==6){ // insere USUARIO servico = 6/quemChamou/quantidade/invitado1/invitado2/invitado3...
			alterlista=1;
			printf("Codigo 6\n");
			i = 0;
			int aux = 0;
			unsigned int idgame = 0;
			carta temp;
			char qjugador[5];
			p = strtok( NULL, "/");
			strcpy(qjugador, p);
			
			int qjugadores =  atoi(qjugador);
			printf("Quantidade de jogadores = %d",qjugadores);
			char convidado[TAMUSERNAME];
			// Ya tenemos el nombre
			
			// Cria partida insere quem convidou e faz loop com os outros
			// Cria partida e devolve id
			idgame=cria_partida(conn);
			retira_partida(lista,nombre);
			
			make_dono(lista,nombre);
			// Aqui ja pode gerar um baralho e colocar indice igual a 0
			preenche(lista,nombre);
			
			// Ate aqui ja tenho quem criou o jogo
			// Agora relaciono o criador do jogo
			printf("Nome de quem solicitou = %s\n",nombre); 
			
			relaciona_jugador(conn, nombre, idgame);
			// Adiciona quantidade de jogadores
			
			alter_emjogo(lista,nombre,1);
			alter_jugadores_partida(lista,nombre,qjugadores+1);
			sum_jugadores_momento(lista,nombre);// Incrementa um nos jogadores
			alter_idgame(lista, nombre, idgame);
			// A cada resposta altera osvalores de quem criou a partida
			
			// Se alguem nao aceita deleta tudo relacionado ao jogo
			// 6/quemchamou/idgame
			char conviteres[MAXNOME+10];
			sprintf(conviteres, "6/%s/%u",nombre,idgame);
			
			for(i=0;i<qjugadores;i++){
				
				p = strtok( NULL, "/");
				strcpy(convidado, p);
				
				// Envia para todos os jogadores convidados
				
				printf("Convidado %d = %s\n",i,convidado);
				// Enviar convite para os convidados
				write(get_socket(lista,convidado),conviteres, strlen(conviteres));
			}
			
			// atriubi a idgame no usuario que convidou
			// Criar variavel com quantiade de pessoas que foram convidadas tambem
			// vai descontanto ate faltar zero para iniciar
			
			// Aqui envia que ja esta na partida e que os convites foram enviados
			sprintf(respuesta,"9/1%s",nombre);
			// Convida os outros da partida
			
			// Antes de convidar para testar vou tentar fazer um loop
			
			// Faz um for com a quantidade de convidados e envia:
			// 6/quemchamou/idpartida
			
		}else if(codigo==7){ // resposta convite partida = 6/quemChamou/quantidade/invitado1/invitado2/invitado3...
			alterlista=1;
			printf("Codigo 7\n");
			// 7/nombre/1/donopartida/idgame
			// aqui vai sobrar somente  /1/donopartida/idgame
			
			char respconvite[2];
			p = strtok( NULL, "/");
			strcpy(respconvite, p);
			int respconvites = atoi(respconvite);
			printf("Reposta convite game = %d",respconvites);
			// Trim o dono da partida
			char donopartida[MAXNOME+1];
			p = strtok( NULL, "/");
			strcpy(donopartida, p);
			int i=0, momento=0;
			char contesta[7+MAXNOME];
			// Seleciona o id da partida
			char idbdgame[10];
			p = strtok( NULL, "/");
			strcpy(idbdgame, p);
			unsigned int idbdgames = atoi(idbdgame);
			// verifica se existe uma partida com essa id (fazer depois)
			printf("Nome de quem respondeu = %s\n",nombre); 
			printf("Nome do dono da partida = %s\n",donopartida);
			if(existe_game(conn, idbdgames)){ // Se game existe
				
				if(respconvites == 1){ // Aceitou
					retira_partida(lista,nombre);
					// relaciona a pessoa com a partida
					relaciona_jugador(conn, nombre,idbdgames);
					sum_jugadores_momento(lista,donopartida);
					alter_idgame(lista,nombre,idbdgames);
					alter_emjogo(lista,nombre,1);
					//if(usuario->jugadores_momento == usuario->jugadores_partida){
					if(qtd_conectados_partida(lista, idbdgames) == get_jugadores_momento(lista, donopartida)){
						
						//strcpy(respuesta,"7/1/"); // Inserido na partida
						//strcat(respuesta, nombre);
						
						node * donod = search_dono(lista, idbdgames);
						
						printf("HAHAHAHAH Dono = %s\n",donod->username);
						
						//printf("Sequencia de jogo TESTETTTTTTTTTTT\n");
						
						printf("Sequencia de jogo\n");
						
						sequencia_jogo(lista,nombre);
						
						
						//printf("PESSOA SEQ1 = %s\n",donod->sequencia[0]);
						//printf("PESSOA SEQ2 = %s\n",donod->sequencia[1]);
						
						printf("Todos ja estao prontos para comecar\n");
						
						
						// Vai enviar assim para todos da partida
						
						// 12/jogant/acao-result/cartaAtual/prox/qtd-jog/Jog1/pont/Jog2/pont
						// Posicao
						// 0    1     2  3   4   5   6     7   8   9 ...
						
						// 12/juninho/0/KS/jose/2/juninho/10/jose/15 ... -> Primeira jogada
						
						// se o codigo for igual a zero vai saber que eh a primeira (mesmo nome
						// 12/juninho/1/KS/jose/2/juninho/10/jose/15 ... -> Disse que era maior e eh maior (acertou)
						// 12/juninho/2/KS/jose/2/juninho/10/jose/15 ... ->  Disse que era menor e eh maior
						// 12/juninho/3/KS/jose/2/juninho/10/jose/15 ... -> Disse que era menor e eh menor (acertou)
						// 12/juninho/4/KS/jose/2/juninho/10/jose/15 ... -> Disse que era maior e eh menor
						// 12/juninho/5/KS/jose/2/juninho/10/jose/15 ... -> Passou vez
						
						// Envia para todos
						
						// Vai pegar a posicao atual % quantidade-1
						int jogaatual = (donod->proxJoga)%(qtd_conectados_partida(lista, idbdgames));
						char * testestring = (char*)malloc(MAXNOME*10*sizeof(char));
						// Junta com a posicao 1
						int cartaatual = donod->poscarta;
						// no lugar do nome ia ja pegar o proximo jogador // Na primeira o proximo eh o mesmo
						sprintf(testestring, "12/%s/0/%d%c/%s",donod->sequencia[jogaatual],donod->baralho[cartaatual].numero,donod->baralho[cartaatual].naipe,donod->sequencia[jogaatual]);
						sprintf(testestring, "%s/%s",testestring,string_conectados_partida_pontos(lista,idbdgames));
						// qtd-jog/Jog1/pont/Jog2/pont
						
						printf("Exemplo inicio JOGO: \n\n\t %s\n",testestring);
						
						strcpy(contesta,testestring);
						strcpy(respuesta,testestring);
						//strcpy(contesta,"8/1/");// Estan todos y juego empeza
						//strcat(contesta,nombre);
						
						free(testestring);
					}else{ // Ainda faltam pessoas
						
						strcpy(respuesta,"7/1/"); // Inserido na partida
						strcat(respuesta, nombre);
						
						printf("Ainda faltam pessoas\n");
						strcpy(contesta,"8/0/");// faltan personas
						strcat(contesta,nombre);
						
					}
					// Envia a mensagem aqui independente do que foi
					
					
					vetsockets = vetor_socket_partida(lista,get_partida(lista, nombre));
					
					
					
					i = 1;
					while(vetsockets[0]>0){
						
						// Para a propria pessoa vai enviar depois
						if(vetsockets[i] != suser){
							write(vetsockets[i], contesta, strlen(contesta));
						}
						vetsockets[0]-=1;
						i++;
						
					}
					
				}else if(respconvites == 2){ // Recusou
					
					// Retira todos da partida
					// Vai avisar todos que alguem nao aceitou e excuir
					deleta_game(conn, idbdgames);
					printf("Usuario %s nao aceitou, partida deletada\n",nombre);
					
					alterlista=1;
					
					vetsockets = vetor_socket_partida(lista,idbdgames);
					
					strcpy(contesta,"8/3/");// acaba partida
					strcat(contesta,nombre);
					
					i = 1;
					while(vetsockets[0]>0){
						printf("retirou da partida\n");
						
						if(vetsockets[i] != suser){
							write(vetsockets[i], contesta, strlen(contesta));
						}
						
						retira_partida(lista,get_nombre(lista,vetsockets[i]));
						vetsockets[0]-=1;
						i++;
						
					}
					
					free(vetsockets);
					
					strcpy(respuesta,"8/3/");
					strcat(respuesta,nombre);
					
					// envia que acabou
					// Vai enviar para todos que a partida acabou
				}
				//strcpy(respuesta,"99/");
			}else{ // Avisa que soliciotu por ele que nao esta disponivel mais
				
				sprintf(respuesta,"7/0/nombre");// Nao existe mais a partida que deseja entrar
				
			}
			
			// Se alguem nao aceita deleta tudo relacionado ao jogo
		}else if(codigo==8){
			alterlista=1;
			
			strcpy(respuesta,"8/2/");
			strcat(respuesta,nombre);
			
			printf("Solicitou acabar partida");
			vetsockets = vetor_socket_partida(lista,get_partida(lista, nombre));
			char contesta[7+MAXNOME];
			strcpy(contesta,"8/2/");// acaba partida
			strcat(contesta,nombre);
			
			i = 1;
			while(vetsockets[0]>0){
				
				if(vetsockets[i] != suser){
					write(vetsockets[i], contesta, strlen(contesta));
				}
				printf("DDDDDD Retirou da partida\n");
				retira_partida(lista,get_nombre(lista,vetsockets[i]));
				vetsockets[0]-=1;
				i++;
				
			}
			
			free(vetsockets);
			// envia isso para todos se for codigo 2
			
		}else if(codigo==9){
			// Funcao para apostar
			
			// Primeiro vai achar o dono da partida por meio da busca de todos mesmo
			// porem vai buscar qual deles tem o mesmo gameID e tem o isdono = 1;
			
			//
			
			// Vai fazer o que tem que fazer na aposta
			// conferir se eh ultima partida e enviar a carta na ppsicao poscarta
			// vai ser interessante colocar o ultimo a jogar e quem vai ser o proximo
			// Para mostrar na tela
			// 9/quemApostou/acao
			
			// Vai receber do cliente
			
			// 9/juninho/1 -> Acha que a seguinte eh maior
			// 9/juninho/2 -> Acha que a seguinte eh menor
			// 9/juninho/3 -> Passa a vez
			
			// Vai enviar assim para todos da partida
			
			// 12/jogant/acao-result/cartaAtual/prox/qtd-jog/Jog1/pont/Jog2/pont
			// Posicao
			// 0    1     2  3   4   5   6     7   8   9 ...
			// 12/juninho/1/KS/jose/2/juninho/10/jose/15 ... -> Disse que era maior e eh maior (acertou)
			// 12/juninho/2/KS/jose/2/juninho/10/jose/15 ... ->  Disse que era menor e eh maior
			// 12/juninho/3/KS/jose/2/juninho/10/jose/15 ... -> Disse que era menor e eh menor (acertou)
			// 12/juninho/4/KS/jose/2/juninho/10/jose/15 ... -> Disse que era maior e eh menor
			// 12/juninho/5/KS/jose/2/juninho/10/jose/15 ... -> Passou vez
			// Envia para todos
			
			
			// Se errou perde 4
			// Se acertou ganha 2
			// Se passou a vez perde 2
			
			
			// Pode passar a vez (simplesmente vai descontar ponto e mandar de novo);
			
			// Is ultima?
			
			
		}
		
		
		if(codigo !=0 ){ // Desconectar
			printf("Codigo: %d => Reposta: %s\n",codigo,respuesta);
			//printf ("Resposta: %s\n", respuesta);
			// Enviamos a resposta
			
			write(suser,respuesta,strlen(respuesta));
			
		}
		
		if((codigo == 0)||(codigo == 1)||(codigo== 2)||(codigo== 3)||(codigo== 4)||(codigo== 5)||(codigo== 6)||(codigo== 7)||(codigo==8)){

			if(alterlista && lista->tam > 0){
				
				printf("String conectados\n");
				char * sconectados = string_conectados_indicador_jogo(lista);
				
				printf("\n%s\n",sconectados);
				
				vetsockets = vetor_socket(lista);
				
				i = 1;
				
				// Aloca o tamanho maximo de um nome * a quantidade de pessoas
				char notificacion[MAXNOME*vetsockets[0]+MAXNOME+10];
				
				sprintf(notificacion, "4/%s",sconectados);
				
				while(vetsockets[0]>0){
					
					printf("USUARIOS CONECTADOS STRING = %s \n",notificacion);
					write(vetsockets[i],notificacion, strlen(notificacion));
					printf("vetsockets p%d = %d \n",i,vetsockets[i]);
					vetsockets[0]-=1;
					i++;
				}
				
				free(vetsockets);
				free(sconectados);
				alterlista=0;
			}
		}
	}
	// Se acabo el servicio para este cliente
	close(suser);
	mysql_close(conn);
	
}
