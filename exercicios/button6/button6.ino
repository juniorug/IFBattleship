/*
  Button

 Turns on and off a light emitting diode(LED) connected to digital
 pin 13, when pressing a pushbutton attached to pin 2.


 The circuit:
 * LED attached from pin 13 to ground
 * pushbutton attached to pin 2 from +5V
 * 10K resistor attached to pin 2 from ground

 * Note: on most Arduinos there is already an LED on the board
 attached to pin 13.


 created 2005
 by DojoDave <http://www.0j0.org>
 modified 30 Aug 2011
 by Tom Igoe

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/Button
 */

// constants won't change. They're used here to
// set pin numbers:
const int b1 = 2;     // the number of the pushbutton pin
const int b2 = 3;
const int b3 = 4;
const int b4 = 5;
const int b5 = A7;
const int b6 = A6;
const int ledPin =  13;      // the number of the LED pin

// variables will change:
int b1State = 0;         // variable for reading the pushbutton status
int b2State = 0;         // variable for reading the pushbutton status
int b3State = 0;         // variable for reading the pushbutton status
int b4State = 0;         // variable for reading the pushbutton status
int b5State = 0;         // variable for reading the pushbutton status
int b6State = 0;         // variable for reading the pushbutton status

void setup() {
  Serial.begin(9600);
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(b1, INPUT);
  pinMode(b2, INPUT);
  pinMode(b3, INPUT);
  pinMode(b4, INPUT);
  pinMode(b5, INPUT);
  pinMode(b6, INPUT);
}

void loop() {
  // read the state of the pushbutton value:
  b1State = digitalRead(b1);
  b2State = digitalRead(b2);
  b3State = digitalRead(b3);
  b4State = digitalRead(b4);
  b5State = digitalRead(b5);
  b6State = digitalRead(b6);

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (b1State == LOW) {
    // turn LED on:
    Serial.println("Botao 1 pressionado");
    digitalWrite(ledPin, HIGH);
    delay(500);
    digitalWrite(ledPin, LOW);
  }
  if (b2State == LOW) {
    // turn LED on:
    Serial.println("Botao 2 pressionado");
    digitalWrite(ledPin, HIGH);
    delay(500);
    digitalWrite(ledPin, LOW);
  }
  if (b3State == LOW) {
    // turn LED on:
    Serial.println("Botao 3 pressionado");
    digitalWrite(ledPin, HIGH);
    delay(500);
    digitalWrite(ledPin, LOW);
  }
  if (b4State == LOW) {
    // turn LED on:
    Serial.println("Botao 4 pressionado");
    digitalWrite(ledPin, HIGH);
    delay(500);
    digitalWrite(ledPin, LOW);
  }
  if (b5State == LOW) {
    // turn LED on:
    Serial.println("Botao 5 pressionado");
    digitalWrite(ledPin, HIGH);
    delay(500);
    digitalWrite(ledPin, LOW);
  }
  if (b6State == LOW) {
    // turn LED on:
    Serial.println("Botao 6 pressionado");
    digitalWrite(ledPin, HIGH);
    delay(500);
    digitalWrite(ledPin, LOW);
  }
}
