// Copyright (C) 2009 Ubixum, Inc. 
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

/*! \file 
 *  Macros for simple common tasks in fx2 firmware.
 * */

#ifndef FX2MACROS_H
#define FX2MACROS_H

#include "fx2regs.h"
#include "fx2types.h"

#define MSB(addr) (BYTE)((addr >> 8) & 0xff)
#define LSB(addr) (BYTE)(addr & 0xff)
#define MAKEWORD(msb,lsb) (((WORD)msb << 8) | lsb)

#define MSW(dword) (WORD)((dword >> 16) & 0xffff)
#define LSW(dword) (WORD)(dword & 0xffff)
#define MAKEDWORD(msw,lsw) (((DWORD)msw << 16) | lsw)

// clock stuff

/**
 * \brief Used for getting and setting the CPU clock speed.
 **/
typedef enum { CLK_12M =0, CLK_24M, CLK_48M} CLK_SPD;

/**
 * \brief Evaluates to a CLK_SPD enum.
 **/
#define CPUFREQ (CLK_SPD)((CPUCS & bmCLKSPD) >> 3)
/**
 * \brief Sets the cpu to operate at a specific
 *  clock speed.
 **/
#define SETCPUFREQ(SPD) CPUCS = (CPUCS & ~bmCLKSPD) | (SPD << 3)

/**
 * \brief Evaluates to a DWORD value representing 
 *  the clock speed in cycles per second. 
 *
 * Speeds:
 *
 *  \li 12000000L
 *  \li 24000000L
 *  \li 48000000L
 *
 **/
#define XTAL (CPUFREQ==CLK_12M ? 12000000L :\
              CPUFREQ==CLK_24M ? 24000000L : 48000000L)


/**
 * \brief Evaluates to the i2c bus frequency in cyles per
 * second.
 *
 * Speeds:
 *
 * \li 400000L
 * \li 100000L
 *
 **/
#define I2CFREQ ((I2CTL & bm400KHZ) ? 400000L : 100000L)


#define IFFREQ (IFCONFIG & bm3048MHZ ? 48000000L : 30000000L)
#define SETIF30MHZ() IFCONFIG &= ~bm3048MHZ
#define SETIF48MHZ() IFCONFIG |= bm3048MHZ


// eeprom stuff
#define EEPROM_TWO_BYTE (I2CS & bmBIT4)

/**
 * \brief Cause the device to disconnect and reconnect to USB.  This macro
 *  unconditionally renumerates the device no matter how the firmware is loaded.
 *
 *  <b>NOTE</b> Windows really doesn't like this if the firmware is loaded
 *  from an eeprom.  You'll see information messages about the device not
 *  working properly.  On the other hand, if you are changing the device 
 *  descriptor, e.g., the vendor and product id, when downloading firmware to the device, 
 *  you'll need to use this macro instead of the  
 *  standard RENUMERATE macro.
 **/
#define RENUMERATE_UNCOND() USBCS|=bmDISCON|bmRENUM;delay(1500);USBCS&=~bmDISCON
/**
 * \brief Cause the device to disconnect and reconnect to the USB bus.  This macro
 *  doesn't do anything if the firmware is loaded from an eeprom.
 **/
#define RENUMERATE() if(!(USBCS&bmRENUM)) {USBCS|=bmDISCON|bmRENUM;delay(1500);USBCS &= ~bmDISCON;}


// interrupts
// USB interrupts are in usbjt.h




/**
 * \brief TRUE if the FX2 has transitioned to high speed on the USB bus..
 **/
#define HISPEED (USBCS&bmHSM)




/**
 * \brief Evaluates to TRUE if a remote wakeup event has occurred.
 **/
#define REMOTE_WAKEUP() (((WAKEUPCS & bmWU) && (WAKEUPCS & bmWUEN)) || ((WAKEUPCS & bmWU2) && (WAKEUPCS & bmWU2EN)))


#endif
