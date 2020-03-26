#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <mysql.h>

// Intoducir dados en base ya creada
#define SERVIDOR "localhost"
#define USUARIO "root"
#define SENHA "mysql"
#define BASE "GameSO"
#define PLAYERFILE "players.txt"
#define GAMEFILE "games.txt"
#define QTDMAX 4
#define QTDMIN 2
#define CHARSNOME 25
#define TAMUSERNAME CHARSNOME+1
#define PORTA 9000


int insere_Player(char nome_arq[], MYSQL *conn);

// Funcao para criar Game inserir usernames do array e retrornar o id do game que estao
unsigned int cria_Game(MYSQL *conn, char players[QTDMAX][TAMUSERNAME], int qtd);

// Funcao para alterar pontuacao de um usuario especifico
int altera_Pontuacao(MYSQL *conn, unsigned int id_game, char player[], int alt_score);

int insere_user(char user[], char senha[], MYSQL *conn);

int loga_user(char user[], char senha[], MYSQL *conn);

// Operacoes usuario

int existe_user(char user[], MYSQL *conn);

int desativa_user(char user[], char senha[], MYSQL *conn);

int ativa_user(char user[], char senha[], MYSQL *conn);

int user_ativo(char user[], MYSQL *conn);


int logado = 0; // 0 = nao

