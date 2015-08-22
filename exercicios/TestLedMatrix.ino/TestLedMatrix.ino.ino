#include "LedControl.h"
int dim =  8;
int numRows =  8;
int numCols =  8;
char matrix[8][8] = { \
            { 'A','A','A','A','A','A','A','A' }, \
            { 'A','A','A','A','A','A','A','A' },\
            { 'A','A','A','A','A','A','A','A' },\
            { 'A','A','A','A','A','A','A','A' },\
            { 'A','A','A','A','A','A','A','A' },\
            { 'A','A','A','A','A','A','A','A' },\
            { 'A','A','A','A','A','A','A','A' },\
            { 'A','A','A','A','A','A','A','A' }\
          };

LedControl lc = LedControl(12,11,10,1);


void setup(){
  Serial.begin(9600);
  lc.shutdown(0,false);
  lc.clearDisplay(0);
  Serial.println("invocando o lcmatrix: ");   
}

void clearMatrix(char matrix[8][8]){
  for (int row = 0; row < numRows; row++) {
    for (int col = 0; col < numCols ; col++) {  
      matrix[row][col] = 'A';
    }
  }
  lc.clearDisplay(0);
}
void loop(){
//  acendeTodosUmPorUm( numRows,  numCols, matrix);
//  apagaTodosUmPorUm(numRows,  numCols, matrix);
//  acendeUmApagaAnterior(numRows,  numCols, matrix);
    //acende(numRows,  numCols);
   // acendeRowValue(numRows,  numCols);
     
   setLCMatrix(numRows,  numCols, matrix);
   delay(1000);
   lc.clearDisplay(0);
}

//int numRows, int numCols, char matrix[numRows][numCols]

void acendeTodosUmPorUm(int numRows, int numCols, char matrix[8][8]) {

  for (int row = 0; row < numRows; row++) {
    for (int col = 0; col < numCols ; col++) {  
      matrix[row][col] = 'B';
      setLCMatrix(numRows, numCols, matrix);
      delay(500);
    }
  }
}

void apagaTodosUmPorUm(int numRows, int numCols, char matrix[8][8]) {

  for (int row = 0; row < numRows; row++) {
    for (int col = 0; col < numCols ; col++) {  
      matrix[row][col] = 'A';
      setLCMatrix(numRows, numCols, matrix);
      delay(500);
    }
  }
}

void acendeUmApagaAnterior(int numRows, int numCols, char matrix[8][8]) {

  for (int row = 0; row < numRows; row++) {
    for (int col = 0; col < numCols ; col++) {  
      matrix[row][col] = 'B';
      if(col > 0){
        matrix[row][col -1] = 'A';
      } else if(row > 0) {
        matrix[row -1][col] = 'A';
      }
      setLCMatrix(numRows, numCols, matrix);
      delay(500);
    }
  }
  lc.clearDisplay(0);
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
void setLCMatrix(int numRows, int numCols, char matrix[8][8]){
  //delay(5000);
  
  for (int row = 0; row < numRows; row++){
   // Serial.print("row: ");
    //Serial.println(row);   
    //delay(5000);
    int rowValue = 0;
    //Serial.print("rowValue at the begin: ");
    //Serial.println(rowValue);
    //delay(5000);
    for (int col = 0; col < numCols ; col++){
     // Serial.print("col: ");
     // Serial.println(col );  
      
     // delay(5000);
      if(matrix[row][col] == 'A') {
      //  Serial.print("[got an 'A' at (x,y): ");
      //  Serial.print(row);Serial.print(" ");Serial.println(col);
      //  Serial.print("pow(2, (7-col)): ");
      //  Serial.println(intPow(2, (7-col))); 
        //delay(5000);
        //Serial.print("rowValue before sum: ");
       // Serial.println(rowValue);
        rowValue += intPow(2, (7-col));  //calcula o valor decimal correspondente à linha.
        Serial.print("rowValue after sum: ");
        Serial.println(rowValue);
        //delay(5000);
      }
    }
    lc.setRow(0,row,rowValue); //ligando os leds correspondentes à linha 'row'
    delay(1000);
  } 
}

//OK
void acende(int numRows, int numCols) {

  for (int row = 0; row < numRows; row++) {
    for (int col = 0; col < numCols ; col++) {  
      lc.setLed(0,col,row,true); 
      delay(100); 
    }
  }
  lc.clearDisplay(0);
}

//OK
void acendeRowValue(int numRows, int numCols) {
  
  for (int row = 0; row < numRows; row++) {
    int rowValue = 0;
    for (int col = 0; col < numCols ; col++) {  
      rowValue += pow(2, (7-col)); 
      lc.setLed(0,row,col,true); 
      delay(100); 
    }
    lc.clearDisplay(0);
    delay(100);
  }
  
}
