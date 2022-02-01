// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// Released under the GPLv3 license to match the rest of the
// Adafruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <VL53L0X.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

VL53L0X sensor; // sensor definition
int distance; // distance value from TOF sensor
// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        6 // On Trinket or Gemma, suggest changing this to 1

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 90 // Popular NeoPixel ring size

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 0
// Time (in milliseconds) to pause between pixels

void setup() {
  Serial.begin(9600);
  Wire.begin();

  sensor.setTimeout(0);
  if (!sensor.init())
  {
    Serial.println("Failed to detect and initialize sensor!");
    while (1) {}
  }

  // Start continuous back-to-back mode (take readings as
  // fast as possible).  To use continuous timed mode
  // instead, provide a desired inter-measurement period in
  // ms (e.g. sensor.startContinuous(100)).
  sensor.startContinuous();
  
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
}

void loop() {
 /*
  distance = sensor.readRangeContinuousMillimeters();   // value from TOF sensor
  Serial.println(distance);
  distance = VL53L0X sensor;
 // if (sensor.timeoutOccurred()) { Serial.print(" TIMEOUT"); }  
 
*/
  distance = sensor.readRangeContinuousMillimeters();
  Serial.println(distance);
  if (sensor.timeoutOccurred()) { Serial.print(" TIMEOUT"); }

  
  pixels.clear(); // Set all pixel colors to 'off'

  // The first NeoPixel in a strand is #0, second is 1, all the way up
  // to the count of pixels minus one.
  for(int i=0; i<NUMPIXELS; i++) { // For each pixel...

    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    // Here we're using a moderately bright green color 0, 150, 0:
    
    
    
    if(distance < 450){
         pixels.setPixelColor(i, pixels.Color(0,150,0));

         pixels.show();   // Send the updated pixel colors to the hardware.
    }
    
    
    
    else{
         
         pixels.setPixelColor(i, pixels.Color(96,96,96));      
         
         

         pixels.show();   // Send the updated pixel colors to the hardware.
    }
     

    delay(DELAYVAL); // Pause before next pass through loop
  }
}
