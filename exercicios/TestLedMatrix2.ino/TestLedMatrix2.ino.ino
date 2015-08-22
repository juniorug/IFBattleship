#include "LedControl.h"
#define DIM 8

int dim = 8;
char matrix[8][8] = { { 'A','A','A','A','A','A','A','A' },
            { 'A','A','A','A','A','A','A','A' },  
            { 'A','A','A','A','A','A','A','A' },
            { 'A','A','A','A','A','A','A','A' },
            { 'A','A','A','A','A','A','A','A' },
            { 'A','A','A','A','A','A','A','A' },
            { 'A','A','A','A','A','A','A','A' },
            { 'A','A','A','A','A','A','A','A' }
          };

LedControl lc = LedControl(12,11,10,1);


void setup(){
  lc.shutdown(0,false);
  lc.clearDisplay(0);
  Serial.begin(9600);
}

void loop(){
  printMatrix();
  acendeTodosUmPorUm();
  printMatrix();
  apagaTodosUmPorUm();
  printMatrix();
  acendeUmApagaAnterior();
  clearMatrix();
  printMatrix();
  delay(100);
}



void acendeTodosUmPorUm() {

  for (int row = 0; row < DIM; row++) {
    for (int col = 0; col < DIM ; col++) {  
      matrix[row][col] = 'B';
      setLCMatrix();
      delay(100);
    }
  }
}

void apagaTodosUmPorUm() {

  for (int row = 0; row < DIM; row++) {
    for (int col = 0; col < DIM ; col++) {  
      matrix[row][col] = 'A';
      setLCMatrix();
      delay(100);
    }
  }
}

void acendeUmApagaAnterior() {

  for (int row = 0; row < DIM; row++) {
    for (int col = 0; col < DIM ; col++) {  
      matrix[row][col] = 'B';
      if(col > 0){
          matrix[row][col -1] = 'A';
      } else if((col == 0) && (row > 0)) {
          matrix[row -1][DIM - 1] = 'A';
      }
      setLCMatrix();
      delay(100);
    }
  }
  lc.clearDisplay(0);
}

void setLCMatrix(){
  for (int row = 0; row < DIM; row++){
    int rowValue = 0;
    for (int col = 0; col < DIM ; col++){
      if(matrix[row][col] == 'B') {
        rowValue += intPow(2, (7-col));  //calcula o valor decimal correspondente à linha.
      }
    }
    lc.setRow(0,row,rowValue); //ligando os leds correspondentes à linha 'row'
  } 
}


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

void clearMatrix(){
  for (int row = 0; row < DIM; row++) {
    for (int col = 0; col < DIM ; col++) {  
      matrix[row][col] = 'A';
    }
  }
  lc.clearDisplay(0);
}


void printMatrix(){
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

