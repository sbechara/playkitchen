#include "FastLED.h"

//Number of LEDs
#define NUM_LEDS 16

//Define our clock and data lines
#define DATA_PIN 7
#define CLOCK_PIN 6

#define WAIT 20
#define MAXBRIGHTNESS 100
#define MINBRIGHTNESS 10

//Create the LED array
CRGB leds[NUM_LEDS];

const byte interruptPin = 2;
volatile byte state = LOW;
int modButtonCycle = 0;

void setup() {

  //Tell FastLED what we're using. Note "BGR" where you might normally find "RGB".
  //This is just to rearrange the order to make all the colors work right.
  FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN, BGR>(leds, NUM_LEDS);

  //Set global brightness
  FastLED.setBrightness(0);

  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), cycle, RISING);

  // For testign
  Serial.begin(9600);
}

void loop() {

  
  
  if (modButtonCycle == 0)
  {
    glowRed(MINBRIGHTNESS, MAXBRIGHTNESS);
  }
  else if (modButtonCycle == 1) {
    move(NUM_LEDS, 50);
  }
  else {
    glowBlue(MINBRIGHTNESS, MAXBRIGHTNESS);
  }


}

// glow red function
void glowRed(int minBrightness, int maxBrightness) {
  // turn all LEDs on
  //Set global brightness
  FastLED.setBrightness(0);

  for (int led = 0; led < NUM_LEDS; led++) {
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

// move function
void move(int numLEDS, int brightness) {
  FastLED.setBrightness(brightness);
  for (int dot = 0; dot < numLEDS; dot++) {
    leds[dot] = CRGB::Maroon;
    FastLED.show();
    leds[dot] = CRGB::Black;
    delay(100);
  }
}

// glow blue function
void glowBlue(int minBrightness, int maxBrightness) {
  // turn all LEDs on
  //Set global brightness
  FastLED.setBrightness(0);

  for (int led = 0; led < NUM_LEDS; led++) {
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

void cycle() {
  Serial.println(modButtonCycle);
      if (modButtonCycle < 2) {
      modButtonCycle++;
    }
    else {
      modButtonCycle = 0;
      
    }
}
