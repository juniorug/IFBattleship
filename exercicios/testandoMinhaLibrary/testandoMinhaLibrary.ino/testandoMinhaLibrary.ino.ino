#include <LedControl.h>
#include <ScrollTest4MAX2.h>
#include <SPI.h>
#include <SD.h>  
#include <TMRpcm.h> 
#include "charLibrary.h"
//#include "messages.h"

//DEFINES
#define DIM 8
#define SD_ChipSelectPin 53  //example uses hardware SS pin 53 on Mega2560
#define SPEAKER_PIN 46   //pino de saida para autofalante
#define HORIZONTAL 'H'
#define VERTICAL 'V'
#define AGUA 'A' 
#define BARCO 'B'  
#define TIRO_CERTO 'C'
#define TIRO_ERRADO 'E'
#define QTD_PLAYERS 2
#define MAX_BOATS 2


/* *CONSTANTS
const int DIN = 12;            //DataIn pin (18)
const int CLK = 11;            //Clock pin (17)
const int LOAD = 10;           //Load pin (16)
const int numDevices = 1;      //Number of MAX7219 LED Driver Chips (1-8)
const long scrollDelay = 100;*/

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
const char *boatDetails[5] = {"Hidroaviao", "Submarino", "Cruzador", "Encouracado", "Porta Aviao"};   

const int bt1 = 2;     // the number of the pushbutton pin
const int bt2 = 3;
const int bt3 = 4;
const int bt4 = 5;
const int bt5 = A7;
const int bt6 = A6;
const int botoes[6] = {bt1,bt2,bt3,bt4,bt5,bt6};

const unsigned char scrollText[] PROGMEM ={
    "  MINHA BIBLIOTECA FUNCIONA   \0"};
const unsigned char PLAYER_1_ADD_BOAT[] PROGMEM = {"Player 1 adcione 7 barcos \0"};

// STRUCTS
struct Boat {
    int x;   //x e y sao as coordenadas iniciais do barco
    int y;
    int size;
    char direction;  //H: horizontal, V: vertical
    bool sunken;     // true: navio afundado
};

struct Player{
    struct Boat boats[MAX_BOATS];
    bool currentPlayer;  //define qual o player que está atacando.
    char matrixBoats[DIM][DIM];   //matriz de barcos
    char matrixShots[DIM][DIM]; //usada quando adcionado a segunda matriz de led
    int playerIndex;    //p1 ou p2
    int countHidro;
    int countSub;
    int countCruz;
    int countEnc;
    int countPA;
    int countShots;  //pra sabermos quantos tiros o player efetuou
    int availableBoats;  //quantidade de barcos no tabuleiro
};

LedControl lc = LedControl(DIN_1,CLK_1,CS_1,DEVICES_PLAYER_1);
ScrollTest4MAX2 sc = ScrollTest4MAX2(&lc,scrollDelay);
LedControl lc2 = LedControl(DIN_2,CLK_2,CS_2,DEVICES_PLAYER_2);
ScrollTest4MAX2 sc2 = ScrollTest4MAX2(&lc2,scrollDelay);
TMRpcm tmrpcm;   // objeto de manipulacao de audio
char mychar;
int playerIndex;
char *message;
struct Player players[QTD_PLAYERS]; //array de jogadores
int bt1State = 0;         // variable for reading the pushbutton status
int bt2State = 0;         // variable for reading the pushbutton status
int bt3State = 0;         // variable for reading the pushbutton status
int bt4State = 0;         // variable for reading the pushbutton status
int bt5State = 0;         // variable for reading the pushbutton status
int bt6State = 0;         // variable for reading the pushbutton status


void setup() {  Serial.begin(9600);
  lc.shutdown(0,false);
  lc.shutdown(1,false);
  lc.clearDisplay(0);
  lc.clearDisplay(1);

  lc2.shutdown(0,false);
  lc2.shutdown(1,false);
  lc2.clearDisplay(0);
  lc2.clearDisplay(1);

  randomSeed(analogRead(A0));  
  tmrpcm.speakerPin = SPEAKER_PIN;

  if (!SD.begin(SD_ChipSelectPin)) {  // inicializando o SDcard
        Serial.println("SD fail");
  } else {
      Serial.println("Initialization Done!");  
  }
  tmrpcm.setVolume(5);
  tmrpcm.play("pacman.wav"); //the sound file "music" will play each time the arduino powers up, or is reset

  for(int i=0; i<6;i++){
      pinMode(botoes[i], INPUT);
  }
}

void loop() {
  //sc.scrollMessage(scrollText);
  mainGame ();
}




void mainGame () { 
    playerIndex = 1;
    message = "";
    int x,y;
    startGame();
}


void startGame(){
      //sc.scrollMessage(scrollText);
   for (int i = 0; i < QTD_PLAYERS; i++) {       
        if (i == 0){
         // scrollText = "teste";
          sc.scrollMessage(PLAYER_1_ADD_BOAT);
        }
   }
           /*Serial.print("I:");
//           Serial.print(reinterpret_cast<const charsc.scrollMessage(scrollText);*>(PLAYER_1_ADD_BOAT));
           const unsigned char scrollText[] PROGMEM ={
    "  MINHA BIBLIOTECA FUNCIONA   \0"};
           //ScrollTest4MAX2 sc = ScrollTest4MAX2(&lc_players[0],scrollDelay);
           //sc.scrollMessage(scrollText);
           //sc_players[i].scrollMessage(mens);
           //Serial.print("mensagem:");
        } else {
           //sc_players[i].scrollMessage(PLAYER_2_ADD_BOAT);
        }
        initializePlayer(&players[i], &playerIndex);
        printPlayerDetails(players[i]);    
        while (players[i].availableBoats < MAX_BOATS) {
            int x,y,boatSize;
            char direction;  
            
            printf("\nDigite a posicao X inicial do barco %d (0-%d): ", players[i].availableBoats + 1, MAX_BOATS);
            scanf("%d", &x);
            
            printf("Digite a posicao Y inicial do barco %d (0-%d): ", players[i].availableBoats + 1, MAX_BOATS );
            scanf("%d", &y);
            
            printf("Digite o tamanho do barco %d (1-5): ", players[i].availableBoats + 1);
            scanf("%d", &boatSize);
            printf("Digite a direcao do barco %d (H: horizontal,V: vertical): ", players[i].availableBoats + 1 );
            scanf(" %c", &direction);

            direction = toupper(direction);
            printf("[X: %d] [Y: %d] [size: %d] [direction: %s]\n", x, y, boatSize, direction == HORIZONTAL ? "Horizontal" : "Vertical");
            
            //add barco    
            bool add = addBoat(&players[i], x, y, boatSize, direction, &message);
            printf("message: %s\n", message); 
            if (add) {
                printBoatDetails(players[i].boats[players[i].availableBoats -1]);    
                printPlayerDetails(players[i]);
            }
        }
    }*/ 
}
