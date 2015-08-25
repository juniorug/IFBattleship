/*
*   HEADER USADO PARA INDEXAR AS MENSAGENS UTILIZADAS NO JOGO
*
*
*
*
*
*/

#ifndef messages_h
#define messages_h

#include "Arduino.h"


static const unsigned char PLAYER_1_ADD_BOAT[] PROGMEM = {"Player 1 adcione 7 barcos \0"};
static const unsigned char PLAYER_2_ADD_BOAT[] PROGMEM = {"Player 2 adcione 7 barcos \0"};
static const char *PLAYER_1_READY PROGMEM = {"Player 1 ready?"};
static const char *PLAYER_2_READY PROGMEM = {"Player 1 ready?"};
static const char *PLAYER_1_NUMBER_CHOOSED PROGMEM = {"Player 1 number choosed:"};
static const char *PLAYER_2_NUMBER_CHOOSED PROGMEM = {"Player 2 number choosed:"};
static const char *EMPATE PROGMEM = {"Empate!"};
static const char *PLAYER_1_COMECA PROGMEM = {"player 1 comeca!"};
static const char *PLAYER_2_COMECA PROGMEM = {"player 2 comeca!"};
static const char *TODOS_OS_BARCOS PROGMEM = {"Todos os barcos foram adcionados! quantidade de players:"};
static const char *HORA_DE_COMECAR PROGMEM = {"Hora de comecar o jogo!!!"};
static const char *PLAYER PROGMEM = {"Player "};
static const char *DIGITE_POSICAO_X_TIRO PROGMEM = {"Digite a posicao X do tiro:"};
static const char *DIGITE_POSICAO_Y_TIRO PROGMEM = {"Digite a posicao Y do tiro:"};
static const char *ACERTOU PROGMEM = {"ACERTOU!!!!!!"};
static const char *AFUNDOU PROGMEM = {"Barco AFUNDOU!!!!"};
static const char *JOGO_ACABOU PROGMEM = {"JOGO ACABOU!!"};
static const char *GANHOU PROGMEM = {"Ganhou"};
static const char *JOGO_CONTINUA PROGMEM = {"Jogo continua, agora e a vez do player"};
static const char *BARCO_NAO_AFUNDOU PROGMEM = {"Barco NAO afundou!!"};
static const char *ERROU PROGMEM PROGMEM = {"ERROU!!!!"};
static const char *DIGITE_POSICAO_X_BARCO PROGMEM = {"Digite a posicao X inicial do barco (0-7):"};
static const char *DIGITE_POSICAO_Y_BARCO PROGMEM = {"Digite a posicao Y inicial do barco (0-7):"};
static const char *DIGITE_TAMANHO_BARCO PROGMEM = {"Digite o tamanho do barco (1-5):"};
static const char *DIGITE_DIRECAO_BARCO PROGMEM = {"Digite a direcao do barco (H: horizontal,V: vertical):"};
static const char *ERRO_QTD_MAX PROGMEM = {"Erro! Quantidade maxima de barcos atingida"};
static const char *ERRO_TAM_INVALIDO PROGMEM = {"Erro! tamanho do barco invalido"};
static const char *ERRO_QTD_HIDRO PROGMEM = {"Erro! Quantidade maxima de Hidroavioes atingida"};
static const char *ERRO_QTD_SUB PROGMEM = {"Erro! Quantidade maxima de Submarinos atingida"};
static const char *ERRO_QTD_CRUZ PROGMEM = {"Erro! Quantidade maxima de Cruzadores atingida"};
static const char *ERRO_QTD_ENC PROGMEM = {"Erro! Quantidade maxima de Encouracados atingida"};
static const char *ERRO_QTD_PA PROGMEM = {"Erro! Quantidade maxima de Porta Avioes atingida"};
static const char *ERRO_POS_INVALIDO PROGMEM = {"Erro! Posicionamento do barco invalido"};
static const char *ERRO_DIREC_INVALIDA PROGMEM = {"Erro! Direcao invalida!"};
static const char *BARCO_ADCIONADO PROGMEM = {"Barco adcionado com sucesso!"};
/*
static const char * = "";
static const char * = "";
static const char * = "";
static const char * = "";
static const char * = "";
static const char * = "";
static const char * = "";
static const char * = "";
static const char * = "";
static const char * = "";
static const char * = "";
static const char * = "";
static const char * = "";
static const char * = "";
static const char * = "";
static const char * = "";
static const char * = "";
static const char * = "";
static const char * = "";
*/
#endif
