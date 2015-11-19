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
 *  Define the standard FX2 interrupts.  For INT2 and INT4 autovector
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
 * \brief Interrupt numbers for standard FX2 interrupts.
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
 USBINT_ISR, ///< USB Interrupt.  An interrupt handler for this should only be used if not using auto vectored interrupts with INT2
 I2CINT_ISR, ///< I2C Bus interrupt
 IE4_ISR, ///< External interrupt 4.  An interrupt handler for this should only be used if not using auto vectored interrupts with INT4
 IE5_ISR, ///< External interrupt 5
 IE6_ISR, ///< External interrupt 6
 // Better names for the USART interrupts
 USART0_ISR = TI_0_ISR, ///< Better name for USART0 interrupt
 USART1_ISR = TI_1_ISR, ///< Better name for USART1 interrupt
} FX2_ISR;

/**
 * \brief Interrupt high priority.
 **/
#define INTERRUPT_HIGH_PRIO	1
/**
 * \brief Interrupt low priority.
 **/
#define INTERRUPT_LOW_PRIO	0


// TIMER0
// =======================================================================

/**
 * \brief Enable the timer 0 interrupt.
 *
 * CLEAR_TIMER0() is a NOP because the timer interrupt flag is automatically
 * cleared when the ISR is called.
 **/
#define ENABLE_TIMER0() ET0=1

/**
 * \brief Clear timer 0 interrupt
 *
 * CLEAR_TIMER0() is a NOP because the timer interrupt flag is automatically
 * cleared when the ISR is called.
 **/
#define CLEAR_TIMER0()

// TIMER1
// =======================================================================

/**
 * \brief Enable timer 1 interrupt
 *
 * CLEAR_TIMER1() is a NOP because the timer interrupt flag is automatically
 * cleared when the ISR is called.
 **/
#define ENABLE_TIMER1() ET1=1

/**
 * \brief Clear timer 1 interrupt
 *
 * CLEAR_TIMER1() is a NOP because the timer interrupt flag is automatically
 * cleared when the ISR is called.
 **/
#define CLEAR_TIMER1()

// TIMER2 and external EXF2 interrupt
// =======================================================================

/**
 * \brief Enable timer 2 interrupt
 *
 * This is the same interrupt whether timer 2 overflowed or 
 * for the external EXF2 flag.
 **/
#define ENABLE_TIMER2() ET2=1
/**
 * \brief Clear timer 2 interrupt
 *
 * Clears both the TF2 AND EXF2 flag
 **/
#define CLEAR_TIMER2() TF2=0;EXF2=0;

// Resume interrupt
// =======================================================================
// After the FX2 has entered its idle state, it responds to an external signal
// on its WAKEUP/WU2 pins or resumption of USB bus activity by restarting its
// oscillator and resuming firmware execution.

/**
 * \brief Enable the Resume Interrupt.  Requires EA=1 separately.
 **/
#define ENABLE_RESUME() ERESI = 1 

/**
 * \brief Clear the resume interrupt.  Use within the resume
 *  interrupt handler.
 **/
#define CLEAR_RESUME() RESI=0

// Interrupt 4 - Autovectored FIFO / GPIF or External interrupt 4
// =======================================================================

//#define ENABLE_INT4()

// External Interrupt 5
// =======================================================================

/**
 * \brief 
 * Enable external interrupt for INT5#
 **/
#define ENABLE_INT5() EIEX5=1 

/**
 * \brief 
 * Clear INT5# interrupt
 **/
#define CLEAR_INT5() \
	EXIF &= ~bmIE5

// USART0
// =======================================================================

/**
 * \brief Set the USART 0 interrupt priority.
 *
 * Does *not* enable the interrupt.
 *
 * \code
 *  SET_USART0_ISR_PRIO(INTERRUPT_HIGH_PRIO); // Set USART0 to high priority
 *  SET_USART0_ISR_PRIO(INTERRUPT_LOW_PRIO);  // Set USART0 to low priority
 * \endcode
 **/
#define SET_USART0_ISR_PRIORITY(p) \
	PS0 = p
/**
 * \brief Enable the USART 0 interrupt.
 *
 * Requires enabling global interrupts (EA=1) separately.
 *
 * The USART interrupt fires for both *receive* (RX) and *transmit* (TX)
 * completing, the interrupt must clear *both*.
 **/
#define ENABLE_USART0() \
	ES0 = 1;
/**
 * \brief Clear USART 0 RX bit.
 **/
#define CLEAR_USART0_RX() \
	RI = 0;
/**
 * \brief Clear USART 0 TX bit.
 **/
#define CLEAR_USART0_TX() \
	TI = 0;
/**
 * \brief Clear USART 0 both TX & RX bit.
 **/
#define CLEAR_USART0() \
	CLEAR_USART0_RX(); \
	CLEAR_USART0_TX();

// USART1
// =======================================================================

/**
 * \brief Set the USART 1 interrupt priority.
 *
 * Does *not* enable the interrupt.
 *
 * \code
 * SET_USART1_ISR_PRIO(INTERRUPT_HIGH_PRIO); // Set USART1 to high priority
 * SET_USART1_ISR_PRIO(INTERRUPT_LOW_PRIO);  // Set USART1 to low priority
 * \endcode
 **/
#define SET_USART1_ISR_PRIORITY(p) \
	PS1 = p
/**
 * \brief Enable the USART 1 interrupt.
 *
 * Requires enabling global interrupts (EA=1) separately.
 *
 * The USART interrupt fires for both *receive* (RX) and *transmit* (TX)
 * completing, the interrupt must clear *both*.
 **/
#define ENABLE_USART1() \
	ES1 = 1;
/**
 * \brief Clear USART 1 receive (RI1) bit.
 **/
#define CLEAR_USART1_RX() \
	RI1 = 0;
/**
 * \brief Clear USART 1 transmit (TI1) bit.
 **/
#define CLEAR_USART1_TX() \
	TI1 = 0;
/**
 * \brief Clear USART 1 both TX & RX bits.
 **/
#define CLEAR_USART1() \
	CLEAR_USART1_RX(); \
	CLEAR_USART1_TX();

// I2C Interrupt
// =======================================================================

/**
 * \brief Set the I2C interrupt priority.
 *
 * Does *not* enable the interrupt.
 *
 * \code
 *  SET_I2C_ISR_PRIO(INTERRUPT_HIGH_PRIO) // Set I2C to high priority
 *  SET_I2C_ISR_PRIO(INTERRUPT_LOW_PRIO)  // Set I2C to low priority
 * \endcode
 **/
#define SET_I2C_ISR_PRIORITY(p) \
	PI2C = p
/**
 * \brief Enable the I2C interrupt.
 *
 * Requires enabling global interrupts (EA=1) separately.
 *
 * The USART interrupt fires for both *receive* (RX) and *transmit* (TX)
 * completing, the interrupt must clear *both*.
 **/
#define ENABLE_I2C() \
	EI2C = 1;
/**
 * \brief Clear I2C interrupt.
 **/
#define CLEAR_I2C() \
	EXIF &= ~bmI2CINT;
