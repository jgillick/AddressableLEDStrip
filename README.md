Addressable RGB LED Strip library for Arduino
=============================================

A simple arduino library for interacting with the addressable RGB LEDs sold by [SparkFun](https://www.sparkfun.com/products/11272).

Install
-------
[Download](https://github.com/jgillick/AddressableLEDStrip/archive/master.zip) the code ZIP, extract the contents and put the folder under your Arduino library directory.

For more instructions, see Arduino's guide to [Installing Additional Arduino Libraries](http://arduino.cc/en/Guide/Libraries).


Example
-------
Set each LED on 1 meter strip to a random RGB color.

#### Pins

* Pin 8 -> SDI (or COM)
* Pin 9 -> CLK

#### Code

    // Set all the LEDs to a random color.
    #include <AddressableLEDStrip.h>

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
