#include <CapacitiveSensor.h>

#include "FastLED.h"

// How many leds in your strip?
#define NUM_LEDS 20

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806, define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 5

// Define the array of leds
CRGB leds[NUM_LEDS];

 float touchThreshold = 0;

 long total1;

 int sensitivity = 15;
 
 unsigned long millisCount;
 unsigned long lastCount;

 bool touched = false;
  
 int value = 200;
 int valueDirection = -1;

 int touchCount = 0;

 static uint8_t hue = 0;

/*
 * CapitiveSense Library Demo Sketch
 * Paul Badger 2008
 * Uses a high value resistor e.g. 10M between send pin and receive pin
 * Resistor effects sensitivity, experiment with values, 50K - 50M. Larger resistor values yield larger sensor values.
 * Receive pin is the sensor pin - try different amounts of foil/metal on this pin
 */


CapacitiveSensor   cs_4_2 = CapacitiveSensor(10,9);        // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired

void setup()                    
{
 //  cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
  Serial.begin(57600);
  Serial.println("resetting");

  Intialize();

  LEDS.addLeds<WS2812,DATA_PIN,RGB>(leds,NUM_LEDS);
  LEDS.setBrightness(25);
}


void Intialize()
{
  int tempValue;
  
  for(int i=0; i< 10; i++)
  {
    tempValue += cs_4_2.capacitiveSensor(10);

    delay(100);
  }

    touchThreshold = (tempValue/10) + sensitivity;
    Serial.println(touchThreshold);
}

void fadeall() { for(int i = 0; i < NUM_LEDS; i++) { leds[i].nscale8(254); } }

void loop() { 

  if(hue >= 255)
  {
    hue = 0;
  }

  ReadSensor();
  
  // First slide the led in one direction
  for(int i = 0; i < NUM_LEDS; i++) {
    // Set the i'th led to red 
    leds[i] = CHSV(hue, value, value);
    // Show the leds
    // now that we've shown the leds, reset the i'th led to black
    // leds[i] = CRGB::Black;
    //fadeall();
    // Wait a little bit before we loop around and do it again

    FastLED.show(); 
    delay(20);
    //ValuePulse();
  }


  
}

//shift the value up and down to give the lamp an ambient pulse
void ValuePulse()
{  
  if(valueDirection == -1 && value < 150)
  {
    valueDirection = 1;
  }else if(valueDirection == 1 && value > 200){
    valueDirection = -1;
  }

  value += valueDirection; 
}

void ReadSensor()
{
  total1 = cs_4_2.capacitiveSensor(10);

  Serial.println(total1);

  //map hue to how much the plant is sensing 
  hue = map(total1, 0, 100, 0, 255);

}
