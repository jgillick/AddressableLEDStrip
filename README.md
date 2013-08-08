Addressable RGB LED Strip Arduino Library
=========================================

A simple arduino library for interacting with the addressable RGB LED strip sold by [SparkFun](https://www.sparkfun.com/products/11272).


Example
-------
Set all the LEDs on a 1 meter strip to an ascending shade of red. This code assumes:
  * SDI (or COM) attached to pin 2
  * CLK attached to pin 3
  * A 1 meter addressable LED strip (FLB-W5050RGB-16-5-N14) with 32 LEDs.

    #include <AddressableLEDStrip.h>

    AddressableLEDStrip strip = AddressableLEDStrip(3, 2, 32);

    int redValue = 0;
    int index = 0;

    void setup()
    {
    }

    // Create an ascending RED for all pixels.
    void loop()
    {
      // Set red value (reset to 0 if it's above 255)
      redValue++;
      if (redValue > 255) {
        redValue = 0;
      }

      // Set LED color
      strip.set_led(index, redValue, 0, 0);
      strip.send();

      // Increment and delay
      index++;
      delay(100);
    }

License
-------
The MIT License (MIT)

Copyright (c) 2013 Jeremy Gillick

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
