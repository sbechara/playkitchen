// So the code is a little janky but it works. If you want to change the colors that should be pretty easy to do.

#include "FastLED.h"

// ***** LUMENATI VARIABLES *******
//Number of LEDs
#define NUM_LEDS_STOVE 12 // stove
#define NUM_LEDS_OVEN 16 // oven

//Define our clock and data lines for the lumenati strip
#define DATA_PIN_STOVE 13
#define CLOCK_PIN_STOVE 12
#define DATA_PIN_OVEN 11
#define CLOCK_PIN_OVEN 10

#define WAIT 20
#define MAXBRIGHTNESS 100
#define MINBRIGHTNESS 10

//Create the LED array for the strip
CRGB ledsStove[NUM_LEDS_STOVE];
CRGB ledsOven[NUM_LEDS_OVEN];

// ******** Cycle Variables *********
const byte interruptPinStove = 3;
const byte interruptPinOven = 2;
int stoveButtonState = LOW;
int ovenButtonState = LOW;
int modButtonCycleStove = 0;
int modButtonCycleOven = 0;

const int maxCycles = 4; // same for both oven and stove

// Interrupt debounce variable
static unsigned long last_interrupt_time = 0;

// ************ Cool Button Variables ********
// Connect both C1: Common Pin and - LED Pin on button to GND
// Sparkfun says you don't need a resistor, already included.
const int stoveButtonPin = 8; // Connected to NO1 pin: Normally Open Pin
const int stoveButtonLEDPin = 9; // Connected to the + LED Pin
const int ovenButtonPin = 6;
const int ovenButtonLEDPin = 7;


void setup() {

  //Tell FastLED what we're using. Note "BGR" where you might normally find "RGB".
  //This is just to rearrange the order to make all the colors work right.
  FastLED.addLeds<APA102, DATA_PIN_STOVE, CLOCK_PIN_STOVE, BGR>(ledsStove, NUM_LEDS_STOVE);
  FastLED.addLeds<APA102, DATA_PIN_OVEN, CLOCK_PIN_OVEN, BGR>(ledsOven, NUM_LEDS_OVEN);

  //Set global brightness
  FastLED.setBrightness(0);

  pinMode(interruptPinStove, INPUT_PULLUP);
  pinMode(interruptPinOven, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPinStove), cycleStove, RISING);
  attachInterrupt(digitalPinToInterrupt(interruptPinOven), cycleOven, RISING);

  pinMode(ovenButtonPin, INPUT_PULLUP);
  pinMode(ovenButtonLEDPin, OUTPUT);
  pinMode(stoveButtonPin, INPUT_PULLUP);
  pinMode(stoveButtonLEDPin, OUTPUT);

  Serial.begin(9600);
}

void loop() {

  stoveButtonState = digitalRead(stoveButtonPin);
  ovenButtonState = digitalRead(ovenButtonPin);

  // **** STOVE MAIN LOOP ****
  if (stoveButtonState == LOW) {
    digitalWrite(stoveButtonLEDPin, HIGH); // turn on the button LED
    if (modButtonCycleStove == 0)
    {
      glowRed(NUM_LEDS_STOVE, ledsStove);
    }
    else if (modButtonCycleStove == 1) {
      glowGreen(NUM_LEDS_STOVE, ledsStove);
    }
    else if (modButtonCycleStove == 2) {
      glowPink(NUM_LEDS_STOVE, ledsStove);
    }
    else {
      glowBlue(NUM_LEDS_STOVE, ledsStove);
    }
    //delay(WAIT);

  }
  else {
    digitalWrite(stoveButtonLEDPin, LOW);
    // turn all LEDs off
    for (int led = 0; led < NUM_LEDS_STOVE; led++) {
      ledsStove[led] = CRGB::Black;
    }
    FastLED.show();
  }

  // **** OVEN MAIN LOOP ****
  if (ovenButtonState == LOW) {
    digitalWrite(ovenButtonLEDPin, HIGH); // turn on the button LED
    if (modButtonCycleOven == 0)
    {
      glowRed(NUM_LEDS_OVEN, ledsOven);
    }
    else if (modButtonCycleOven == 1) {
      glowGreen(NUM_LEDS_OVEN, ledsOven);
    }
    else if (modButtonCycleOven == 2) {
      glowPink(NUM_LEDS_OVEN, ledsOven);
    }
    else {
      glowBlue(NUM_LEDS_OVEN, ledsOven);
    }
    //delay(WAIT);

  }
  else {
    digitalWrite(ovenButtonLEDPin, LOW);
    // turn all LEDs off
    for (int led = 0; led < NUM_LEDS_OVEN; led++) {
      ledsOven[led] = CRGB::Black;
    }
    FastLED.show();
  }

}

// ******** SUB FUNCTIONS ***************

