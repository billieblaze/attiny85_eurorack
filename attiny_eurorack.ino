/*
  ATTiny85 for eurorack.. 

  Pins 0/1/2 each go to an 1/8th inch jack,  each jack has a resistor and an LED for basic status monitoring
  Pins 3/4 each go to a 10k potentiometer  

  Todo: 
  * increase the robustness of analog and digital IO, currently just straight ot chip
  * 
  
*/

// setup them pins
const int inputPins[] = {0};
const int outputPins[] = {1,2};
const int potPins[] = {3,4};

// variables
int inputCounter = 0;   // counter for the number of button presses
int inputState = 0;         // current state of the button
int lastInputState = 0;     // previous state of the button


byte outputState = 0;

// the setup function runs once when you press reset or power the board
void setup() {

  for (int thisPin = 0; thisPin < sizeof(inputPins); thisPin++) {
    pinMode(inputPins[thisPin], INPUT);
  }

  for (int thisPin = 0; thisPin < sizeof(outputPins); thisPin++) {
    pinMode(outputPins[thisPin], OUTPUT);
  }
  
}

// the loop function runs over and over again forever
void loop() {
  
  inputState = digitalRead(inputPins[0]);
  if (inputState != lastInputState) {
    if (inputState == HIGH) { // if the state has changed, increment the counter
      inputCounter++;
    } else {
      // if the current state is LOW then the button wend from on to off:
      
    }
  }
  // save the current state as the last state,
  //for next time through the loop
  lastInputState = inputState;


  // turns on the LED every four button pushes by checking the modulo of the button push counter.
  // the modulo function gives you the remainder of the division of two numbers:
  if (inputCounter % 4 == 0) {
    trigger(1);
  } else {
    trigger(2);
  }
  
}

void trigger( int pin ) { 
  digitalWrite(pin, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(100);              // wait for a second
  digitalWrite(pin, LOW);    // turn the LED off by making the voltage LOW
  delay(100);  
}
