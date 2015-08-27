/*
 * IRremote: IRrecvDemo - demonstrates receiving IR codes with IRrecv
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */

#include <IRremote.h>

int RECV_PIN = 3;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, DEC);
    irrecv.resume(); // Receive the next value

    if (results.value == 2390193129){
      Serial.println("Botao 1");
    } else if (results.value == 518768101){
      Serial.println("Botao 2");
    } else if(results.value == 2537436489){
      Serial.println("Botao 4");
    } else if(results.value == 4059454913){
      Serial.println("Botao 6");
    } else {
      Serial.println("undefined");
    }
  }
  delay(100);
  
}
