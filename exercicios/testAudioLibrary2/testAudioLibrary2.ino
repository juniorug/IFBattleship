#include <SPI.h>
#include <SD.h>                      // need to include the SD library
#define SD_ChipSelectPin 53  //example uses hardware SS pin 53 on Mega2560
//#define SD_ChipSelectPin 10  //using digital pin 4 on arduino nano 328
#include <TMRpcm.h>           //  also need to include this library...

TMRpcm tmrpcm;   // create an object for use in this sketch
char mychar;

void setup(){

  tmrpcm.speakerPin = 11; //11 on Mega, 9 on Uno, Nano, etc

  Serial.begin(9600);//boolean SDClass::begin(uint8_t csPin, int8_t mosi, int8_t miso, int8_t sck) {
  //if (!SD.begin(SD_ChipSelectPin)) {  // see if the card is present and can be initialized:
  if (!SD.begin(53,51,50,52)) {
    Serial.println("SD fail");  
    return;   // don't do anything more if not
  }
  Serial.println("Initialization Done!");  
  tmrpcm.volume(1);
  tmrpcm.play("pacman.wav"); //the sound file "music" will play each time the arduino powers up, or is reset
  Serial.println("first sound should finish");  
}

void loop(){  
  
  if(Serial.available()){   
    Serial.println("choose a sound(o,p,r,r,w,t,y,u,i)");
    mychar = Serial.read();

    if(mychar == 'o'){ //send the letter p over the serial monitor to start playback
      Serial.println("o choosed");  
      tmrpcm.play("1.wav");
    } else if(mychar == 'r'){ //send the letter p over the serial monitor to start playback
      Serial.println("r choosed");
      tmrpcm.play("2.wav");
    } else if(mychar == 'q'){ //send the letter p over the serial monitor to start playback
      Serial.println("q choosed");
      tmrpcm.play("3.wav");
    } else if(mychar == 'p'){
      Serial.println("p choosed");
      tmrpcm.play("4.wav");
    }
    else if(mychar == 'w'){ //send the letter p over the serial monitor to start playback
      Serial.println("w choosed");
      tmrpcm.play("5.wav");
    }
    else if(mychar == 't'){ //send the letter p over the serial monitor to start playback
      Serial.println("t choosed");
      tmrpcm.play("6.wav");
    }
    else if(mychar == 'y'){ //send the letter p over the serial monitor to start playback
      Serial.println("y choosed");
      tmrpcm.play("pacman.wav");
    }
    else if(mychar == 'u'){ //send the letter p over the serial monitor to start playback
      Serial.println("u choosed");
      tmrpcm.play("output_new.wav");
    }
    else if(mychar == 'i'){ //send the letter p over the serial monitor to start playback
      Serial.println("i choosed");
      tmrpcm.play("whyhere.wav");
    }
  }

}
