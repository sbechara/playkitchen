#include "FastLED.h"

// ***** LUMENATI VARIABLES *******
//Number of LEDs
#define NUM_LEDS_STRIP 16

//Define our clock and data lines for the lumenati strip
#define DATA_PIN_STRIP 7
#define CLOCK_PIN_STRIP 6

#define WAIT 20
#define MAXBRIGHTNESS 100
#define MINBRIGHTNESS 10

//Create the LED array for the strip
CRGB leds[NUM_LEDS_STRIP];

// ******** Cycle Variables *********
const byte interruptPin = 3;
volatile byte state = LOW;
int modButtonCycle = 0;
const int maxCycles = 4;

// Interrupt debounce variable
static unsigned long last_interrupt_time = 0;

// ************ Cool Button Variables ********
const int ovenButtonPin = 9; // Connected to NO1 pin: Normally Open Pin
const int ovenButtonLEDPin = 10; // Connected to the + LED Pin
// Connect both C1: Common Pin and - LED Pin on button to GND
// Sparkfun says you don't need a resistor, already included.

int ovenButtonState = LOW;

void setup() {

  //Tell FastLED what we're using. Note "BGR" where you might normally find "RGB".
  //This is just to rearrange the order to make all the colors work right.
  FastLED.addLeds<APA102, DATA_PIN_STRIP, CLOCK_PIN_STRIP, BGR>(leds, NUM_LEDS_STRIP);

  //Set global brightness
  FastLED.setBrightness(0);

  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), cycle, RISING);

  pinMode(ovenButtonPin, INPUT_PULLUP);
  pinMode(ovenButtonLEDPin, OUTPUT);

  Serial.begin(9600);
}

void loop() {

  ovenButtonState = digitalRead(ovenButtonPin);
  if (ovenButtonState == LOW) {
    digitalWrite(ovenButtonLEDPin, HIGH); // turn on the button LED
    if (modButtonCycle == 0)
    {
      glowRed(MINBRIGHTNESS, MAXBRIGHTNESS);
    }
    else if (modButtonCycle == 1) {
      glowGreen(MINBRIGHTNESS, MAXBRIGHTNESS);
    }
    else if (modButtonCycle == 2) {
      glowPink(MINBRIGHTNESS, MAXBRIGHTNESS);
    }
    else {
      glowBlue(MINBRIGHTNESS, MAXBRIGHTNESS);
    }
    delay(WAIT);

  }
  else {
    digitalWrite(ovenButtonLEDPin, LOW);
    // turn all LEDs off
    for (int led = 0; led < NUM_LEDS_STRIP; led++) {
      leds[led] = CRGB::Black;
    }
    FastLED.show();
  }

}

// ******** SUB FUNCTIONS ***************

// Interrupt function to change the "cycle"
void cycle() {
  unsigned long interrupt_time = millis();

  if (interrupt_time - last_interrupt_time > 500)
  {
    Serial.println(modButtonCycle);
    if (modButtonCycle < maxCycles - 1) {
      modButtonCycle++;
    }
    else {
      modButtonCycle = 0;

    }
  }
  else {
    Serial.println("Multiple presses");
  }
  last_interrupt_time = interrupt_time;
  Serial.println(modButtonCycle);
}

// ***** COLOR GLOWING FUNCTIONS BELOW ********

// glow red function
void glowRed(int minBrightness, int maxBrightness) {
  // turn all LEDs on
  //Set global brightness
  FastLED.setBrightness(0);

  for (int led = 0; led < NUM_LEDS_STRIP; led++) {
    leds[led] = CRGB::Maroon;
  }
  FastLED.show();

  // glowing UP
  for (int t = minBrightness; t < maxBrightness; t++) {
    FastLED.setBrightness(t);
    FastLED.show();
    delay(WAIT);
  }

  // glowing DOWN
  for (int t = maxBrightness; t > minBrightness; t--) {
    FastLED.setBrightness(t);
    FastLED.show();
    delay(WAIT);
  }
}

// glow pink function
void glowPink(int minBrightness, int maxBrightness) {
  // turn all LEDs on
  //Set global brightness
  FastLED.setBrightness(0);

  for (int led = 0; led < NUM_LEDS_STRIP; led++) {
    leds[led] = CRGB::Pink;
  }
  FastLED.show();

  // glowing UP
  for (int t = minBrightness; t < maxBrightness; t++) {
    FastLED.setBrightness(t);
    FastLED.show();
    delay(WAIT);
  }

  // glowing DOWN
  for (int t = maxBrightness; t > minBrightness; t--) {
    FastLED.setBrightness(t);
    FastLED.show();
    delay(WAIT);
  }
}

// glow blue function
void glowBlue(int minBrightness, int maxBrightness) {
  // turn all LEDs on
  //Set global brightness
  FastLED.setBrightness(0);

  for (int led = 0; led < NUM_LEDS_STRIP; led++) {
    leds[led] = CRGB::DeepSkyBlue;
  }
  FastLED.show();

  // glowing UP
  for (int t = minBrightness; t < maxBrightness; t++) {
    FastLED.setBrightness(t);
    FastLED.show();
    delay(WAIT);
  }

  // glowing DOWN
  for (int t = maxBrightness; t > minBrightness; t--) {
    FastLED.setBrightness(t);
    FastLED.show();
    delay(WAIT);
  }
}

// glow green function
void glowGreen(int minBrightness, int maxBrightness) {
  // turn all LEDs on
  //Set global brightness
  FastLED.setBrightness(0);

  for (int led = 0; led < NUM_LEDS_STRIP; led++) {
    leds[led] = CRGB::Green;
  }
  FastLED.show();

  // glowing UP
  for (int t = minBrightness; t < maxBrightness; t++) {
    FastLED.setBrightness(t);
    FastLED.show();
    delay(WAIT);
  }

  // glowing DOWN
  for (int t = maxBrightness; t > minBrightness; t--) {
    FastLED.setBrightness(t);
    FastLED.show();
    delay(WAIT);
  }
}
