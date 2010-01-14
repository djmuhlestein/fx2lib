// Copyright (C) 2010 Ubixum, Inc. 
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
 *  Define the standard fx2 interrupts.  For int2 and int4 autovector
 *  interrupts see \ref autovector.h
 *
 *  To enable an interrupt, simply define an interrupt handler function
 *  and use the appropriate ENABLE_* macro.  Interrupt enable macros
 *  do not enable interrupts globally.  Use EA=1 to enable interrupts.
 *
 *  \code
 *      void main() {
 *          ENABLE_RESUME();
 *          EA=1;
 *          ...
 *      }
 *
 *      void handle_resume() interrupt RESUME_ISR {
 *          CLEAR_RESUME();
 *      }
 *  \endcode
 *
 * */


/**
 * \brief interrupt numbers for standard fx2 interrupts

 **/
typedef enum {
 IE0_ISR=0, ///< External interrupt 0
 TF0_ISR, ///< Timer 0 interrupt
 IE1_ISR, ///< External interrupt 1
 TF1_ISR, ///< Timer 1 interrupt  
 TI_0_ISR, ///< Serial port 0 transmit or receive interrupt
 TF2_ISR, ///< Timer 2 interrupt
 RESUME_ISR, ///< Resume interrupt
 TI_1_ISR, ///< Serial port 1 transmit or receive interrupt
 USBINT_ISR, ///< Usb Interrupt.  An interrupt handler for this should only be used if not using auto vectored interrupts with int2
 I2CINT_ISR, ///< I2C Bus interrupt
 IE4_ISR, ///< External interrupt 4.  An interrupt handler for this should only be used if not using auto vectored interrupts with int4
 IE5_ISR, ///< External interrupt 5
 IE6_ISR, ///< External interrupt 6
} FX2_ISR;


/**
 * \brief Enable the timer 0 interrupt.
 *
 * There is not CLEAR_TIMER0 because the timer interrupt flag 
 * is automatically cleared when the isr is called.
 **/
#define ENABLE_TIMER0() ET0=1

/**
 * \brief Enable timer 1 interrupt
 * There is no CLEAR_TIMER1 because the timer interrupt flag
 * is automatically cleared when the isr is called.
 **/
#define ENABLE_TIMER1() ET1=1


/**
 * \brief Enable timer 2 interrupt
 *
 * This is the same interrupt whether timer 2 overflowed or 
 * for the external EXF2 flag.
 **/
#define ENABLE_TIMER2() ET2=1
/**
 *  \brief Clear timer 2 interrupt
 *
 *  Clears both the TF2 AND EXF2 flag
 **/
#define CLEAR_TIMER2() TF2=0;EXF2=0;

/**
 * \brief Enable the Resume Interrupt.  Requires EA=1 separately.
 **/
#define ENABLE_RESUME() ERESI = 1 

/**
 * \brief Clear the resume interrupt.  Use within the resume
 *  interrupt handler.
 **/
#define CLEAR_RESUME() RESI=0


#define ENABLE_INT4() 

/**
 * \brief 
 * Enable external interupt for int5#
 **/
#define ENABLE_INT5() EIEX5=1 

/**
 * \brief 
 * Clear int5# interrupt
 **/
#define CLEAR_INT5() EXIF &= ~0x80

