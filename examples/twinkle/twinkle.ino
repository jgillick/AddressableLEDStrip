#include <AddressableLEDStrip.h>

/*
  Twinkle all the LEDs randomly.

  This sets a random white intensity for each LED between -200 and 10. 
  With each cycle the intensity for every LED is increads by 2.
  When an LED's intensity gets to 200, a new random intensity is chosen for it between -200 and 10

  Pins:
    * Pin 8 -> SDI (or COM)
    * Pin 9 -> CLK
  
  For a strand of 32 addressable LEDs
*/

int SDI = 8;
int CKI = 9;
int LEN = 32

AddressableLEDStrip strip = AddressableLEDStrip(CKI, SDI, LEN);

int count = 0;
int inc = 2;

void setup() {
  randomSeed(analogRead(0));
  strip.allow_out_of_bounds = true;
  
  chooseColors();
 
  strip.send();
}

// Pick a color for each LED
void chooseColors() {
  for(int i = 0; i < LEN; i++){
    int intensity = random(-200, 10);
    strip.set_led(i, intensity, intensity, intensity);
  } 
}

// Create an ascending RED for all pixels.
void loop() {
  
  // Adjust the intensity of each LED by 1 either up or down (per 'dir' variable)
  for(int i = 0; i < LEN; i++){
    int intensity = strip.get_red(i);
    intensity += inc;
    
    if (intensity > 200) {
      intensity = random(-200, 10);
    }
    
    strip.set_led(i, intensity, intensity, intensity);
  }
  strip.send();
  
  delay(2);
}

