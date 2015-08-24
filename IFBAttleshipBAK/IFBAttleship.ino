#include <LedControl.h>
#include <ScrollTest4MAX2.h>
#include "charLibrary.h"
#include "messages.h"

//DEFINES
#define DIM 8



// *CONSTANTS
const int DIN_1 = 12;            //DataIn pin (18)
const int CLK_1 = 11;            //Clock pin (17)
const int CS_1 = 10;           //Load pin (16)
const int DEVICES_PLAYER_1 = 2;      //duas matrizes para o player 1
//definir os pinos da matriz do player 2:

const int DIN_2 = 9; //TESTAR?           //DataIn pin (18)
const int CLK_2 = 8; //TESTAR?          //Clock pin (17)
const int CS_2 = 7; //TESTAR??          //Load pin (16)
const int DEVICES_PLAYER_2 = 2;      //duas matrizes para o player 2

const long scrollDelay = 100;


LedControl lc_player1 = LedControl(DIN_1,CLK_1,CS_1,DEVICES_PLAYER_1);
ScrollTest4MAX2 sc_player1 = ScrollTest4MAX2(&lc_player1,scrollDelay);

LedControl lc_player2 = LedControl(DIN_2,CLK_2,CS_2,DEVICES_PLAYER_2);
ScrollTest4MAX2 sc_player1 = ScrollTest4MAX2(&lc_player2,scrollDelay);

void setup() {
    Serial.begin(9600);
    lc_player1.shutdown(0,false);
    lc_player1.clearDisplay(0);
    lc_player2.shutdown(0,false);
    lc_player2.clearDisplay(0);
    randomSeed(analogRead(A0));  
}

void loop() {
  //sc.scrollMessage(scrollText);
}

