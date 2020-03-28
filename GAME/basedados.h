#include <stdio.h>
#include <mysql.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

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
#define PORTA 9001


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

