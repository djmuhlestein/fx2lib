/**
 * Copyright (C) 2010 Ubixum, Inc. 
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 **/

#include <fx2regs.h>
#include <fx2macros.h>
#include <fx2ints.h>
#include <lights.h>

volatile bit d2;
volatile bit d3;
volatile bit d4;
volatile bit d5;

void timer0_isr() interrupt TF0_ISR {
 d2 = !d2;
 if (d2) { d2on(); } else { d2off(); }
}

void timer1_isr() interrupt TF1_ISR {
 d3 = !d3;
 if (d3) { d3on(); } else { d3off(); }
}

void timer2_isr() interrupt TF2_ISR {
 d4 = !d4;
 if (d4) { d4on(); } else { d4off(); }

 CLEAR_TIMER2(); // This one is not done automatically!
}


void main(void)
{
    WORD counter=0;

    SETCPUFREQ(CLK_12M);

    // enable timer 0 and timer 1 to be 16 bit counters
    TMOD = 0x11; 

    // enable timer 2 to also be a 16 bit counter
    T2CON = 0;
    RCAP2L = 0; // reload values for t2
    RCAP2H = 0; 

    EA=1; // enable interrupts
    ENABLE_TIMER0();
    ENABLE_TIMER1();
    ENABLE_TIMER2();
    TR0=1; // start t0
    TR1=1; // start t1 
    TR2=1; // start t2

    // and blink d5
    while (TRUE) {
        ++counter;
        if (!counter) {
            d5 = !d5;
            if (d5) { d5off(); } else { d5on(); }
        }
    }
}


