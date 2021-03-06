#include <LedControl.h>
#include <ScrollTest4MAX2.h>
#include <SPI.h>
#include <SD.h>  
#include <TMRpcm.h> 
#include "charLibrary.h"
#include "messages.h"

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
#define MAX_BOATS 4




// *CONSTANTS
const int DIN_1 = 12;            //DataIn pin (18)
const int CLK_1 = 11;            //Clock pin (17)
const int CS_1 = 10;           //Load pin (16)
const int DEVICES_PLAYER_1 = 2;      //duas matrizes para o player 1
//definir os pinos da matriz do player 2:
const int DIN_2 = A10; //9TESTAR?           //DataIn pin (18)
const int CLK_2 = A9; //8TESTAR?          //Clock pin (17)
const int CS_2 = A8; //7TESTAR??          //Load pin (16)
const int DEVICES_PLAYER_2 = 2;      //duas matrizes para o player 2

const long scrollDelay = 40;
const char *boatDetails[5] = {"Hidroaviao", "Submarino", "Cruzador", "Encouracado", "Porta Aviao"};   

const int bt1 = 2;     // the number of the pushbutton pin
const int bt2 = 3;
const int bt3 = 4;
const int bt4 = A5;
const int bt5 = A6;
const int bt6 = A7;
const int botoes[6] = {bt1,bt2,bt3,bt4,bt5,bt6};

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

//VARIAVEIS DO JOGO

LedControl lc_players[2] = {LedControl(DIN_1,CLK_1,CS_1,DEVICES_PLAYER_1),LedControl(DIN_2,CLK_2,CS_2,DEVICES_PLAYER_2)};
ScrollTest4MAX2 sc_players[2] = {ScrollTest4MAX2(&lc_players[0],scrollDelay),ScrollTest4MAX2(&lc_players[1],scrollDelay)};
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
int allBtState[6] = {bt1State,bt2State,bt3State,bt4State,bt5State,bt6State};

void setup() {
    Serial.begin(9600);
    delay(500);
    clearDisplays();
    
    randomSeed(analogRead(A0));  
    tmrpcm.speakerPin = SPEAKER_PIN; //
    
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
  clearDisplays();
  mainGame ();
  delay(10000);
  
}
void clearDisplays(){
  for (int i = 0; i < 2; i++){
       lc_players[i].shutdown(0,false);
       lc_players[i].clearDisplay(0);
       lc_players[i].shutdown(1,false);
       lc_players[i].clearDisplay(1);
    }
}
//################  METODOS PARA ESCOLHA DO FIRST PLAYER (RETIRADOD DE TESTRANDOM.INO) ################ 

//algoritmo para escolha de quem começa a jogar
//int chooseFirstPlayer(){
int chooseFirstPlayer(){
  long p1Number = 0L;
  long p2Number = 0L;
  int choosedplayer = 1;
  while (p1Number == p2Number) {  
    Serial.println("PLAYER_1_READY");
    sc_players[0].scrollMessage(PLAYER_1_READY);
    lc_players[0].clearDisplay(0);lc_players[0].clearDisplay(1);
    sc_players[1].scrollMessage(PLAYER_1_READY);
    lc_players[1].clearDisplay(0);lc_players[1].clearDisplay(1);
    
    bt3State = digitalRead(bt3);
    while (bt3State == HIGH) {
      generateAndShowNumber(1,&p1Number);
      bt3State = digitalRead(bt3);
    } 
    Serial.println("botao 3 pressionado");
    // mostra o numero obtido pelo p1:
    Serial.println("PLAYER_1_NUMBER_CHOOSED");
    Serial.println(p1Number);
    piscaNumeroDisplay(1, p1Number);

    Serial.println("PLAYER_2_READY");
    sc_players[0].scrollMessage(PLAYER_2_READY);
    lc_players[0].clearDisplay(0);lc_players[0].clearDisplay(1);
    sc_players[1].scrollMessage(PLAYER_2_READY);
    lc_players[1].clearDisplay(0);lc_players[1].clearDisplay(1);
    
    bt6State = digitalRead(bt6);
    while (bt6State == HIGH) {
      generateAndShowNumber(2,&p2Number);
      bt6State = digitalRead(bt6);
    }
    Serial.println("botao 6 pressionado");
    // mostra o numero obtido pelo p2:
    Serial.println("PLAYER_2_NUMBER_CHOOSED");
    Serial.println(p2Number);
    piscaNumeroDisplay(2, p2Number);

    if (p1Number == p2Number){
      Serial.println("EMPATE");
      sc_players[0].scrollMessage(EMPATE);
      sc_players[1].scrollMessage(EMPATE);
    }
  }
  if (p1Number > p2Number) {
    Serial.println("PLAYER_1_COMECA");
    sc_players[0].scrollMessage(PLAYER_1_COMECA);
    sc_players[1].scrollMessage(PLAYER_1_COMECA);
    players[0].currentPlayer = true;
    players[1].currentPlayer = false;
    choosedplayer = 1;
  } else {
    Serial.println("PLAYER_2_COMECA");
    sc_players[0].scrollMessage(PLAYER_2_COMECA);
    sc_players[1].scrollMessage(PLAYER_2_COMECA);
    players[1].currentPlayer = true;
    players[0].currentPlayer = false;
    choosedplayer = 2;
  } 
  delay(1000);
  return choosedplayer;
}

