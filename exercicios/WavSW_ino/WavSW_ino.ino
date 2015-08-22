#include <SPI.h>
#include <SD.h>                      // need to include the SD library
#define SD_ChipSelectPin 4  //using digital pin 4 on arduino nano 328
#include <TMRpcm.h>           //  also need to include this library...
 
TMRpcm tmrpcm;   // create an object for use in this sketch
 int SW1; 
 /*int SW2;
 int SW3;
 int SW4;*/
void setup(){
 Serial.begin(9600); 
 pinMode(A0,INPUT);  //Define A0 as digital input.
 pinMode(15,INPUT);  //Define A1 as digital input. 
 pinMode(16,INPUT);  //Define A2 as digital input.
 pinMode(17,INPUT);  //Define A3 as digital input.
 
  tmrpcm.speakerPin = 11; //11 on Mega, 9 on Uno, Nano, etc
  //pinMode(10, OUTPUT);
  pinMode(53, OUTPUT);
  while (!SD.begin(SD_ChipSelectPin)) {  // see if the card is present and can be initialized:
     Serial.println("initialization failed. Things to check:");
     delay(500);
  //return;   // don't do anything more if not
  }
  Serial.println("initialization DONE!");
 //tmrpcm.volume(1023);
 Serial.println("wavInfo: ");
 //Serial.println(tmrpcm.wavInfo("pacman.wav"));
 //tmrpcm.play("pacman.wav"); //the sound file "1" will play each time the arduino powers up, or is reset
}
 
void loop(){  
 SW1=digitalRead(A0); 
 /*SW2=digitalRead(15);
 SW3=digitalRead(16);
 SW4=digitalRead(17);*/
  
     if (SW1 == LOW) { //if SW1 pressed then play file "6.wav"
      tmrpcm.play("pacman.wav");
      Serial.println("LOW");
      delay(5000);
    }/* else if(SW2 == LOW){ //if SW2 pressed then play file "4.wav"
    }
      tmrpcm.play("4.wav");
    } else if(SW3 == LOW){ //if SW3 pressed then play file "5.wav"
      tmrpcm.play("5.wav");
    } else if(SW4 == LOW){  //if SW4 pressed then play file "3.wav"
      tmrpcm.play("3.wav");
    }*/
  
}
