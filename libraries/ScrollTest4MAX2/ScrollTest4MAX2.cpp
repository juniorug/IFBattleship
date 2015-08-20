#include "ScrollTest4MAX2.h"

// * GLOBAL VARIABLES
unsigned long bufferLong [14] = {0};  //Buffer for scrolling text

ScrollTest4MAX2::ScrollTest4MAX2(LedControl *lc, long scrollDelay) {

  _lc = lc;  
  _scrollDelay = scrollDelay;
  for (int x = 0; x < _lc->getDeviceCount(); x++){
        _lc->shutdown(x,false);       //The MAX72XX is in power-saving mode on startup
        _lc->setIntensity(x,8);       // Set the brightness to default value
        _lc->clearDisplay(x);         // and clear the display
  }  
}

void ScrollTest4MAX2::scrollAllFonts() {
    for (int counter=0x20;counter<0x80;counter++){
        loadBufferLong(counter);
        delay(500);
    }
}

 void ScrollTest4MAX2::scrollGivenFont(int font) {
    loadBufferLong(font);
    delay(500);    
}

// Scroll Message
void ScrollTest4MAX2::scrollMessage(const unsigned char * messageString) {
    int counter = 0;
    int myChar=0;
    do {
        // read back a char 
        myChar =  pgm_read_byte_near(messageString + counter); 
        if (myChar != 0){
            loadBufferLong(myChar);
        }
        counter++;
    } 
    while (myChar != 0);
}
// Load character into scroll buffer
void ScrollTest4MAX2::loadBufferLong(int ascii){
    if (ascii >= 0x20 && ascii <=0x7f){
        for (int a=0;a<7;a++){                      // Loop 7 times for a 5x7 font
            unsigned long c = pgm_read_byte_near(font5x7 + ((ascii - 0x20) * 8) + a);     // Index into character table to get row data
            unsigned long x = bufferLong [a*2];     // Load current scroll buffer
            x = x | c;                              // OR the new character onto end of current
            bufferLong [a*2] = x;                   // Store in buffer
        }
        byte count = pgm_read_byte_near(font5x7 +((ascii - 0x20) * 8) + 7);     // Index into character table for kerning data
        for (byte x=0; x<count;x++){
            rotateBufferLong();
            printBufferLong();
            delay(_scrollDelay);
        }
    }
}
// Rotate the buffer
void ScrollTest4MAX2::rotateBufferLong(){
    for (int a=0;a<7;a++){                      // Loop 7 times for a 5x7 font
        unsigned long x = bufferLong [a*2];     // Get low buffer entry
        byte b = bitRead(x,31);                 // Copy high order bit that gets lost in rotation
        x = x<<1;                               // Rotate left one bit
        bufferLong [a*2] = x;                   // Store new low buffer
        x = bufferLong [a*2+1];                 // Get high buffer entry
        x = x<<1;                               // Rotate left one bit
        bitWrite(x,0,b);                        // Store saved bit
        bufferLong [a*2+1] = x;                 // Store new high buffer
    }
}  
// Display Buffer on LED matrix
void ScrollTest4MAX2::printBufferLong(){
  for (int a=0;a<7;a++){                    // Loop 7 times for a 5x7 font
    unsigned long x = bufferLong [a*2+1];   // Get high buffer entry
    byte y = x;                             // Mask off first character
    _lc->setRow(3,a,y);                       // Send row to relevent MAX7219 chip
    x = bufferLong [a*2];                   // Get low buffer entry
    y = (x>>24);                            // Mask off second character
    _lc->setRow(2,a,y);                       // Send row to relevent MAX7219 chip
    y = (x>>16);                            // Mask off third character
    _lc->setRow(1,a,y);                       // Send row to relevent MAX7219 chip
    y = (x>>8);                             // Mask off forth character
    _lc->setRow(0,a,y);                       // Send row to relevent MAX7219 chip
  }
}