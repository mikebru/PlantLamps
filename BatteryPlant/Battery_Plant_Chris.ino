/*
* Name: Chris Correll and Michael Bruner
* Arduino code touch plant light up leds 
* Uses capacitive touch with 10mOhm resistor foil ground plane and itsy bitsy
* Leonardo based microcontroller
*/

#include <CapacitiveSensor.h>
#include "FastLED.h"

// How many leds in your strip?
#define NUM_LEDS 20 
#define DATA_PIN 5
#define SEND_PIN 10
#define RECEIVE_PIN 9  // Has sensor on it

// Define the array of leds
CRGB leds[NUM_LEDS];
float touch_threshold = 0;
long total1;
unsigned long last_count = 0;
int sensitivity = 15; 
int value = 200;
int touch_count = 0;
bool touched = false;  
static uint8_t hue = 0;

CapacitiveSensor   cs = CapacitiveSensor(SEND_PIN,RECEIVE_PIN);        // 10M resistor between pins 10 & 9, pin 9 is sensor pin, add a wire and or foil if desired

void setup()                    
{
  // Init capacitive sensor
  Intialize();
  // Init LEDs
  LEDS.addLeds<WS2812,DATA_PIN,RGB>(leds,NUM_LEDS);
  LEDS.setBrightness(50);
}

// Takes ten readings from the capacitive sensor and averages to find 
// a baseline (touch_threshold) samples at a rate of 10hZ (every 100ms)
void Intialize()
{
  int tempValue;
  
  for(int i=0; i< 10; i++)
  {
    tempValue += cs.capacitiveSensor(10);
    delay(100);
  }
  
    touch_threshold = (tempValue/10) + sensitivity;
}

// Take reading (10 bytes) and check if it is greater then baseline plus sensitivity
void ReadSensor()
{
  total1 = cs.capacitiveSensor(10);
  if(total1 >= touch_threshold)
  { 
    touched = true;
  }
  else if(total1 < touch_threshold)
  {
    touched = false;
  }
}

// Changes LED colors if capacitive sensor read is touched
void loop() { 
  // Reinitialize every 5min what to do if person is touching plant during init time?
  if (millis() > last_count+300,000){
    Initialize();
  }
  for(int i = 0; i < NUM_LEDS; i++) {
    ReadSensor();
    // Update color if sensor touched
    if (touched) {
      hue += 3;
    }
    // Set the i'th led to red 
    leds[i] = CHSV(hue, value, value);
    FastLED.show(); 
    delay(20);
    // Reset hue if at the end of the colors
    if(hue >= 255)
    {
    hue = 0;
    }
  }
}