void generateAndShowNumber(int player, long *number){ 
  *number = random(10);
  mostraNumeroDisplay( 1,*number);
}

void mostraNumeroDisplay(int display, long numero){
  printLetter(numbers[((int)numero)]);
  delay(50);
}

void piscaNumeroDisplay(int display, long numero){
  for (int i = 0; i < 5; i++) {
    printLetter(numbers[((int)numero)]);
    delay(500);
    lc_players[0].clearDisplay(0);
    lc_players[1].clearDisplay(0);
    delay(500);
  }
}

void printLetter(const byte letter[7]){
  for (int i = 0; i < 7; i++) {    
      lc_players[0].setRow(0,i,letter[i]);
      lc_players[1].setRow(0,i,letter[i]);
  }
}


//################ METODOS PARA IMPRIMIR A MATRIZ DE BARCOS (RETIRADOD DE TESTLEDMATRIX2.INO) ################ 

int intPow(int x, int pow)
{
    int ret = 1;
    while ( pow != 0 )
    {
        if ( (pow & 1) == 1 )
            ret *= x;
        x *= x;
        pow >>= 1;
    }
    return ret;
}
// whatMatrix = 0 -> matriz de barco; whatMatrix = 1 -> matriz de tiro
void setLCMatrix(char matrix[DIM][DIM], LedControl lc, int whatMatrix){
  for (int row = 0; row < DIM; row++){
    int rowValue = 0;
    for (int col = 0; col < DIM ; col++){
      if((matrix[row][col] == 'B') && (whatMatrix == 0)) {
        rowValue += intPow(2, (7-col));  //calcula o valor decimal correspondente à linha.
      } else if (((matrix[row][col] == 'C') && (whatMatrix == 1)) || ((matrix[row][col] == 'E') && (whatMatrix == 1))){ 
        rowValue += intPow(2, (7-col));  //calcula o valor decimal correspondente à linha.
      }
    }
    lc.setRow(whatMatrix,row,rowValue); //ligando os leds correspondentes à linha 'row'
  } 
}

//metodo para imprimir a matriz de tiros quando o player estiver selecionando o ponto que vai atirar
void setLineShotMatrix(char matrix[DIM][DIM], LedControl lc, int row, int y){
    Serial.println("inside setLineShotMatrix");
    Serial.print("[X(Row): ");Serial.print(row);Serial.print("] [Y: ");Serial.print(y);Serial.print("]\n"); 
    int rowValue = 0;
    for (int col = 0; col < DIM ; col++){
        if ((matrix[row][col] == 'C') || (matrix[row][col] == 'E')){ 
             rowValue += intPow(2, (7-col));  //calcula o valor decimal correspondente à linha.
        }
    }
    Serial.print("rowValue antes de adcionar o valor do ponto do tiro: ");Serial.print(rowValue); Serial.print("\n"); 
    if ((matrix[row][y] != 'C') && (matrix[row][y] != 'E')){
        rowValue += intPow(2, (7-y)); //adicionando o valor do ponto y ao rowvalue
    }
    Serial.print("rowValue depois de adcionar o valor do ponto do tiro: ");Serial.print(rowValue); Serial.print("\n");
    lc.setRow(1,row,rowValue); //ligando os leds correspondentes à linha 'row'
}
//barco
void setLineBoatMatrix(char matrix[DIM][DIM], LedControl lc, int row, int y){
    //Serial.println("inside setLineBoatMatrix");
    //Serial.print("[X(Row): ");Serial.print(row);Serial.print("] [Y: ");Serial.print(y);Serial.print("]\n"); 
    int rowValue = 0;
    for (int col = 0; col < DIM ; col++){
        if (matrix[row][col] == 'B') { 
             rowValue += intPow(2, (7-col));  //calcula o valor decimal correspondente à linha.
        }
    }
    //Serial.print("rowValue antes de adcionar o valor do ponto do barco: ");Serial.print(rowValue); Serial.print("\n"); 
    if (matrix[row][y] != 'B') {
        rowValue += intPow(2, (7-y)); //adicionando o valor do ponto y ao rowvalue
    }
    //Serial.print("rowValue depois de adcionar o valor do ponto do barco: ");Serial.print(rowValue); Serial.print("\n");
    lc.setRow(0,row,rowValue); //ligando os leds correspondentes à linha 'row'
}
//incrementando barco
void setLineIncreaseBoatMatrix(char matrix[DIM][DIM], LedControl lc, int row, int y,int y1 ){
    Serial.println("inside setLineIncreaseBoatMatrix");
    Serial.print("[X(Row): ");Serial.print(row);Serial.print("] [Y: ");Serial.print(y);Serial.print("] [Y1: ");Serial.print(y1);Serial.print("]\n");
    int rowValue = 0;
    for (int col = 0; col < DIM ; col++){
        if (matrix[row][col] == 'B') { 
             rowValue += intPow(2, (7-col));  //calcula o valor decimal correspondente à linha.
        }
    }
    Serial.print("rowValue antes de adcionar o valor do ponto do barco: ");Serial.print(rowValue); Serial.print("\n"); 
    for (int colY = y; colY <= y1; colY++){
        if (matrix[row][colY] != 'B') {
            rowValue += intPow(2, (7-colY)); //adicionando o valor do ponto y ao rowvalue
        }
    }
    Serial.print("rowValue depois de adcionar o valor do ponto do barco: ");Serial.print(rowValue); Serial.print("\n");
    lc.setRow(0,row,rowValue); //ligando os leds correspondentes à linha 'row'
}




