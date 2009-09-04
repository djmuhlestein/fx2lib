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

#include <i2c.h>

#define LED_ADDR 0x21
#define BTN_ADDR 0x20

#define KEY_F1 0
#define KEY_F2 1
#define KEY_F3 2
#define KEY_F4 3


BYTE digits[] = { 0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x98, 0x88, 0x83, 0xc6, 0xa1, 0x86, 0x8e  };


/**
 * This is pretty much the same function that is provided as the dev_io example from Cypress
 * Except is uses i2c read and write functions not from their library
 **/
void main(void) {

    BYTE    num = 0;
    //BYTE xdata	buttons;
    BYTE    buttons;
	BYTE	kstates = 0xff;
	BYTE	kdeltas;
	BYTE	key;
	BYTE	display = 1;

	while(1)
	{
		i2c_read ( BTN_ADDR, 1, &buttons );

		kdeltas = kstates ^ buttons;			// 
		kstates = buttons;
		key = 0;

		while(kdeltas)
		{
			if(kdeltas & 0x01)
			{
				if(!((kstates >> key) & 0x01))
					switch(key)
					{
                        case KEY_F1: // wakeup?
							num = 0;
							break;
						case KEY_F2:
							if(--num > 0x0f)
								num = 0x0f;
							break;
						case KEY_F3:
							if(++num > 0x0f)
								num = 0;
							break;						
						case KEY_F4:
							num = 0x0f;
					}
				display = 1;
			}
			kdeltas = kdeltas >> 1;
			++key;
		}
		if(display)
		{
            i2c_write ( LED_ADDR, 1, &digits[num], 0, NULL );
			display = 0;
		}
    }

}
