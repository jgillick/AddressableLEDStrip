#include <AddressableLEDStrip.h>

/*
  Twinkle all the LEDs with random colors.

  This chooses a random color for each LED (0:Red, 1:Green, 2:Blue) and intensity.
  With each cycle the intensity for each LED is increads by 2 on that color.
  When an LED's intensity gets to 200, a new random color and intensity is chosen.

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
int count = 0;
int inc = 2;

// Holds the color we're shining for each LED: 0:Red, 1:Green, 2:Blue
int strip_colors[LEN];

void setup() {
  randomSeed(analogRead(0));
  strip.allow_out_of_bounds = true;
  
  chooseColors();

  strip.send();
}

// Pick a color for each LED
void chooseColors() {
  for(int i = 0; i < LEN; i++){
    chooseColorFor(i);
  } 
}

// Choose a color for an LED and set it
void chooseColorFor(int led) {
  int color = random(-200, 10);
  strip_colors[led] = random(0, 3);
  
  strip.clear_led(led);
  switch (strip_colors[led]){
    case 0:
      strip.set_red(led, color);
      break;
    case 1:
      strip.set_green(led, color);
      break;
    case 2:
      strip.set_blue(led, color);
      break;
  }
}

// Create an ascending RED for all pixels.
void loop() {
  
  // Adjust the intensity of each LED by 1 either up or down (per 'dir' variable)
  for(int i = 0; i < LEN; i++){
    int colors[] = { strip.get_red(i), strip.get_green(i), strip.get_blue(i) };
    int change = strip_colors[i];
    
    // Update only the selected color
    colors[ change ] += inc;
    
    if (colors[ change ] > 200) {
      chooseColorFor(i);
    }
    else {
      strip.set_led(i, colors[0], colors[1], colors[2]);
    }
  }
  strip.send();
  
  count += inc;
  delay(1);
}

