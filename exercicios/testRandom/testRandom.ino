#include "LedControl.h"
#include "charLibrary.h"
#define DIM 8

LedControl lc = LedControl(12,11,10,1);


const byte numbers[10][7] =  { {B01110000,B10001000,B10011000,B10101000,B11001000,B10001000,B01110000},
                            {B01000000,B11000000,B01000000,B01000000,B01000000,B01000000,B11100000},
                            {B01110000,B10001000,B00001000,B00010000,B00100000,B01000000,B11111000},
                            {B11111000,B00010000,B00100000,B00010000,B00001000,B10001000,B01110000},
                            {B00010000,B00110000,B01010000,B10010000,B11111000,B00010000,B00010000},
                            {B11111000,B10000000,B11110000,B00001000,B00001000,B10001000,B01110000},
                            {B00110000,B01000000,B10000000,B11110000,B10001000,B10001000,B01110000},
                            {B11111000,B10001000,B00001000,B00010000,B00100000,B00100000,B00100000},
                            {B01110000,B10001000,B10001000,B01110000,B10001000,B10001000,B01110000},
                            {B01110000,B10001000,B10001000,B01111000,B00001000,B00010000,B01100000}
                        };

void setup() {
   lc.shutdown(0,false);
   lc.clearDisplay(0);
   Serial.begin(9600);
}

void loop() {
  chooseFirstPlayer();
}





//algoritmo para escolha de quem começa a jogar
//int chooseFirstPlayer(){
void chooseFirstPlayer(){
  long p1Number = 0L;
  long p2Number = 0L;

  while (p1Number == p2Number) {
    Serial.println("player 1 ready?");
    //while (digitalRead(buttonPlayer1) == LOW) {
    for (int i = 0; i < 10; i++){
      //mostraNumeroDisplay(1,p1Number);
      generateAndShowNumber(1,&p1Number);
    }
    // mostra o numero obtido pelo p1:
    piscaNumeroDisplay(1, p1Number);

    Serial.println("player 2 ready?");
    //while (digitalRead(buttonPlayer2) == LOW) {
    for (int i = 0; i < 10; i++){
      //mostraNumeroDisplay(2,p2Number);
      generateAndShowNumber(2,&p1Number);
    }
    // mostra o numero obtido pelo p2:
    piscaNumeroDisplay(2, p2Number);

    if (p1Number == p2Number){
      Serial.println("Empate!");
    }
  }
  if (p1Number > p2Number) {
    Serial.println("player 1 comeca!");
   // p1.currentPlayer = true;
   // p2.currentPlayer = false;
  } else {
    Serial.println("player 2 comeca!");
   // p2.currentPlayer = true;
    //p1.currentPlayer = false;
  } 
}

void generateAndShowNumber(int player, long *number){
  randomSeed(analogRead(0));
  *number = random(10);
  //MOSTRA O NUMERO NO DISPLAY:
  //mostraNumeroDisplay(player, number);
  Serial.println("random: ");
  Serial.println(*number);
  mostraNumeroDisplay( 1,*number);
  delay(500);
}

void mostraNumeroDisplay(int display, long numero){
  //PrintDisplay(display,numero);
  printLetter(numbers[((int)numero)]);
  delay(100);
  lc.clearDisplay(0);
}
void piscaNumeroDisplay(int display, long numero){
  for (int i = 0; i < 5; i++) {
    //PrintDisplay(display,numero);
    printLetter(numbers[((int)numero)]);
    delay(1000);
    lc.clearDisplay(0);
  }
}

void printLetter(const byte letter[7]){
  for (int i = 0; i < 7; i++) {
      lc.setRow(0,i,letter[i]);
  }
}

