#include "FastLED.h"

#include <Wire.h>
#include "Adafruit_MPR121.h"

#ifndef _BV
#define _BV(bit) (1 << (bit)) 
#endif

// You can have up to 4 on one i2c bus but one is enough for testing!
Adafruit_MPR121 cap = Adafruit_MPR121();

// Keeps track of the last pins touched
// so we know when buttons are 'released'
uint16_t lasttouched = 0;
uint16_t currtouched = 0;


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

    while (!Serial) { // needed to keep leonardo/micro from starting too fast!
    delay(10);
  }
  
  Serial.println("resetting");
  
  LEDS.addLeds<WS2812,Floor_PIN,RGB>(ledsFloor, NUM_FLOOR);
  
  LEDS.addLeds<WS2812,Ceiling_PIN,RGB>(ledsCeiling, NUM_FLOOR);
  
  LEDS.addLeds<WS2812,Mush_PIN,RGB>(ledsMush, NUM_MUSH);

  LEDS.setBrightness(84);


  // Default address is 0x5A, if tied to 3.3V its 0x5B
  // If tied to SDA its 0x5C and if SCL then 0x5D
  if (!cap.begin(0x5A)) {
    Serial.println("MPR121 not found, check wiring?");
    while (1);
  }
  Serial.println("MPR121 found!");
}

void loop() {
  // put your main code here, to run repeatedly:

  // Get the currently touched pads
  currtouched = cap.touched();
  
  for (uint8_t i=0; i<12; i++) {
    // it if *is* touched and *wasnt* touched before, alert!
    if ((currtouched & _BV(i)) && !(lasttouched & _BV(i)) ) {
      Serial.print(i); Serial.println(" touched");
    }
    // if it *was* touched and now *isnt*, alert!
    if (!(currtouched & _BV(i)) && (lasttouched & _BV(i)) ) {
      Serial.print(i); Serial.println(" released");
    }
  }

  // reset our state
  lasttouched = currtouched;
  

}
