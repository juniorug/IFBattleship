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
static const unsigned char PLAYER_1_READY[] PROGMEM = {"Player 1 ready?"};
static const unsigned char PLAYER_2_READY[] PROGMEM = {"Player 2 ready?"};
static const unsigned char PLAYER_1_NUMBER_CHOOSED[] PROGMEM = {"Player 1 number choosed:"};
static const unsigned char PLAYER_2_NUMBER_CHOOSED[] PROGMEM = {"Player 2 number choosed:"};
static const unsigned char EMPATE[] PROGMEM = {"Empate!"};
static const unsigned char PLAYER_1_COMECA[] PROGMEM = {"player 1 comeca!"};
static const unsigned char PLAYER_2_COMECA[] PROGMEM = {"player 2 comeca!"};
static const unsigned char TODOS_OS_BARCOS[] PROGMEM = {"Todos os barcos foram adcionados! quantidade de players:"};
static const unsigned char HORA_DE_COMECAR[] PROGMEM = {"Hora de comecar o jogo!!!"};
static const unsigned char PLAYER[] PROGMEM = {"Player "};
static const unsigned char DIGITE_POSICAO_X_TIRO[] PROGMEM = {"Digite a posicao X do tiro:"};
static const unsigned char DIGITE_POSICAO_Y_TIRO[] PROGMEM = {"Digite a posicao Y do tiro:"};
static const unsigned char ACERTOU[] PROGMEM = {"ACERTOU!!!!!!"};
static const unsigned char AFUNDOU[] PROGMEM = {"Barco AFUNDOU!!!!"};
static const unsigned char JOGO_ACABOU[] PROGMEM = {"JOGO ACABOU!!"};
static const unsigned char PLAYER_1_GANHOU[] PROGMEM = {"Player 1 Ganhou"};
static const unsigned char PLAYER_2_GANHOU[] PROGMEM = {"Player 2 Ganhou"};
static const unsigned char JOGO_CONTINUA_1[] PROGMEM = {"Jogo continua, agora e a vez do player 1"};
static const unsigned char JOGO_CONTINUA_2[] PROGMEM = {"Jogo continua, agora e a vez do player 2"};
static const unsigned char BARCO_NAO_AFUNDOU[] PROGMEM = {"Barco NAO afundou!!"};
static const unsigned char ERROU[] PROGMEM = {"ERROU!!!!"};
static const unsigned char DIGITE_POSICAO_X_BARCO[] PROGMEM = {"Digite a posicao X inicial do barco (0-7):"};
static const unsigned char DIGITE_POSICAO_Y_BARCO[] PROGMEM = {"Digite a posicao Y inicial do barco (0-7):"};
static const unsigned char DIGITE_TAMANHO_BARCO[] PROGMEM = {"Digite o tamanho do barco (1-5):"};
static const unsigned char DIGITE_DIRECAO_BARCO[] PROGMEM = {"Digite a direcao do barco (H: horizontal,V: vertical):"};
static const unsigned char ERRO_QTD_MAX[] PROGMEM = {"Erro! Quantidade maxima de barcos atingida"};
static const unsigned char ERRO_TAM_INVALIDO[] PROGMEM = {"Erro! tamanho do barco invalido"};
static const unsigned char ERRO_QTD_HIDRO[] PROGMEM = {"Erro! Quantidade maxima de Hidroavioes atingida"};
static const unsigned char ERRO_QTD_SUB[] PROGMEM = {"Erro! Quantidade maxima de Submarinos atingida"};
static const unsigned char ERRO_QTD_CRUZ[] PROGMEM = {"Erro! Quantidade maxima de Cruzadores atingida"};
static const unsigned char ERRO_QTD_ENC[] PROGMEM = {"Erro! Quantidade maxima de Encouracados atingida"};
static const unsigned char ERRO_QTD_PA[] PROGMEM = {"Erro! Quantidade maxima de Porta Avioes atingida"};
static const unsigned char ERRO_POS_INVALIDO[] PROGMEM = {"Erro! Posicionamento do barco invalido"};
static const unsigned char ERRO_DIREC_INVALIDA[] PROGMEM = {"Erro! Direcao invalida!"};
static const unsigned char BARCO_ADCIONADO[] PROGMEM = {"Barco adcionado com sucesso!"};
#endif
