/*
button hookup guide
*/

int led = 13;

// HOW TO HOOKUP BUTTON
const int buttonPin = 3; // Connected to NO1 pin: Normally Open Pin
const int buttonLEDPin = 9; // Connected to the + LED Pin
// Connect both C1: Common Pin and - LED Pin on button to GND
// Sparkfun says you don't need a resistor, already included.

int buttonState = LOW;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT); 
  pinMode(buttonPin ,INPUT_PULLUP);
  pinMode(buttonLEDPin, OUTPUT);                                 
}

// the loop routine runs over and over again forever:
void loop() {
  buttonState = digitalRead(buttonPin);
  
  if(buttonState == LOW){
  digitalWrite(led, HIGH);
  digitalWrite(buttonLEDPin,HIGH);
}
  else{
  digitalWrite(led,LOW);
  digitalWrite(buttonLEDPin,LOW);
  }

}
