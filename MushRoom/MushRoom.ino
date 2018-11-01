#include "FastLED.h"

// How many leds in your strip?
#define NUM_FLOOR 240
#define NUM_MUSH 20

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806, define both DATA_PIN and CLOCK_PIN
#define Floor_PIN 3
#define Ceiling_PIN 4
#define Mush_PIN 5

// Define the array of leds
CRGB ledsFloor[NUM_FLOOR];
CRGB ledsCeiling[NUM_FLOOR];
CRGB ledsMush[NUM_MUSH];

void setup() {
  // put your setup code here, to run once:  
  Serial.begin(57600);
  Serial.println("resetting");
  
  LEDS.addLeds<WS2812,Floor_PIN,RGB>(ledsFloor, NUM_FLOOR);
  
  LEDS.addLeds<WS2812,Ceiling_PIN,RGB>(ledsCeiling, NUM_FLOOR);
  
  LEDS.addLeds<WS2812,Mush_PIN,RGB>(ledsMush, NUM_MUSH);

  LEDS.setBrightness(84);
}

void loop() {
  // put your main code here, to run repeatedly:

}