int main(int argc, char *argv[]){

	int sock_conn, sock_listen, ret;
	struct sockaddr_in serv_adr;
	char peticion[512];
	char respuesta[512];
	
	// Socket que vai esperar por alguma conexao, de escuta
	if ((sock_listen = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		printf("Error ao criar socket");
	// Fem el bind al port
	
	
	memset(&serv_adr, 0, sizeof(SERVIDOR));
	serv_adr.sin_family = AF_INET;
	
	// Estamos escutando de qualquer endereco ip
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	// Associamos o socket que criamos com porta e tipo de dados
	serv_adr.sin_port = htons(PORTA);
	if (bind(sock_listen, (struct sockaddr *) &serv_adr, sizeof(serv_adr)) < 0)
		printf ("Erro ao fazer bind");
	
	// A fila de xonecoes nao pode ser maior que 3
	// Ate 3 podem estar na fila esperando pelo servidor
	if (listen(sock_listen, 3) < 0)
		printf("Erro na escuta");
	
	int i;
	
	char players[QTDMAX][TAMUSERNAME] = {"jose", "juninhoojl", "luiz"};
	
	int qtdp = 3;
	
	//int i=0;
	
	unsigned int id_jogo=0;
	
	
	// Ler lista de pessoas para um mesmo jogo
	// Cria jogo
	// Pega o id e adiciona na lista
	
	MYSQL *conn;
	int err;
	
	conn=mysql_init(NULL);
	
	/*	INSERT INTO Game (Duracion,Vencedor) VALUES (33,1);*/
	/*	INSERT INTO Game (Duracion,Vencedor) VALUES (30,2);*/
	
	/*	INSERT INTO Relaciona (IDg,IDp) VALUES (1,1);*/
	/*	INSERT INTO Relaciona (IDg,IDp) VALUES (1,2);*/
	
	
	if(conn==NULL){
		printf("Error ao criar conexao: %u %s\n",mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	
	conn=mysql_real_connect(conn,SERVIDOR,USUARIO,SENHA,BASE,0, NULL, 0);
	
	if(conn==NULL){
		printf("Erro ao iniciar conexao: %u%s\n",mysql_errno(conn),mysql_error(conn));
		exit (1);
	}
	
	
	/*
	for(i=0;i<qtdp;i++){
	printf("Player %d = %s\n",i,players[i]);
	}
	
	*/
	
	
	insere_user("juninhos1","1qaz2wsx",conn);
	
	insere_user("jose","asdfghjk",conn);
	loga_user("jose","asdfghjk",conn);
	
	desativa_user("jose","asdfghjk",conn);
	
	printf("ATIVO = %d", user_ativo("juninhos1",conn));
	
	ativa_user("jose","asdfghjk",conn);
	
	// Descomentar para inserir jugadores
	//insere_Player(PLAYERFILE, conn);
	
	//id_jogo=cria_Game(conn, players, qtdp);
	
	//altera_Pontuacao(conn, 1, players[0], 10);
	
	qtdp=3;
	
	// Descomentar para criar juego
	//
	//printf("IdJogo = %u\n",id_jogo); 
	
	/*	for(i=0;i<qtdp;i++){*/
	/*		printf("Player %d = %s\n",i,players[i]);*/
	/*	}*/
	
	// Agora ja relaciona jogadores da lista usando id do game

	
	// Laco infinito
	for (;;){
		printf ("Escuchando\n");
		
		// Quando escuta algo cria um socket de conexao
		sock_conn = accept(sock_listen, NULL, NULL);

		printf ("Recebi uma conexao\n");


		int terminar =0;
		// Atender esse cliente ate que se desconecte
		int situacao = 0;
		while (terminar ==0)
		{
			// Ahora recibimos la petici?n
			ret=read(sock_conn,peticion, sizeof(peticion));
			printf ("Recibido\n");
			
			// Tenemos que a?adirle la marca de fin de string 
			// para que no escriba lo que hay despues en el buffer
			peticion[ret]='\0';
			
			
			printf ("Peticao: %s\n",peticion);
			
			// vamos a ver que quieren
			char *p = strtok( peticion, "/");
			int codigo =  atoi (p);
			// Ya tenemos el c?digo de la petici?n
			char nombre[20];
			
			if (codigo !=0)
			{
				p = strtok( NULL, "/");
				strcpy (nombre, p);
				// Ya tenemos el nombre
				printf ("Codigo: %d, Nome: %s\n", codigo, nombre);
			}
			
			if (codigo ==0){ //petici?n de desconexi?n
				terminar=1;
			}else if (codigo ==1){ //piden la longitd del nombre
				sprintf (respuesta,"%d",(int)strlen (nombre));
			}else if (codigo ==2){
				// quieren saber si el nombre es bonito
				if((nombre[0]=='M') || (nombre[0]=='S')){
					strcpy (respuesta,"SIM");
				}else{
					strcpy (respuesta,"NAO");
				}
			}else if (codigo==3){ //quiere saber si es alto
			
				p = strtok( NULL, "/");
				float altura =  atof (p);
				if (altura > 1.70){
					sprintf (respuesta, "%s eh alto",nombre);
				}else{
					sprintf (respuesta, "%s eh baixo",nombre);
				}
			}else if (codigo==4){// Busca usuario
				
				if (existe_user(nombre,conn) == 1){
					
					if(user_ativo(nombre,conn) == 1){
						sprintf (respuesta, "%s existe",nombre);
						
					}else{
						sprintf (respuesta, "%s existe (mas esta desativado)",nombre);
					}
					
				}else{
					sprintf (respuesta, "%s nao existe",nombre);
				}
				
				
			}else if (codigo==5){ // insere USUARIO
				
				char senha[20];
				p = strtok( NULL, "/");
				strcpy (senha, p);
				
				situacao=insere_user(nombre,senha,conn);
				
				if (situacao == 0){
					sprintf (respuesta, "%s inserido com sucesso",nombre);
				}else if (situacao == 1){
					sprintf (respuesta, "%s ja existe",nombre);
				}else{
					sprintf (respuesta, "%s nao pode ser inserido",nombre);
				}
				
			}else if (codigo==6){ // remove USUARIO
				
				char senha[20];
				p = strtok( NULL, "/");
				int situacao=0;
				strcpy (senha, p);
				
				situacao = desativa_user(nombre,senha,conn);
				
				if (situacao == 0){
					sprintf (respuesta, "%s desativado com sucesso",nombre);
				}else if (situacao == 2){
					sprintf (respuesta, "%s nao pode ser desativado",nombre);
				}else{
					sprintf (respuesta, "Erro ao desativar %s",nombre);
				}
				
				
			}else if (codigo==7){ // recupera USUARIO
				
				char senha[20];
				p = strtok( NULL, "/");
				int situacao=0;
				strcpy (senha, p);
				
				situacao = ativa_user(nombre,senha,conn);
				
				if (situacao == 0){
					sprintf (respuesta, "%s ativado com sucesso",nombre);
				}else if (situacao == 2){
					sprintf (respuesta, "%s nao pode ser reativado",nombre);
				}else{
					sprintf (respuesta, "Erro ao reativar %s",nombre);
				}
				
				
			}
			
			if(codigo !=0){ // Desconectar
			
				
				printf ("Resposta: %s\n", respuesta);
				// Enviamos a resposta
				write (sock_conn,respuesta, strlen(respuesta));
			}
		}
		// O servico acabou para esse cliente
		close(sock_conn); 
		mysql_close (conn);
	}
}


// Lista usuarios

	/*	INSERT INTO Player (Username, Password) VALUES ('Jose', '1qaz2wsx');*/
	/*	INSERT INTO Player (Username, Password) VALUES ('Luiz', '2wsx3edc');*/
	// Retorna ID do Game
int insere_Player(char nome_arq[], MYSQL *conn){
	
	FILE *arq;
	int err;
	char username[25];
	char senha[25];
	char query[80];
	
	// Abre arquivo
	arq=fopen(nome_arq, "r");
	
	// Insere dados
	if (arq==NULL){
		perror("Error");
		return 1;
	}else{ 
		
		if (arq==NULL){
			perror("Error");
			return 1;
		}else{
			
			while(!feof(arq)) {
				
				err=fscanf(arq,"%s %s", &username[0], &senha[0]);
				
				if(err!=2){
					
					// Caso esteja na ultima linha, para nao repetir
					if(err<0){
						return 1;
					}
					printf("Erro ao introduzir dados\n");
					printf("%d",err); 
					
				}
				strcpy (query, "INSERT INTO Player (Username, Password) VALUES ('");
				strcat (query, username);
				strcat (query, "','");
				strcat (query, senha); 
				strcat (query, "'");
				strcat (query, ");");
				printf("query = %s\n", query);
				err = mysql_query(conn, query);
				
				if (err!=0){
					printf ("Error ao introduzir dados na base %u %s\n", mysql_errno(conn), mysql_error(conn));
					return 1;
				}
			}
		}
	}
	
	// Fecha arquivo
	fclose(arq);
	
	return 0;
}
	
	
	
int insere_user(char user[], char senha[], MYSQL *conn){
	
	// Conferir se existe USUARIO
	// se nao nao insere
	char query[80];
	int err;
	
	if(existe_user(user,conn)){
		
		printf("Usuario ja existe\n");
		return 1;
	}else{
		strcpy (query, "INSERT INTO Player (Username, Password) VALUES ('");
		strcat (query, user);
		strcat (query, "','");
		strcat (query, senha); 
		strcat (query, "'");
		strcat (query, ");");
		printf("query = %s\n", query);
		err = mysql_query(conn, query);
		
		if (err!=0){
			printf ("Error ao introduzir dados na base %u %s\n", mysql_errno(conn), mysql_error(conn));
			return 2;
		}else{
			
			printf("Usuario inserido com sucesso\n");
		}
	}
	return 0;
}
	
// Deleta usuario (altera flag de ativo para false);
// Ativo recebe bit false
	
int loga_user(char user[], char senha[], MYSQL *conn){
	
	char query[80];
	int err;
	MYSQL_RES *resultado;
	MYSQL_ROW row;

	if(existe_user(user,conn)){
		
		// SELECT EXISTS(SELECT * FROM Player WHERE Username = 'jose' AND Password = 'asdfghjk');
		
		strcpy (query, "SELECT EXISTS(SELECT * FROM Player WHERE Username = '");
		strcat (query, user);
		strcat (query, "' AND Password = '");
		strcat (query, senha);
		strcat (query, "');");
		
		err = mysql_query(conn, query);
		
		if (err!=0) {
			printf ("Error ao consultar usuario na base %u %s\n", mysql_errno(conn), mysql_error(conn));
			exit (1); 
		}
		
		resultado = mysql_store_result(conn);
		row = mysql_fetch_row(resultado);
		
		if(atoi(row[0]) == 1){ // Login ok
			
			printf("Usuario e senha corretos\n");
			return 1;
			
		}else{ // Nao pode logar
			
			printf("Usuario e/ou senha incorretos\n");
			
		}
		
	}else{
		printf("Usuario nao existe\n");
	}

	return 0;
}
	


int user_ativo(char user[], MYSQL *conn){
	
	char query[80];
	int err;
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	char valor;
	
	// Somente se existe
	
	if(existe_user(user,conn)){

		strcpy (query, "SELECT Ativo FROM Player WHERE Username = '");
		strcat (query, user);
		strcat (query, "';");
		
		err = mysql_query(conn, query);
		
		if (err!=0) {
			printf ("Error ao consultar usuario na base %u %s\n", mysql_errno(conn), mysql_error(conn));
			exit (1); 
		}
		
		resultado = mysql_store_result(conn);
		row = mysql_fetch_row(resultado);
		
		
	}else{
		//Retorna 2 se nao exite
		return 2;
	}
	
	
	return atoi(row[0]);
}
	

	
int desativa_user(char user[], char senha[], MYSQL *conn){
	
	char query[80];
	int err;
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	
	// Se pode se autenticar pode se remover
	
	if(loga_user(user,senha,conn)){
		
		printf("Pode ser deletado\n");
		
		strcpy (query, "UPDATE Player SET Ativo=0 WHERE Username='");
		strcat (query, user);
		strcat (query, "';");
		
		printf("query = %s\n", query);
		
		err = mysql_query(conn, query);
		
		if (err!=0){
			printf ("Error ao remover usuario na base %u %s\n", mysql_errno(conn), mysql_error(conn));
			return 1;
		}
		
	}else{
		
		printf("Nao pode ser deletado");
		// Nao pode 
		return 2;
	}
	
	
	return 0;
}
	
int ativa_user(char user[], char senha[], MYSQL *conn){
	
	char query[80];
	int err;
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	
	// Se pode se autenticar pode se remover
	
	if(loga_user(user,senha,conn)){
		
		printf("Pode ser reativad\n");
		
		strcpy (query, "UPDATE Player SET Ativo=1 WHERE Username='");
		strcat (query, user);
		strcat (query, "';");
		
		printf("query = %s\n", query);
		
		err = mysql_query(conn, query);
		
		if (err!=0){
			printf ("Error ao reativar usuario na base %u %s\n", mysql_errno(conn), mysql_error(conn));
			return 1;
		}
		
	}else{
		
		printf("Nao pode ser reativado");
		// Nao pode 
		return 2;
	}
	
	
	return 0;
}


int existe_user(char user[], MYSQL *conn){
	
	char query[80];
	int err;
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	
	strcpy (query, "SELECT EXISTS(SELECT * FROM Player WHERE Username = '");
	strcat (query, user);
	strcat (query, "');");
	
	err = mysql_query(conn, query);
	
	if (err!=0) {
		printf ("Error ao consultar usuario na base %u %s\n", mysql_errno(conn), mysql_error(conn));
		exit (1); 
	}
	
	resultado = mysql_store_result(conn);
	row = mysql_fetch_row(resultado);
	
	// Quantidade que existe, tem que ser 1 para existir
	
	return atoi(row[0]);
}

	
	
// Recebe pessoas que vao entrar em um jogo
unsigned int cria_Game(MYSQL *conn, char players[QTDMAX][TAMUSERNAME], int qtd){
	
	int err,i=0;
	unsigned int id_game=0;
	char query[80];
	char id_games[10];
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	
	// Cria Game
	strcpy (query, "INSERT INTO Game () VALUES ();");
	err = mysql_query(conn, query);
	
	if (err!=0){
		printf ("Error ao introduzir dados na base %u %s\n", mysql_errno(conn), mysql_error(conn));
		return 1;
	}
	
	// Seleciona ultimo ID
	strcpy (query, "SELECT LAST_INSERT_ID();");
	err = mysql_query(conn, query);
	
	if (err!=0) {
		printf ("Error al consultar ultimo ID de la base %u %s\n", mysql_errno(conn), mysql_error(conn));
		exit (1); 
	}
	
	resultado = mysql_store_result(conn);
	row = mysql_fetch_row(resultado);
	
	id_game = atoi (row[0]);
	
	printf("id_game = %u\n",id_game); 
	
	
	for(i=0;i<qtd;i++){
		
		//INSERT INTO Relaciona (Game,Player) VALUES (1,'Luiz');
		printf("id_game = %u\n",id_game);
		strcpy (query, "INSERT INTO Relaciona (Game,Player) VALUES ('");
		sprintf(id_games, "%u", id_game);
		strcat (query, id_games);
		strcat (query, "','");
		strcat (query, players[i]);
		strcat (query, "'");
		strcat (query, ");");
		printf("query = %s\n", query);
		err = mysql_query(conn, query);
		
		// Nao precisa esvaziar string pq tem o fim da linha e comeca no 0
		if (err!=0){
			printf ("Error ao introduzir dados na base %u %s\n", mysql_errno(conn), mysql_error(conn));
			exit (1); 
		}
		
	}
	
	// Retorna id do Game que foram adicionados
	return id_game;
}

	
int altera_Pontuacao(MYSQL *conn, unsigned int id_game, char player[], int alt_score){
	
	// Query para editar 
	// UPDATE Relaciona SET score=PONTOS WHERE Player=PLAYERNAME AND Game=GAMEID;
	
	// Antes consulta os pontos atuais faz a conta com a alteracao
	
	int err,i=0;
	//unsigned int id_game=0;
	char query[80];
	char id_games[10];
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	int score=10;
	char scores[10];
	
	
	strcpy (query, "SELECT Score from Relaciona WHERE Game='");
	sprintf(id_games, "%u", id_game);
	strcat (query, id_games);
	strcat (query, "' AND Player='");
	strcat (query, player);
	strcat (query, "';");
	
	printf("query = %s\n", query);
	
	err = mysql_query(conn, query);
	
	if (err!=0){
		printf ("Error ao introduzir dados na base %u %s\n", mysql_errno(conn), mysql_error(conn));
		return 1;
	}
	
	resultado = mysql_store_result(conn);
	row = mysql_fetch_row(resultado);
	
	score = atoi (row[0]);
	
	printf("\nSCORE = %d\n",score);
	
	score += alt_score;
	
	strcpy (query, "UPDATE Relaciona SET score='");
	sprintf(scores, "%d", score);
	strcat (query, scores);
	strcat (query, "' WHERE Player='");
	strcat (query, player);
	strcat (query, "' AND Game='");
	sprintf(id_games, "%d", id_game);
	strcat (query, id_games);
	strcat (query, "';");
	printf("query = %s\n", query);
	
	err = mysql_query(conn, query);
	
	if (err!=0){
		printf ("Error ao introduzir dados na base %u %s\n", mysql_errno(conn), mysql_error(conn));
		return 1;
	}
	
	
	return 0;
}




