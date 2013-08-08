#include "Arduino.h"
#include "AddressableLEDStrip.h"

// Create the LED strip object with the clock pin, serial data pin and the number of LEDs in the strip.
AddressableLEDStrip::AddressableLEDStrip(int clk_pin, int sdi_pin, int num_leds)
{

  allow_out_of_bounds = false;

  strip_len = num_leds;

  // Create color arrays
  red_values = new int[num_leds];
  green_values = new int[num_leds];
  blue_values = new int[num_leds];

  // Setup pins
  clk = clk_pin;
  sdi = sdi_pin;
  pinMode(sdi, OUTPUT);
  pinMode(clk, OUTPUT);
}

// Set the RGB value on a single LED
// This does not write anything to the strip.
void AddressableLEDStrip::set_led(uint16_t index, int red, int green, int blue)
{
  // Make sure index is within range
  if (index < strip_len) {

    // Update the value to be within the 0 - 255 boundary
    if (allow_out_of_bounds == false) {
      if (red < 0) red = 0;
      else if (red > 255) red = 255;

      if (green < 0) green = 0;
      else if (green > 255) green = 255;

      if (blue < 0) blue = 0;
      else if (blue > 255) blue = 255;
    }

    // Set values
    red_values[index] = red;
    green_values[index] = green;
    blue_values[index] = blue;
  }
}

// Sets all the LEDs to OFF
// This does not write them to the strip.
void AddressableLEDStrip::clear_all()
{
  set_all_leds(0, 0, 0);
}

// Clear the color values for an LED at this index
void AddressableLEDStrip::clear_led(int index)
{
	set_led(index, 0, 0, 0);
}

// Set the red color (0 - 255) for an LED at this index
void AddressableLEDStrip::set_red(int index, int color)
{
	set_led(index, color, get_green(index), get_blue(index));
}

// Set the green color (0 - 255) for an LED at this index
void AddressableLEDStrip::set_green(int index, int color)
{
	set_led(index, get_red(index), color, get_blue(index));
}

// Set the blue color (0 - 255) for an LED at this index
void AddressableLEDStrip::set_blue(int index, int color)
{
	set_led(index, get_red(index), get_green(index), index);
}

// Set all the LEDs to the same RGB value.
// This does not write them to the strip.
void AddressableLEDStrip::set_all_leds(int red, int green, int blue)
{
  for(int i = 0 ; i < strip_len ; i++) {
    set_led(i, red, green , blue);
  }
}

// Push the RGB values to the LED strip.
void AddressableLEDStrip::send()
{
    //Each LED requires 24 bits of data
  //MSB: R7, R6, R5..., G7, G6..., B7, B6... B0
  //Once the 24 bits have been delivered, the IC immediately relays these bits to its neighbor
  //Pulling the clock low for 500us or more causes the IC to post the data.

  for(int i = 0 ; i < strip_len ; i++) 
  {	
		_send_color_bits(get_red(i));
		_send_color_bits(get_green(i));
		_send_color_bits(get_blue(i));
  }

  //Pull clock low to put strip into reset/post mode
  digitalWrite(clk, LOW);
  delayMicroseconds(500); //Wait for 500us to go into reset
}

// Send the individual bits from this value to the LED strip.
void AddressableLEDStrip::_send_color_bits(int value)
{
  // Value must be between 0 - 255
  if (value < 0) value = 0;
  else if (value > 255) value = 255;

  // Pull 8 bits from the value
  //for(int bit_place = 7; bit_place >= 0; bit_place--) {
  for(int bit_place = 7; bit_place >= 0; bit_place--) {
     //int bit_mask = pow(2, bit_place); // 128, 64, 32, 16, 8, 4, 2, 1
     int bit_mask = 1 << bit_place;  // 128, 64, 32, 16, 8, 4, 2, 1

    // Pull clock low to set the value
    digitalWrite(clk, LOW);

    // Write value
    if(value & bit_mask)
      digitalWrite(sdi, HIGH);
    else
      digitalWrite(sdi, LOW);

    // Latch the new value in
    digitalWrite(clk, HIGH);
  }
}

// Get the number of LED that are in this strip (or at least what you set the length to be).
int AddressableLEDStrip::length()
{
  return strip_len;
}

// Get the red value at an LED index
int AddressableLEDStrip::get_red(int index)
{
  if (index < strip_len) {
    return red_values[index];
  }
  return 0;
}

// Get the green value at an LED index
int AddressableLEDStrip::get_green(int index)
{
  if (index < strip_len) {
    return green_values[index];
  }
  return 0;
}

// Get the blue value at an LED index
int AddressableLEDStrip::get_blue(int index)
{
  if (index < strip_len) {
    return blue_values[index];
  }
  return 0;
}