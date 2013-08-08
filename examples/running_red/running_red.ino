#include <AddressableLEDStrip.h>

/*
  Set all the LEDs on a 1 meter strip to an ascending shade of red.

  Pins:
    * Pin 8 -> SDI (or COM)
    * Pin 9 -> CLK
  
  For a strand of 32 addressable LEDs
*/

int SDI = 8;
int CKI = 9;
int LEN = 32;

AddressableLEDStrip strip = AddressableLEDStrip(CKI, SDI, LEN);

byte redValue = 0;
int index = 0;

void setup() {
  strip.clear_all();
  strip.send();
}

// Create an ascending RED for all pixels.
void loop() {
  
  redValue += 5;
  if (redValue > 255) {
    redValue = 10;
  }
  
  if (index > LEN) {
    index = 0;
  }
  
  strip.set_led(index, redValue, 0, 0);
  strip.send();
  delay(10);
  
  index++;
}

