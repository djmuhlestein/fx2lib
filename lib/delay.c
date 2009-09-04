/**
 * Copyright (C) 2009 Ubixum, Inc. 
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
#include <delay.h>

void delay(WORD millis) {
    /**
     * It takes 12 crystal pulses to make 1 machine cycle (8051.com)
     * ez-usb trm 1.13
     *  83.3 ns at 48mhz per instruction cycle
     *  (assume 166.6ns at 24mhz)
     *  (assume 333.3ns at 12mhz)
     * ez-usb trm 12.1
     *  Includes the cycles for each instruction
     **/    
    WORD loop_count;
    volatile WORD count;  // NOTE perhaps use different solutions w/ out volatile
    
    
    // set count to the number of times we need to
    // go around a loop for 1 millisecond
    
    // then do that loop millis times. (1000 us=1ms)
    
    // 48mhz: 1000 us / (17 cycles * 83.3 ns / cycle / 1000 ns/us) = 706
    // 24mhz: 353
    // 12mhz: 177
    // recalculate if the number of cycles changes
    // like if you change the loop below
    loop_count = CPUFREQ == CLK_12M ? 177 :
                 CPUFREQ == CLK_24M ? 353 : 706;
    
    // sdcc generated assembly
    /*  cycles   code
                ;   delay.c:31: do {
                00101$:
                ;   delay.c:32: } while ( --count );
        2           dec _delay_count_1_1
        2           mov a,#0xff
        4           cjne    a,_delay_count_1_1,00121$
        2           dec (_delay_count_1_1 + 1)
                00121$:
        2           mov a,_delay_count_1_1
        2           orl a,(_delay_count_1_1 + 1)
        3           jnz 00101$
        
        Total 17
    */
    
    do {
        count = loop_count;
        do {            
        } while ( --count );        
    } while ( --millis );
    
}
