#include <AddressableLEDStrip.h>

/*
  Set all the LEDs to a random color and then pulse them on and off.

  Pins:
    * Pin 8 -> SDI (or COM)
    * Pin 9 -> CLK
  
  For a strand of 32 addressable LEDs
*/

int SDI = 8;
int CKI = 9;
#define LEN 32

AddressableLEDStrip strip = AddressableLEDStrip(CKI, SDI, LEN);

int redValue = 0;
int index = 0;
int dir = -1;
int count = 0;
int inc = 2;
int strip_colors[LEN];

void setup() {
  strip.allow_out_of_bounds = true;
  
  // Pick a color to make random (R, G or B)
  for(int i = 0; i < LEN; i++){
    strip_colors[i] = random(0, 3);
    int color = random(50, 200);
    
    switch (strip_colors[i]){
      case 0:
        strip.set_led(i, color, 0, 0);
        break;
      case 1:
        strip.set_led(i, 0, color, 0);
        break;
      case 2:
        strip.set_led(i, 0, 0, color);
        break;
    }
  } 
  
  strip.send();
}

// Create an ascending RED for all pixels.
void loop() {
  
  // Adjust the intensity of each LED by 1 either up or down (per 'dir' variable)
  for(int i = 0; i < LEN; i++){
    int colors[] = { strip.get_red(i), strip.get_green(i), strip.get_blue(i) };
    int change = strip_colors[i];
    
    colors[ change ] += (dir * inc);
    
    strip.set_led(i, colors[0], colors[1], colors[2]);
  }
  strip.send();
  
  count += inc;
  delay(5);
  
  // Switch direction after 255 cycles
  if (count >= 200) {
    count = 0;
    dir *= -1;
  }
}

