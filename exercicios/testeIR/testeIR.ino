
#include <IRremote.h>

IRsend irsend;

const int bt1 = 4;     // the number of the pushbutton pin
const int bt2 = 5;
const int bt3 = 6;
const int bt4 = 7;
const int bt5 = 8;
const int bt6 = 9;
const int botoes[6] = {bt1,bt2,bt3,bt4,bt5,bt6};


int bt1State = 0;         // variable for reading the pushbutton status
int bt2State = 0;         // variable for reading the pushbutton status
int bt3State = 0;         // variable for reading the pushbutton status
int bt4State = 0;         // variable for reading the pushbutton status
int bt5State = 0;         // variable for reading the pushbutton status
int bt6State = 0;         // variable for reading the pushbutton status
int allBtState[6] = {bt1State,bt2State,bt3State,bt4State,bt5State,bt6State};


void setup() {
  Serial.begin(9600); 
  Serial.println("inicio");
  pinMode(2, OUTPUT);
  for(int i=0; i<6;i++){
      pinMode(botoes[i], INPUT);
      allBtState[i] = 0;
    }

}

void loop() {
 for(int i=0; i<6;i++){
    allBtState[i] = digitalRead(botoes[i]);
    if (allBtState[i] == LOW) {
        for (int j = 0; j < 3; j++) {
            if ( i == 0){
                 irsend.sendNEC(0xC308F7, 32);  //ok
            } else if ( i == 1){
                 irsend.sendNEC(0xC38877, 32); //ok
            } else if ( i == 2){
                 irsend.sendNEC(0x00000000, 32);
            } else if ( i == 3){
                 irsend.sendNEC(0xC3C837, 32); //ok
            } else if ( i == 4){
                 irsend.sendNEC(0xffffffff, 32);
            } else if ( i == 5){
                 irsend.sendNEC(0xC3B04F, 32); //ok
            } 
          





          
//            if ( i == 0){
//                 irsend.sendSony(0xa90, 12); // Sony TV power code
//            } else if ( i == 1){
//                 irsend.sendSony(0x68B92, 12); // Sony TV power code
//            } else if ( i == 2){
//                 irsend.sendSony(0xa8bca, 12); // Sony TV power code
//            } else if ( i == 3){
//                 irsend.sendSony(0x74bca, 12); // Sony TV power code
//            } else if ( i == 4){
//                 irsend.sendSony(0x00002422, 15);// Sony TV power code
//            } else if ( i == 5){
//                 irsend.sendSony(0x00000122, 15); // Sony TV power code
//            } else if ( i == 6){
//                 irsend.sendSony(0x00003026, 15); // Sony TV power code
//            }
//            if (( i % 2) == 0){
//                 irsend.sendSony(0xa90, 12); // Sony TV power code
//            } else {
//                 irsend.sendSony(0x68B92, 12); // Sony TV power code
//            } 
            delay(40);          
        }
        Serial.print("Botao ");Serial.print(i+1);Serial.print(" pressionado \n");
//        digitalWrite(2, HIGH);   // turn the LED on (HIGH is the voltage level)
//        Serial.println("rodando");
//        delay(100);              // wait for a second
//       digitalWrite(2, LOW);    // turn the LED off by making the voltage LOW
//       delay(100);  
    }
 }
}
