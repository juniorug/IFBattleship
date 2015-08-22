#include <LedControl.h>
#include <ScrollTest4MAX2.h>

// *CONSTANTS
const int DIN = 12;            //DataIn pin (18)
const int CLK = 11;            //Clock pin (17)
const int LOAD = 10;           //Load pin (16)
const int numDevices = 1;      //Number of MAX7219 LED Driver Chips (1-8)
const long scrollDelay = 100;

const unsigned char scrollText[] PROGMEM ={
    "  MINHA BIBLIOTECA FUNCIONA   \0"};

LedControl lc = LedControl(DIN,CLK,LOAD,numDevices);
ScrollTest4MAX2 sc = ScrollTest4MAX2(&lc,scrollDelay);


void setup() {
  
}

void loop() {
  sc.scrollMessage(scrollText);
}