// ################ METODOS DO JOGO (RETIRADOD DE TESTLEDMATRIX2.INO) ################ 
// VAI PARA DENTRO DO LOOP
void mainGame ()
{
    playerIndex = 1;
    message = "";
    int x,y;
    startGame();
    Serial.println("\nTodos os barcos foram adcionados!  Hora de comecar o jogo!!!\n");
    
    int playerBegin = chooseFirstPlayer();
    bool gameOver = false;
    while (!gameOver) {
      for (int i = 0; i < QTD_PLAYERS; i++) {
          setLCMatrix(players[i].matrixBoats, lc_players[i], 0);
          setLCMatrix(players[i].matrixShots, lc_players[i], 1);
      }
      gameOver = attackHour(players[0].currentPlayer ? 0:1);
    }
    
}

bool attackHour(int currentPlayer){
    setLCMatrix(players[currentPlayer].matrixShots, lc_players[currentPlayer], 1);
    bool gameOver = false;
    clearButtonState();    
    int x = 0;
    int y = 0;
    int boatSize = 1;
    char direction = HORIZONTAL;
    Serial.print("dentro do attackHour. Current player: ");Serial.print(currentPlayer ? "Player 2\n":"Player 1\n");
    lc_players[currentPlayer].clearDisplay(1);
    //mostra aonde ja foi atirado!
    setLCMatrix(players[currentPlayer].matrixShots, lc_players[currentPlayer], 1);
    //lc_players[currentPlayer].setLed(1,x,y,true);
    setLineShotMatrix(players[currentPlayer].matrixShots, lc_players[currentPlayer], y, x);
    
    //solicitando x e y
    allBtState[(currentPlayer * 3) + 2] = digitalRead(botoes[(currentPlayer * 3) + 2]);
    while (allBtState[(currentPlayer * 3) + 2] == HIGH) {
        allBtState[(currentPlayer * 3) + 0] = digitalRead(botoes[(currentPlayer * 3) + 0]);  //lendo botao X do player i+1
        if (allBtState[(currentPlayer * 3) + 0] == LOW) {
            //Serial.print("Botao X do player ");Serial.print(currentPlayer + 1);Serial.print(" pressionado\n");
            if(x < 7){
                x++;
            } else {
                x = 0;
            }
            lc_players[currentPlayer].clearDisplay(1);
            setLCMatrix(players[currentPlayer].matrixShots, lc_players[currentPlayer], 1);
            //lc_players[currentPlayer].setLed(1,y,x,true);
            setLineShotMatrix(players[currentPlayer].matrixShots, lc_players[currentPlayer], y, x); 
            delay(500);  
        }
        allBtState[(currentPlayer * 3) + 1] = digitalRead(botoes[(currentPlayer * 3) + 1]);  //lendo botao Y do player i+1
        if (allBtState[(currentPlayer * 3) + 1] == LOW) {
            //Serial.print("Botao Y do player ");Serial.print(currentPlayer + 1);Serial.print(" pressionado\n");
            if(y < 7){
                y++;
            } else {
                y = 0;
            }
            lc_players[currentPlayer].clearDisplay(1);
            setLCMatrix(players[currentPlayer].matrixShots, lc_players[currentPlayer], 1);
            //lc_players[currentPlayer].setLed(1,y,x,true);
            setLineShotMatrix(players[currentPlayer].matrixShots, lc_players[currentPlayer], y, x);
            delay(500);  
        }
        allBtState[(currentPlayer * 3) + 2] = digitalRead(botoes[(currentPlayer * 3) + 2]);
    }
    delay(200);
    Serial.println("saiu! Botao ENTER do player ");Serial.print(currentPlayer+1);Serial.print(" pressionado\n");
    Serial.print("x: ");Serial.print(x);Serial.print("\n");
    Serial.print("y: ");Serial.print(y);Serial.print("\n");
  
    int currentDefender = getCurrentDefender();
    bool fired = fire(x,y, players[currentDefender].matrixBoats);
    printBoatDetails(players[currentDefender].boats[0]);
    printBoatDetails(players[currentDefender].boats[1]);
  if (fired){
    int k =  getShipIndexByGivenPoint(x, y, players[currentDefender].boats);    
    tmrpcm.play("boom2.wav");
    Serial.print("ACERTOU!!!!!!!!  Barco index: ");Serial.print(k);Serial.print("\n");    
    printMirroredMessage(ACERTOU);
    if (isSunkenShip(&players[currentDefender].boats[k], players[currentDefender].matrixBoats)){
      Serial.println("Barco AFUNDOU!!!!!!!!");
      printMirroredMessage(AFUNDOU);
      printBoatDetails(players[currentDefender].boats[k]);
      decrementBoatCount(&players[currentDefender], players[currentDefender].boats[k].size);
      players[currentDefender].availableBoats --;
      if(noMoreBoats(players[currentDefender])){
        //tmrpcm.play("game_over2.wav");
        tmrpcm.play("end2.wav");
        Serial.print("JOGO ACABOU!! Player "); Serial.print(players[0].currentPlayer ? 1:2);Serial.print(" ganhou\n");
        printMirroredMessage(JOGO_ACABOU);
        if(players[0].currentPlayer){
          printMirroredMessage(PLAYER_1_GANHOU);
        } else {
          printMirroredMessage(PLAYER_2_GANHOU);
        }
        gameOver = true;
      } else {
        Serial.print("Jogo continua, agora e a vez do player ");Serial.print(players[0].currentPlayer ? 2:1);Serial.print("\n");
        /*printMirroredMessage(JOGO_CONTINUA);
        if(players[0].currentPlayer){
          printMirroredMessage(JOGO_CONTINUA_2);
        } else {
          printMirroredMessage(JOGO_CONTINUA_1);
        }*/
      }
    } else {
      Serial.print("Barco NAO afundou!!!!!!!!\n");
      printMirroredMessage(BARCO_NAO_AFUNDOU);
      printBoatDetails(players[currentDefender].boats[k]);
      Serial.print("Jogo continua, agora e a vez do player ");Serial.print(players[0].currentPlayer ? 2:1);Serial.print("\n");
      /*if(players[0].currentPlayer){
        printMirroredMessage(JOGO_CONTINUA_2);
      } else {
        printMirroredMessage(JOGO_CONTINUA_1);
      }*/
    }
    printPlayerDetails(players[currentDefender]);
  } else{
    tmrpcm.play("6.wav");
    Serial.println("ERROU!!!!!!!!");
    printMirroredMessage(ERROU);
  }
  fillMatrixShots(x,y,players[currentPlayer].matrixShots, fired);
  printPlayerDetails(players[currentPlayer]);
  if (!gameOver){
    changeCurrentPlayer(players);
  }
  
  return gameOver;
}

