#include "FastLED.h"

//Number of LEDs
#define NUM_LEDS 12

//Define our clock and data lines
#define DATA_PIN 11
#define CLOCK_PIN 13

#define WAIT 20
#define MAXBRIGHTNESS 70
#define MINBRIGHTNESS 10

//Create the LED array
CRGB leds[NUM_LEDS];

void setup() { 

      //Tell FastLED what we're using. Note "BGR" where you might normally find "RGB".
      //This is just to rearrange the order to make all the colors work right.
      FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN, BGR>(leds, NUM_LEDS);

      //Set global brightness
      FastLED.setBrightness(0);

              for(int led = 0; led < NUM_LEDS; led++) { 
            leds[led] = CRGB::Maroon; 
        }
        FastLED.show();
}

void loop() { 

  
// glowing UP
  for (int t=MINBRIGHTNESS; t<MAXBRIGHTNESS; t++){
    FastLED.setBrightness(t);
    FastLED.show();
    delay(WAIT);
  }

// glowing DOWN
  for (int t=MAXBRIGHTNESS; t>MINBRIGHTNESS; t--){
    FastLED.setBrightness(t);
    FastLED.show();
    delay(WAIT);
  }

}
