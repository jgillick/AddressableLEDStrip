#include <AddressableLEDStrip.h>

/*
  Set all the LEDs to RED at a medium intensity and then create a 
  heartbeat-like pulse from the middle of the LED strand.

  Pins:
    * Pin 8 -> SDI (or COM)
    * Pin 9 -> CLK
  
  For a strand of 32 addressable LEDs
*/

int SDI = 8;  // Pin connected to SDI on the LED strand
int CKI = 9;  // Pin connected to CLK on the LED strand
int LEN = 32; // Number of LEDs in your strand

int intensity = 35; // The initial intensity of LEDs (0 - 255)

int direction = 1; // Pulsing direction: 1 = up, -1 = down
int increment = 8; // How much to increment each LED during each cycle

double speed = 20;  // The speed of the pulsing
double accel = 1; // The acceleration of each pulse

AddressableLEDStrip strip = AddressableLEDStrip(CKI, SDI, LEN);
int cycle, middle;

void setup() {
  strip.allow_out_of_bounds = true;
  
  // Make all the LEDs red
  for (int i = 0; i < LEN; i++) {
    strip.set_led(i, intensity, 0, 0);
  } 
  strip.send();
  
  cycle = 0;
  middle = round(LEN / 2);
}

void loop() {
  
  // Increment cycle, change direction if we're at the end
  cycle += direction;
  if (cycle <= 0 || cycle > LEN) {
    direction *= -1;
    cycle += direction;
  }
  
  // Increment the intensity of the LEDs, from the middle out
  inc_led(middle);
  for (int i = 1; i < cycle; i++) {
    
    // Left/right indexes to increment
    int lindex = middle - i;
    int rindex = middle + i;
    
    inc_led(lindex);
    inc_led(rindex);
  }
  
  strip.send();
  
  // Pause
  delay(speed);
  speed += (accel * direction);
}

// Increment the color on an LED
void inc_led(int index) {
  if (index >= 0 && index < LEN) {
    int color = strip.get_red(index);
    color += (direction * increment);
    
    strip.set_led(index, color, 0, 0);
  }
}

