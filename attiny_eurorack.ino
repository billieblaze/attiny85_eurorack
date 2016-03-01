/*
  ATTiny85 for eurorack.. 

  Pins 0/1/2 each go to an 1/8th inch jack,  each jack has a resistor and an LED for basic status monitoring
  Pins 3/4 each go to a 10k potentiometer  

  Todo: 
  * increase the robustness of analog and digital IO, currently just straight ot chip
  * 
  
*/

#include "avr/interrupt.h"

// setup them pins
//const int inputPins[] = {0};
const int outputPins[] = {1,2};
const int potPins[] = {3,4};

// variables
int inputCounter = 0;   // counter for the number of button presses
int inputState = 0;         // current state of the button
int lastInputState = 0;     // previous state of the button

byte outputState = 0;
int pulseStart = 0; 

// pot values
int clockDivider = 0; 
int stepLength = 0;



// the setup function runs once when you press reset or power the board
void setup() {

  /*for (int thisPin = 0; thisPin < sizeof(inputPins); thisPin++) {
    pinMode(inputPins[thisPin], INPUT);
  }*/

  for (int thisPin = 0; thisPin < sizeof(outputPins); thisPin++) {
    pinMode(outputPins[thisPin], OUTPUT);
  }

  GIMSK = 0b00100000;    // turns on pin change interrupts
  PCMSK = 0b00000001;    // turn on interrupts on pins PB0, PB1, &amp; PB4
  sei();        
}

// the loop function runs over and over again forever
void loop() {

  clockDivider = analogRead(potPins[0]);
  // map it to the range of the analog out:
  clockDivider = map(clockDivider, 1, 1023, 0, 32);

  stepLength = analogRead(potPins[1]);
  // map it to the range of the analog out:
  //stepLength = map(stepLength, 0, 1023, 0, 255);

  if (inputState != lastInputState) {
    if (inputState == HIGH) { // if the state has changed, increment the counter   
      
      if ( inputCounter % clockDivider == 0 ) {
        outputState = HIGH;
        inputState = LOW;
      }

      inputCounter++;
      
    }
    
    lastInputState = inputState;
    
  } else {
    if( millis() - pulseStart  >= stepLength){
      inputState = LOW;
      outputState = LOW;
    }
  }

  trigger();
  
}

void trigger( ) { 
  digitalWrite(outputPins[0], outputState);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(outputPins[1], !outputState);
}


ISR(PCINT0_vect)
{
  pulseStart = millis();
  inputState = HIGH; 
}