void printMirroredMessage(const unsigned char message[]){
  for (int i = 0; i < QTD_PLAYERS; i++) {
    sc_players[i].scrollMessage(message);  //imprime a mensagem
  }
  clearDisplays();
  printBothMatrix();
}

void printBothMatrix(){
  for (int i = 0; i < QTD_PLAYERS; i++) {
    setLCMatrix(players[i].matrixBoats, lc_players[i], 0);//imprime novamente as matrizes de barco e tiro
    setLCMatrix(players[i].matrixShots, lc_players[i], 1);
  }
}



//testado   //ALTERAR PARA USAR OS BOTOES
void startGame(){
    for (int i = 0; i < QTD_PLAYERS; i++) {
        if (i == 0){
            sc_players[i].scrollMessage(PLAYER_1_ADD_BOAT);
            clearDisplays(); 
        } else {
            sc_players[i].scrollMessage(PLAYER_2_ADD_BOAT);
            clearDisplays();
        }
      
        initializePlayer(&players[i], &playerIndex);
        clearButtonState();    
        int x0 = 0;
        int y0 = 0;
        int x1 = 0;
        int y1 = 0;
        int boatSize = 1;
        char direction = HORIZONTAL;
        while (players[i].availableBoats < MAX_BOATS) {
            x0 = 0;
            y0 = 0;
            x1 = 0;
            y1 = 0;
            boatSize = 1;
            direction = HORIZONTAL;
            lc_players[i].clearDisplay(0);
            setLCMatrix(players[i].matrixBoats, lc_players[i], 0);//imprime novamente as matrizes de barco e tiro
            //lc_players[i].setLed(0,x0,y0,true);
            setLineBoatMatrix(players[i].matrixBoats, lc_players[i], y0, x0);
            //solicitando x0 e y0
            allBtState[(i * 3) + 2] = digitalRead(botoes[(i * 3) + 2]);
            //solicitando x0 e y0
            while (allBtState[(i * 3) + 2] == HIGH) {
                allBtState[(i*3) + 0] = digitalRead(botoes[(i*3) + 0]);  //lendo botao X do player i+1
                if (allBtState[(i*3) + 0] == LOW) {
                    //Serial.print("Botao X do player ");Serial.print(i+1);Serial.print(" pressionado\n");
                    //Serial.print("y antes: ");Serial.print(y0);Serial.print("\n");
                    if(y0 < 7){
                       y0++;
                       y1++;
                    } else {
                       y0 = 0;
                       y1=0;
                    }
                    //Serial.print("y depois: ");Serial.print(y0);Serial.print("\n");
                    lc_players[i].clearDisplay(0);
                    setLCMatrix(players[i].matrixBoats, lc_players[i], 0);//imprime novamente as matrizes de barco e tiro
                    //lc_players[i].setLed(0,x0,y0,true);
                    setLineBoatMatrix(players[i].matrixBoats, lc_players[i], x0, y0);
                    delay(500);  
                }
                allBtState[(i*3) + 1] = digitalRead(botoes[(i*3) + 1]);  //lendo botao Y do player i+1
                if (allBtState[(i*3) + 1] == LOW) {
                    //Serial.print("Botao Y do player ");Serial.print(i+1);Serial.print(" pressionado\n");
                    //Serial.print("x antes: ");Serial.print(x0);Serial.print("\n");
                    if(x0 < 7){
                        x0++;
                        x1++;
                    } else {
                       x0 = 0;
                       x1 = 0;
                    }
                    //Serial.print("x depois: ");Serial.print(x0);Serial.print("\n");
                    lc_players[i].clearDisplay(0);
                    setLCMatrix(players[i].matrixBoats, lc_players[i], 0);//imprime novamente as matrizes de barco e tiro
                    //lc_players[i].setLed(0,x0,y0,true);
                    setLineBoatMatrix(players[i].matrixBoats, lc_players[i], x0, y0);
                    delay(500);  
                }
                allBtState[(i * 3) + 2] = digitalRead(botoes[(i * 3) + 2]);
            }
            delay(500);
            Serial.print("saiu! Botao ENTER do player ");Serial.print(i+1);Serial.print(" pressionado\n");

            //pegando agora o tamanho 
            allBtState[(i * 3) + 2] = digitalRead(botoes[(i * 3) + 2]);
            direction = HORIZONTAL;
            bool changeDirectionToVertical = false;
            bool changeDirectionToHorizontal = false;
            while (allBtState[(i * 3) + 2] == HIGH) {
                allBtState[(i*3) + 0] = digitalRead(botoes[(i*3) + 0]);  //lendo botao X do player i+1
                if ((allBtState[(i*3) + 0] == LOW) && (!changeDirectionToVertical)) {
                    changeDirectionToHorizontal = true;  
                    if(y1 < 7){
                        y1++;
                        boatSize++;
                    } 
                    //lc_players[i].setLed(0,x0,y1,true);
                    //setLineBoatMatrix(players[i].matrixBoats, lc_players[i], x0, y1);
                    setLineIncreaseBoatMatrix(players[i].matrixBoats, lc_players[i], x0, y0, y1);
                    for(int line = y0; line <=y1; line++){
                      //lc_players[i].setLed(0,x0,line,true);
                      //setLCMatrix(players[i].matrixBoats, lc_players[i], 0);//imprime novamente as matrizes de barco e tiro
                    }
                    delay(500);
                }
                allBtState[(i*3) + 1] = digitalRead(botoes[(i*3) + 1]);  //lendo botao X do player i+1
                if ((allBtState[(i*3) + 1] == LOW) && (!changeDirectionToHorizontal)) {  
                    changeDirectionToVertical = true;
                    direction = VERTICAL;
                    if(x1 < 7){
                        x1++;
                        boatSize++;
                    } 
                    //lc_players[i].setLed(0,x1,y1,true);
                    setLineBoatMatrix(players[i].matrixBoats, lc_players[i], x1, y1);
                    for(int row = x0; row <= x1; row++){
                      //setLCMatrix(players[i].matrixBoats, lc_players[i], 0);//imprime novamente as matrizes de barco e tiro
                      //lc_players[i].setLed(0,row,y1,true);
                    }
                    delay(500);
                }
                allBtState[(i * 3) + 2] = digitalRead(botoes[(i * 3) + 2]);
            }
            delay(100);
            Serial.print("saiu novamente! Botao ENTER do player ");Serial.print(i+1);Serial.print(" pressionado\n");
            Serial.println("TENTANDO ADCIONAR BARCO:");
            Serial.print("x0: ");Serial.print(y0);Serial.print("\n");
            Serial.print("y0: ");Serial.print(x0);Serial.print("\n");
            Serial.print("boatsize: ");Serial.print(boatSize);Serial.print("\n");
            Serial.print("direction: ");Serial.print(direction);Serial.print("\n");
      
            delay(1000);
            bool add = addBoat(&players[i],y0,x0,boatSize,direction, &message);
            setLCMatrix(players[i].matrixBoats, lc_players[i], 0);//imprime novamente as matrizes de barco e tiro
            Serial.println("mensagem:");
            Serial.println(message);
            Serial.println("add?:");
            Serial.println(add);
            if (add){
                printPlayerDetails(players[i]);
                printBoatDetails(players[i].boats[players[i].availableBoats -1]);
            }
            setLCMatrix(players[i].matrixBoats, lc_players[i], 0);//imprime novamente as matrizes de barco e tiro   
        }  
    }
}
void clearButtonState(){
  for (int i = 0; i < 6; i++){
      allBtState[i] = 0;
  }
}
//testado
void initializePlayer(struct Player *player, int *playerIndex){

    if (*playerIndex == 1){
        player->currentPlayer = true; 
    } else {
        player->currentPlayer = false;    
    }
    resetMatrix(player->matrixBoats);
    resetMatrix(player->matrixShots);
    player->playerIndex = *playerIndex;
    player->countHidro = 0;
    player->countSub = 0;
    player->countCruz = 0;
    player->countEnc = 0;
    player->countPA = 0;
    player->countShots = 0;
    player->availableBoats = 0;
    if(*playerIndex < QTD_PLAYERS) {
        *playerIndex = *playerIndex + 1;         
    }
}

