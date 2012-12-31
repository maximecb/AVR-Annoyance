AVR-Annoyance
=============

Device producing screechy high-pitched noises at random intervals, similar to the "Annoy-a-tron".
This device is powered by an inexpensive ATtiny microcontroller.

Requirements:

    avr-gcc
    avr-libc
    avrdude
  
To build the project, type:

    make build
  
To program into your microcontroller, type:

    make fuse
    make flash

Testimonials from unwilling, annoyed users:

> "What's that sound!?"

> "Maybe it's the printer"

> "I once spent half an hour looking for it, couldn't find it"

During tests, the evice is able to operate for over two months drawing power
from two 3V CR2032 batteries connected in series. After two months of
operation, a battery voltage of 4.0V was measured with a 100Ohm load.