// Interrupt function to change the "cycle" STOVE
void cycleStove() {
  unsigned long interrupt_time = millis();
  Serial.println("Stove Button Press Registered");
  if (interrupt_time - last_interrupt_time > 500)
  {
    Serial.println(modButtonCycleStove);
    if (modButtonCycleStove < maxCycles - 1) {
      modButtonCycleStove++;
    }
    else {
      modButtonCycleStove = 0;
    }
    // so it instantly changes color when pressed. Seems janky but I kinda like the flash of color even if "main" button is not depressed.
    if (modButtonCycleStove == 0)
    {
      glowRed(NUM_LEDS_STOVE, ledsStove);
    }
    else if (modButtonCycleStove == 1) {
      glowGreen(NUM_LEDS_STOVE, ledsStove);
    }
    else if (modButtonCycleStove == 2) {
      glowPink(NUM_LEDS_STOVE, ledsStove);
    }
    else {
      glowBlue(NUM_LEDS_STOVE, ledsStove);
    }
  }
  else {
    Serial.println("Multiple presses");
  }
  last_interrupt_time = interrupt_time;
  Serial.println(modButtonCycleStove); //debugging
}

// Interrupt function to change the "cycle" OVEN
void cycleOven() {
  unsigned long interrupt_time = millis();
  Serial.println("Oven Button Press Registered");
  if (interrupt_time - last_interrupt_time > 500)
  {
    Serial.println(modButtonCycleOven);
    if (modButtonCycleOven < maxCycles - 1) {
      modButtonCycleOven++;
    }
    else {
      modButtonCycleOven = 0;
    }
    if (modButtonCycleOven == 0)
    {
      glowRed(NUM_LEDS_OVEN, ledsOven);
    }
    else if (modButtonCycleOven == 1) {
      glowGreen(NUM_LEDS_OVEN, ledsOven);
    }
    else if (modButtonCycleOven == 2) {
      glowPink(NUM_LEDS_OVEN, ledsOven);
    }
    else {
      glowBlue(NUM_LEDS_OVEN, ledsOven);
    }
  }
  else {
    Serial.println("Multiple presses");
  }
  last_interrupt_time = interrupt_time;
  Serial.println(modButtonCycleOven);
}



// ***** COLOR GLOWING FUNCTIONS BELOW ********

// glow red function
void glowRed(int numLEDS, CRGB ledArray[]) {
  // turn all LEDs on
  //Set global brightness
  FastLED.setBrightness(0);

  for (int led = 0; led < numLEDS; led++) {
    ledArray[led] = CRGB::Maroon;
  }
  FastLED.show();

  // glowing UP
  for (int t = MINBRIGHTNESS; t < MAXBRIGHTNESS; t++) {
    FastLED.setBrightness(t);
    FastLED.show();
    delay(WAIT);
  }

  // glowing DOWN
  for (int t = MAXBRIGHTNESS; t > MINBRIGHTNESS; t--) {
    FastLED.setBrightness(t);
    FastLED.show();
    delay(WAIT);
  }
}

// glow pink function
void glowPink(int numLEDS, CRGB ledArray[]) {
  // turn all LEDs on
  //Set global brightness
  FastLED.setBrightness(0);

  for (int led = 0; led < numLEDS; led++) {
    ledArray[led] = CRGB::Pink;
  }
  FastLED.show();

  // glowing UP
  for (int t = MINBRIGHTNESS; t < MAXBRIGHTNESS; t++) {
    FastLED.setBrightness(t);
    FastLED.show();
    delay(WAIT);
  }

  // glowing DOWN
  for (int t = MAXBRIGHTNESS; t > MINBRIGHTNESS; t--) {
    FastLED.setBrightness(t);
    FastLED.show();
    delay(WAIT);
  }
}

// glow blue function
void glowBlue(int numLEDS, CRGB ledArray[]) {
  // turn all LEDs on
  //Set global brightness
  FastLED.setBrightness(0);

  for (int led = 0; led < numLEDS; led++) {
    ledArray[led] = CRGB::DeepSkyBlue;
  }
  FastLED.show();

  // glowing UP
  for (int t = MINBRIGHTNESS; t < MAXBRIGHTNESS; t++) {
    FastLED.setBrightness(t);
    FastLED.show();
    delay(WAIT);
  }

  // glowing DOWN
  for (int t = MAXBRIGHTNESS; t > MINBRIGHTNESS; t--) {
    FastLED.setBrightness(t);
    FastLED.show();
    delay(WAIT);
  }
}

// glow green function
void glowGreen(int numLEDS, CRGB ledArray[]) {
  // turn all LEDs on
  //Set global brightness
  FastLED.setBrightness(0);

  for (int led = 0; led < numLEDS; led++) {
    ledArray[led] = CRGB::Green;
  }
  FastLED.show();

  // glowing UP
  for (int t = MINBRIGHTNESS; t < MAXBRIGHTNESS; t++) {
    FastLED.setBrightness(t);
    FastLED.show();
    delay(WAIT);
  }

  // glowing DOWN
  for (int t = MAXBRIGHTNESS; t > MINBRIGHTNESS; t--) {
    FastLED.setBrightness(t);
    FastLED.show();
    delay(WAIT);
  }
}