//testado
bool addBoat(struct Player *player,int x, int y, int boatSize, char direction, char **message) {
    bool add = false;
    if(player->availableBoats >= MAX_BOATS) {
        *message = "erro! Quantidade maxima de barcos atingida";
    } else if (!isValidBoatSize(boatSize)) {     
        *message = "erro! tamanho do barco invalido";
    } else if (!isBoatAvailable(*player, boatSize)) {     
        *message = "erro! Quantidade de boatDetails[size -1] atingida";
    } else if (!isValidBoatPlace(x, y, boatSize, direction, *player)) {  //checa se barco nao sobrepoe outro ou ultrapassa limites da matriz CRIAR ESSE METODO!!
        *message = "erro! Posicionamento do barco invalido";
    } else if (!verifyDirection(direction)){
        *message = "erro! Direcao invalida!";
    }
    else{   //adcionar barco        
        struct Boat boat = {x,y,boatSize,direction,false};    
        player->boats[player->availableBoats] = boat;
        player->availableBoats ++;
        incrementBoatCount(player,boatSize);
        addBoatToMatrix(player->matrixBoats, boat);
        add = true;
        *message = "barco adcionado com sucesso!";
    }
    return add; 
}

//testado
bool verifyDirection(char direction){
    if ((direction!=HORIZONTAL) && (direction!=VERTICAL)){
        return false;
    }
    return true;
}

