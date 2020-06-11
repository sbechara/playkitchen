#include "FastLED.h"

//Number of LEDs
#define NUM_LEDS 12

//Define our clock and data lines
#define DATA_PIN 11
#define CLOCK_PIN 13

//Create the LED array
CRGB leds[NUM_LEDS];

void setup() { 

      //Tell FastLED what we're using. Note "BGR" where you might normally find "RGB".
      //This is just to rearrange the order to make all the colors work right.
      FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN, BGR>(leds, NUM_LEDS);

      //Set global brightness
      FastLED.setBrightness(40);
}

void loop() { 

  uint8_t x;
  uint16_t wait = 100;

for (int dot=0;dot<NUM_LEDS; dot++){
  leds[dot] = CRGB::Maroon;
  FastLED.show();
  leds[dot]=CRGB::Black;
  delay(100);
}

}
