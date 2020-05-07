#ifndef _BASEDADOS_H_
#define _BASEDADOS_H_
#include <stdio.h>
#include <mysql.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "servidor.h"
#include "fmd5.h"

// PRODUCION
// #define SERVIDORDADOS "shiva2.upc.es"


// LOCAL ##########
#define SERVIDORDADOS "localhost"

#define SERVIDOR "localhost"
#define USUARIO "root"
#define SENHA "mysql"
#define BASE "MGX1"
#define PLAYERFILE "players.txt"
#define GAMEFILE "games.txt"
#define QTDMAX 4
#define QTDMIN 2
#define CHARSNOME 25
#define TAMUSERNAME CHARSNOME+1
#define PORTA 50003

int insere_Player(char nome_arq[], MYSQL *conn);

// Funcao para criar Game inserir usernames do array e retrornar o id do game que estao
unsigned int cria_Game(MYSQL *conn, char players[QTDMAX][TAMUSERNAME], int qtd);

// Funcao para alterar pontuacao de um usuario especifico
int altera_Pontuacao(MYSQL *conn, unsigned int id_game, char player[], int alt_score);

int existe_user(char user[], MYSQL *conn);

int loga_user(char user[], char senha[], MYSQL *conn);
// Operacoes usuario

int insere_user(char user[], char senha[], MYSQL *conn);

// Funcao real para remover
// (remove tudo que esta relacionado)
int remove_user(char user[], MYSQL *conn);

// Cria partida e devolve id
unsigned int cria_partida(MYSQL *conn);

// Relaciona jogador com jogo a partir do ID
int relaciona_jugador(MYSQL *conn, char jugador[], unsigned int id_game);

#endif