//testado
// testa se o tamanho do barco e valido
bool isValidBoatSize(int boatSize){
    return ((boatSize > 0) && (boatSize <= 5));
}
//testado
//testa se o player ainda pode adcionar barcos e se o tamanho do barco desejado est disponivel
bool isBoatAvailable(struct Player player, int boatSize){
    bool available = false;     
    switch(boatSize) {
        case 1:
              return (player.countHidro < 2);  //se o jogador tem menos que dois hidros, returna true!
              break;
        case 2:
              return (player.countSub < 2);  //se o jogador tem menos que dois Sub, returna true!
              break;
        case 3:
              return (player.countCruz < 1);  //se o jogador nao tem nenhum Cruzeiro, returna true! 
              break;
        case 4:
              return (player.countEnc < 1);  //se o jogador nao tem nenhum encouracado, returna true! 
              break;
        case 5:
              return (player.countPA < 1);  //se o jogador nao tem nenhum porta avioes, returna true! 
              break;
    }
    return available;
}

//testado
//checa se pode adcionar um barco na posicao desejada
// checa se nao ultrapassa os limites da matriz e se nao sobrepoe outro barco
bool isValidBoatPlace(int x, int y, int boatSize, char direction , struct Player player){
    
    //checa se nao ultrapassa os limites da matriz
    if ((x < 0) || (x > 7) || (y < 0) || (y > 7)) {
        return false;
    } else if (((direction == HORIZONTAL) && (x + boatSize > 8)) || ((direction == VERTICAL) && (y + boatSize > 8))) {
        return false;
    } 
    //checa se nao sobrepoe outro barco 
    switch (direction){
        case HORIZONTAL:
            for (int i = x; i < (x + boatSize); i++){
                if(player.matrixBoats[y][i] == BARCO){  // sobrepondo um barco // if(player.matrixBoats[i][y] == 'B'){
                    return false;
                    break;    
                }
            }
            return true;
            break;
        case VERTICAL:
            for (int i = y; i < (y + boatSize); i++){
                if(player.matrixBoats[i][x] == BARCO){   //if(player.matrixBoats[x][i] == 'B'){
                    return false;   // sobrepondo um barco
                    break;    
                }
            }
            return true;
            break;
    }
    return true;
}


