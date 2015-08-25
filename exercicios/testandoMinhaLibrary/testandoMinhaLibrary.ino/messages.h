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
static const unsigned char PLAYER_2_ADD_BOAT[] PROGMEM = "Player 2 adcione 7 barcos \0"};
static const char *PLAYER_1_READY = "Player 1 ready?";
static const char *PLAYER_2_READY = "Player 1 ready?";
static const char *PLAYER_1_NUMBER_CHOOSED = "Player 1 number choosed:";
static const char *PLAYER_2_NUMBER_CHOOSED = "Player 2 number choosed:";
static const char *EMPATE = "Empate!";
static const char *PLAYER_1_COMECA = "player 1 comeca!";
static const char *PLAYER_2_COMECA = "player 2 comeca!";
static const char *TODOS_OS_BARCOS = "Todos os barcos foram adcionados! quantidade de players:";
static const char *HORA_DE_COMECAR = "Hora de comecar o jogo!!!";
static const char *PLAYER = "Player ";
static const char *DIGITE_POSICAO_X_TIRO = "Digite a posicao X do tiro:";
static const char *DIGITE_POSICAO_Y_TIRO = "Digite a posicao Y do tiro:";
static const char *ACERTOU = "ACERTOU!!!!!!";
static const char *AFUNDOU = "Barco AFUNDOU!!!!";
static const char *JOGO_ACABOU = "JOGO ACABOU!!";
static const char *GANHOU = "Ganhou";
static const char *JOGO_CONTINUA = "Jogo continua, agora e a vez do player";
static const char *BARCO_NAO_AFUNDOU = "Barco NAO afundou!!";
static const char *ERROU = "ERROU!!!!";
static const char *DIGITE_POSICAO_X_BARCO = "Digite a posicao X inicial do barco (0-7):";
static const char *DIGITE_POSICAO_Y_BARCO = "Digite a posicao Y inicial do barco (0-7):";
static const char *DIGITE_TAMANHO_BARCO = "Digite o tamanho do barco (1-5):";
static const char *DIGITE_DIRECAO_BARCO = "Digite a direcao do barco (H: horizontal,V: vertical):";
static const char *ERRO_QTD_MAX = "Erro! Quantidade maxima de barcos atingida";
static const char *ERRO_TAM_INVALIDO = "Erro! tamanho do barco invalido";
static const char *ERRO_QTD_HIDRO = "Erro! Quantidade maxima de Hidroavioes atingida";
static const char *ERRO_QTD_SUB = "Erro! Quantidade maxima de Submarinos atingida";
static const char *ERRO_QTD_CRUZ = "Erro! Quantidade maxima de Cruzadores atingida";
static const char *ERRO_QTD_ENC = "Erro! Quantidade maxima de Encouracados atingida";
static const char *ERRO_QTD_PA = "Erro! Quantidade maxima de Porta Avioes atingida";
static const char *ERRO_POS_INVALIDO = "Erro! Posicionamento do barco invalido";
static const char *ERRO_DIREC_INVALIDA = "Erro! Direcao invalida!";
static const char *BARCO_ADCIONADO = "Barco adcionado com sucesso!";
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
