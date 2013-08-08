#include <AddressableLEDStrip.h>

/*
  Move the selected LED, like a cursor, along the LED strip by sending commands in the serial console.
  
  Commands:
    < and > : Move left and right
    + and - : Change the LED intensity
       c    : Change the color
  
  Pins:
    * Pin 8 -> SDI (or COM)
    * Pin 9 -> CLK
  
  For a strand of 32 addressable LEDs
*/

int SDI = 8;
int CKI = 9;
#define LEN 32

AddressableLEDStrip strip = AddressableLEDStrip(CKI, SDI, LEN);

int color = 0;
int intensity = 100;
int index = 0;

void setup() {
  Serial.begin(9600);
  set_led();
}


void loop() {
  if (Serial.available() > 0) {
    char incoming = Serial.read();
    
    // Process command
    switch(incoming) {
      case '>':
        index++;
        if (index >= LEN)
          index = 0;
        Serial.println("Move right");
        break;
      case '<':
        index--;
        if (index < 0)
          index = LEN - 1;
        Serial.println("Move left");
        break;
      case '+':
        intensity += 15;
        if (intensity > 256)
          intensity = 256;
        Serial.println("Increse intensity");
        break;
      case '-':
        intensity -= 15;
        if (intensity <= 0)
          intensity = 0;
        Serial.println("Decrese intensity");
        break;
      case 'c':
        color += 1;
        if (color > 2) 
          color = 0;
        Serial.println("Change color");
        break;
    }
    
    set_led();
  }
}

// Update LED with the new settings
void set_led(){
  // Update LED
  strip.clear_all();
  
  switch(color) {
    case 0: // RED
      strip.set_led(index, intensity, 0, 0);
      break;
    case 1: // GREEN
      strip.set_led(index, 0, intensity, 0);
      break;
    case 2: // BLUE
      strip.set_led(index, 0, 0, intensity);
      break;
  }
  strip.send();
}