//testado
//Adciona na matriz, o barco. necessario fazer validacao se eh possivel adcionar antes.
void addBoatToMatrix(char matrix[8][8], struct Boat boat) {
    if (boat.direction == HORIZONTAL){
        for (int i = boat.x; i <= boat.size+boat.x-1; i++ ) {
            matrix[boat.y][i] = BARCO;
        }
    }
    else if (boat.direction == VERTICAL){
        for (int i = boat.y; i <= boat.size+boat.y-1; i++ ) {
            matrix[i][boat.x] = BARCO;
        }
    }
}

//testado
void incrementBoatCount(struct Player *player, int boatSize){
    switch(boatSize){
       case 1:
             player->countHidro ++;
             break;

       case 2:
             player->countSub ++;
             break;

       case 3:
             player->countCruz ++;
             break;

       case 4:
             player->countEnc ++;
             break;

       case 5:
             player->countPA ++;
             break;
    }
}

//testado
void decrementBoatCount(struct Player *player, int boatSize){
    switch(boatSize){
       case 1:
             player->countHidro --;
             break;

       case 2:
             player->countSub --;
             break;

       case 3:
             player->countCruz --;
             break;

       case 4:
             player->countEnc --;
             break;

       case 5:
             player->countPA --;
             break;
    }
}

//testado
void resetMatrix(char matrix[8][8]){
  for (int row = 0; row < DIM; row++) {
    for (int col = 0; col < DIM ; col++) {  
      matrix[row][col] = AGUA;
    }
  }
}

void resetAllMatrix(){
  for (int i = 0; i < QTD_PLAYERS; i++) {
      resetMatrix(players[i].matrixBoats);
      resetMatrix(players[i].matrixShots);
  }
}


//testado
void printMatrix(char matrix[8][8]){
    Serial.print("[ ");
    for (int row = 0; row < DIM; row++) {
        for (int col = 0; col < DIM ; col++) {  
            Serial.print(matrix[row][col]);
            if((row < DIM -1) || (col < DIM -1)){
                Serial.print(",");
            }
        }
        if (row < DIM -1) {
            Serial.print("\n  ");
        }
    }
    Serial.println(" ]");   
}

//testado   //ALTERAR PARA SERIAL!!
void printPlayerDetails(struct Player player){

    Serial.println("Player details: \n"); 
    Serial.print("currentPlayer: "); Serial.print(player.currentPlayer == 1 ? "Yes" : "NO");Serial.print("\n");
    Serial.print("player.playerIndex: ");Serial.print(player.playerIndex);Serial.print("\n");
    Serial.println("player.matrixBoats: "); 
    printMatrix(player.matrixBoats);
    Serial.println("player.matrixShots: "); 
    printMatrix(player.matrixShots);
    Serial.print("player.countHidro: ");Serial.print(player.countHidro);Serial.print("\n");
    Serial.print("player.countSub:");Serial.print(player.countSub);Serial.print("\n");
    Serial.print("player.countCruz:");Serial.print(player.countCruz);Serial.print("\n");
    Serial.print("player.countEnc: ");Serial.print(player.countEnc);Serial.print("\n");
    Serial.print("player.countPA: ");Serial.print(player.countPA);Serial.print("\n");
    Serial.print("player.countShots: ");Serial.print(player.countShots);Serial.print("\n");
    Serial.print("player.availableBoats: ");Serial.print(player.availableBoats);Serial.print("\n");
}

