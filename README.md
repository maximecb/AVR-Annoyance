AVR-Annoyance
=============

Device producing screechy high-pitched noises at random intervals, similar to the "Annoy-a-tron".
This device is powered by an inexpensive ATtiny microcontroller.

Parts required (total value less than $2):
- ATTiny85 or ATMega8/16/32 microcontroller
- 1x 1uF capacitor
- 1x 10K resistor
- 1x 2N2222 transistor
- 1x speaker 8 to 30 Ohms
- 4.5V to 6V battery (2xCR2032 batteries work)
- Wire to make connections

Software requirements:

    avr-gcc
    avr-libc
    avrdude

To compile the code, type:

    make build
  
To program into your microcontroller, type:

    make fuse
    make flash

Testimonials from unwilling, annoyed users:

> "What's that sound!?"

> "Maybe it's the printer"

> "I once spent half an hour looking for it, couldn't find it"

During tests, the device was able to operate for over two months drawing power
from two 3V CR2032 batteries connected in series. After two months of
operation, a battery voltage of 4.0V was measured with a 100Ohm load.
