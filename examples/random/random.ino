#include <AddressableLEDStrip.h>

/*
  Set all the LEDs on a 1 meter strip to an ascending shade of red.

  This code assumes:
    * SDI (or COM) attached to pin 2
    * CLK attached to pin 3
    * A 1 meter addressable LED strip (FLB-W5050RGB-16-5-N14) with 32 LEDs.
*/

int SDI = 2;
int CKI = 3;
int LEN = 32;

AddressableLEDStrip strip = AddressableLEDStrip(CKI, SDI, LEN);

int redValue = 0;
int index = 0;

void setup() {
  strip.clear_leds();
  strip.send();
}

// Create an ascending RED for all pixels.
void loop() {
  
  if (index > LEN) {
    index = 0;
  }
  
  strip.set_led(index, random256, random(256), random(256));
  strip.send();
  delay(50);
  
  index++;
}