//testado //ALTERAR PARA SERIAL!!
void printBoatDetails(struct Boat boat){

    Serial.print("Boat details: \n");
    Serial.print("Position X0: ");Serial.print(boat.x);Serial.print("\n");
    Serial.print("Position Y0: ");Serial.print(boat.y);Serial.print("\n");
    Serial.print("Size: ");Serial.print(boat.size); Serial.print("\n");
    Serial.print("Tipe: ");Serial.print(boatDetails[boat.size-1]); Serial.print("\n");
    Serial.print("Direction: ");Serial.print(boat.direction == HORIZONTAL ? "Horizontal" : "Vertical");Serial.print("\n"); 
    Serial.print("Is sunken? ");Serial.print(boat.sunken == 1 ? "Yes" : "NO");   Serial.print("\n");
}

//testado
//testa se acertou ou errou o tiro
bool fire(int x, int y, char matrix[8][8]){
    bool fired = false;
    if (matrix[y][x] == 'B') {
        fired = true;
        matrix[y][x] = 'C';    //acertou o tiro!
    } else if (matrix[y][x] == 'A') {
        matrix[y][x] = 'E';    //errou o tiro!
    }
    return fired;
}

//testado
void fillMatrixShots(int x, int y, char matrix[8][8], bool fired){
    if ((matrix[y][x] == 'A') && (fired)){
      matrix[y][x] = 'C';    //acertou o tiro!
    } else if (matrix[y][x] == 'A') {
      matrix[y][x] = 'E';    //errou o tiro!
    }
}




//testado
// testa se o dado ponto x,y pertence a algum barco retornando o indice do mesmo. -1 se ponto nao pertence a nenhum barco
int getShipIndexByGivenPoint(int x, int y, struct Boat boats[7]) {
    Serial.println("dentro do getship");
    Serial.print("x: ");Serial.print(x);Serial.print("\n");
    Serial.print("y: ");Serial.print(y);Serial.print("\n");
    for (int k = 0; k < 7; k++){
        Serial.print("K: ");Serial.print(k);Serial.print("\n");
        Serial.print("boat direction: ");Serial.print(boats[k].direction);
        switch (boats[k].direction){
            case HORIZONTAL:
                Serial.print("horizontal");
                for (int i = boats[k].x; i < (boats[k].x + boats[k].size); i++){
                    if((x == i) && (y == boats[k].y)){
                      Serial.print("retornando K: ");Serial.print(k);
                        return k;
                        break;    
                    }
                }
                break;
            case VERTICAL:
                Serial.print("vertical");
                for (int i = boats[k].y; i < (boats[k].y + boats[k].size); i++){
                    if((x == boats[k].x) && (y == i)){
                        Serial.print("retornando K: ");Serial.print(k);
                        return k;
                        break;    
                    }
                }
                break;
        }
    }
    return -1;   //boat not found!
}


//testa se o navio afundou
//testado
bool isSunkenShip(struct Boat *boat, char matrix[8][8]){
    if (!boat->sunken){
        switch (boat->direction){
            case HORIZONTAL:
                for (int i = boat->x; i < (boat->x + boat->size); i++){
                    if(matrix[boat->y][i] == 'B'){
                        return false;
                        break;    
                    }
                }
                boat->sunken = true;
                return boat->sunken;
                break;
            case VERTICAL:
                for (int i = boat->y; i < (boat->y + boat->size); i++){
                    if(matrix[i][boat->x] == 'B'){;
                        return false;
                        break;    
                    }
                }
                boat->sunken = true;
                return boat->sunken;
                break;
        }
    }
    return boat->sunken;
}
//testado
bool noMoreBoats(struct Player player){
    return player.availableBoats < 1;   //todos os barcos foram afundados
}

//testado
void changeCurrentPlayer(struct Player players[2]){
    players[0].currentPlayer = !players[0].currentPlayer;
    players[1].currentPlayer = !players[1].currentPlayer;    
}

int getCurrentDefender(){
  return (players[0].currentPlayer ? 1:0);
}

