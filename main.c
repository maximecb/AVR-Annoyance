/*****************************************************************************
*
*  This file is part of the AVR Annoyance project. The project is
*  distributed at:
*  https://github.com/maximecb/AVR-Annoyance
*
*  Copyright (c) 2012, Maxime Chevalier-Boisvert. All rights reserved.
*
*  This software is licensed under the following license (Modified BSD
*  License):
*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions are
*  met:
*   1. Redistributions of source code must retain the above copyright
*      notice, this list of conditions and the following disclaimer.
*   2. Redistributions in binary form must reproduce the above copyright
*      notice, this list of conditions and the following disclaimer in the
*      documentation and/or other materials provided with the distribution.
*   3. The name of the author may not be used to endorse or promote
*      products derived from this software without specific prior written
*      permission.
*
*  THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED
*  WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
*  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN
*  NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
*  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
*  NOT LIMITED TO PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
*  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*****************************************************************************/

// Define CPU frequency
#define F_CPU 8000000UL

// Header files
#include <stdlib.h>
#include <avr/io.h>
#include <avr/power.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/wdt.h>
#include <util/delay.h>
#include "utility.h"

MAKE_OUTPUT(OUT_BUZZER, B, 4, 1)

// Watchdog timer interrupt handler
ISR(WDT_vect)
{
}

void makeNoise()
{
    uint8_t cnt = 10 + (rand() % 10);
    for (uint8_t i = 0; i < cnt; ++i)
    {
        uint8_t cnt2 = 10 + (rand() % 20);
        for (uint8_t j = 0; j < cnt2; ++j)
        {
            OUT_BUZZER(1);
            _delay_us(250);
            OUT_BUZZER(0);
            _delay_us(250);
        }

        _delay_ms(3 + (rand() % 12));
    }
}

void beep()
{
    for (uint8_t i = 0; i < 100; ++i)
    {
        OUT_BUZZER(1);
        _delay_us(500);
        OUT_BUZZER(0);
        _delay_us(500);
    }
}

int main(void)
{
    INIT_OUT_BUZZER();

    // Disable the extraneous peripherals to save power
    power_adc_disable();
    power_usi_disable();
    power_timer0_disable();
    power_timer1_disable();

    // Setup the watchdog timer with a ~8s timeout, interrupt on timeout
    MCUSR &= ~(1<<WDRF);
    WDTCR |= (1<<WDCE) | (1<<WDE);
    WDTCR = (1<<WDCE) | (1<<WDP3) | (1<<WDP0);
    WDTCR |= (1<<WDIE);

    // Enable interrupts
    sei();

    // Set sleep mode to power down mode
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);

    int counter = 0;

    int target = 0;

    for (;;)
    {
        // Increment the wake counter
        counter++;

        // If the target was reached
        if (counter >= target)
        {
            // Make annoying noise
            makeNoise();

            // Reset the wake counter
            counter = 0;

            int p = rand() % 100;

            // 30% prob: wait up to ~40s
            if (p < 30)
            {
                target = rand() % 6;
            }

            // 50% prob: wait up to a few minutes
            else if (p < 80)
            {
                target = rand() % 60;
            }

            // 12% prob: wait up to one hour
            else if (p < 92)
            {
                target = rand() % 450;
            }

            // 8% prob: wait up to multiple hours
            else
            {
                target = rand() % 2500;
            }

            /*
            _delay_ms(1000);
            for (int i = 0; i < (target / 75); ++i)
            {
                beep();
                _delay_ms(200);
            }
            */
        }

        // Put the chip to sleep in power-down mode
        sleep_mode();
    }
}

