#include "basedados.h"

int insere_user(char user[], char senha[], MYSQL *conn){
	
	char query[100];
	int err;
	
	// Se nao existe
	if(!existe_user(user,conn)){
		
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
			return 3;
			
		}else{
			printf("Usuario inserido com sucesso\n");
			return 1;
		}
		
	}else{
		
		printf("Usuario ja existe\n");
		return 2;
	}
	
	return 0;
}
	
	
int loga_user(char user[], char senha[], MYSQL *conn){
	
	char query[100];
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
			return 2;
		}
		
		resultado = mysql_store_result(conn);
		row = mysql_fetch_row(resultado);
		
		if(atoi(row[0]) == 1){ // Login ok
			printf("Usuario e senha corretos\n");
			return 1;
			
		}else{ // Nao pode logar
			printf("Usuario e/ou senha incorretos\n");
			return 3;
		}
		
	}else{
		printf("Usuario nao existe\n");
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
		
