#include <AddressableLEDStrip.h>

/*
  Set all the LEDs to a random color.

  Pins:
    * Pin 8 -> SDI (or COM)
    * Pin 9 -> CLK

  For a strand of 32 addressable LEDs
*/

int SDI = 8;
int CKI = 9;
int LEN = 32;

AddressableLEDStrip strip = AddressableLEDStrip(CKI, SDI, LEN);

int index = 0;

void setup() { }

void loop() {
  // If we're at the end of the strand, start from the beginning again.
  if (index > LEN) {
    index = 0;
  }

  // Set the LED at 'index' to a random RGB color
  strip.set_led(index, random(256), random(256), random(256));
  strip.send();

  // Delay 50 milliseconds and then move to the next LED
  delay(50);
  index++;
}

