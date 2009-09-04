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

#ifndef SETUPDAT_H
#define SETUPDAT_H

#include "fx2regs.h"
#include "delay.h"
/** \file setupdat.h
  Utilities for handling setup data and vendor commands.

 \verbatim

 This module needs initialized with a device descriptor.
 NOTE that your descriptors need to be located in code memory
 to use the SUDPTRH:L to auto transfer the data
 
 and vendor commands handler.  You have to provide callbacks.

DEVICE DESCRIPTORS
 
 // copy the dscr_asm file from the lib dir to your
 // own project directory, change it how
 // you want, and link it against your project

VENDOR COMMANDS

  0xA0 is handled by ez-usb firmware.  (Upload/Download ram)
  0xA1-0xAF is reserved for other ez-usb functions so don't use that
  Any other value (Above 0x0C anyway) can be used for device specific
  commands.
  
  If you include this file, you need to define a function for vendor
  commands even if you don't want to implement any vendor commands.
  The function should return TRUE if you handled the command and FALSE
  if you didn't.  The handle_setup function calls
  EP0CS |= bmHSNAK;
  before returning so there is no reason to set that bit in your
  vendor command handler.  (You do need to Set EP0 data and
  byte counts appropriately though.)
  
  // return TRUE if you handle the command 
  // you can directly get SETUPDAT[0-7] for the data sent with the command
  BOOL handle_vendorcommand(BYTE cmd) { return FALSE; }
  // a note  on vencor commands
  // this from the usb spec for requesttype
        D7 Data Phase Transfer Direction
        0 = Host to Device
        1 = Device to Host
        D6..5 Type
        0 = Standard
        1 = Class
        2 = Vendor
        3 = Reserved
        D4..0 Recipient
        0 = Device
        1 = Interface
        2 = Endpoint
        3 = Other
        4..31 = Reserved
  // if you want libusb to send data back to the host via ep0, you need to make
  // sure the requesttype had 1 in bit 7.  This is for libusb on linux anyway.
  
  
  // set *alt_ifc to the current alt interface for ifc
  BOOL handle_get_interface(BYTE ifc, BYTE* alt_ifc) { *ifc=0;*alt_ifc=0;}
  // return TRUE if you set the interface requested
  // NOTE this function should reconfigure and reset the endpoints
  // according to the interface descriptors you provided.
  BOOL handle_set_interface(BYTE ifc,BYTE alt_ifc) { return TRUE; }
  // handle getting and setting the configuration
  // 0 is the default.  If you support more than one config
  // keep track of the config number and return the correct number
  // config numbers are set int the dscr file.
  BYTE handle_get_configuration() { return 1; }
  // return TRUE if you handle this request
  // NOTE changing config requires the device to reset all the endpoints
  BOOL handle_set_configuration(BYTE cfg) { return FALSE; }
  // ep num (byte 7 is dir 1=IN,0=OUT)
  // client needs to reset the endpoint to default state
  void handle_reset_ep(BYTE ep) { }

  \endverbatim
*/


#define SETUP_VALUE() MAKEWORD(SETUPDAT[3],SETUPDAT[2])
#define SETUP_INDEX() MAKEWORD(SETUPDAT[5],SETUPDAT[4])
#define SETUP_LENGTH() MAKEWORD(SETUPDAT[7],SETUPDAT[6]) 
#define SETUP_TYPE SETUPDAT[0]

/**
 * self_powered is set to FALSE by default.  It is 
 * used for GET_FEATURE requests.  Firmware can set it to 
 * TRUE if the device is not powered by the USB bus.
 **/
extern volatile BOOL self_powered;

/**
 * remote_wakeup_allowed defaults to FALSE but can be
 * set to TRUE with SET_FEATURE from the host. (firmware shouldn't 
 * set this.)
 **/
extern volatile BOOL remote_wakeup_allowed;

//! see TRM 2-3
//! here are the usb setup data commands
//! these are the usb spec pretty much

typedef enum {
    GET_STATUS,
    CLEAR_FEATURE,
    // 0x02 is reserved
    SET_FEATURE=0x03,
    // 0x04 is reserved
    SET_ADDRESS=0x05, // this is handled by EZ-USB core unless RENUM=0
    GET_DESCRIPTOR,
    SET_DESCRIPTOR,
    GET_CONFIGURATION,
    SET_CONFIGURATION,
    GET_INTERFACE,
    SET_INTERFACE,
    SYNC_FRAME
} SETUP_DATA;


/**
 * returns the control/status register for an end point
 * (bit 7=1 for IN, 0 for out
 **/
xdata BYTE* ep_addr(BYTE ep);

/*
 You can call this function directly if you are polling
 for setup data in your main loop.
 You can also use the usbjt and enable the sudav isr
 and call the function from withing the sudav isr routine
*/
void handle_setupdata();


/**
    For devices to properly handle usb hispeed
    (This is if your descriptor has high speed and full speed versions
     and it should since the fx2lp is a high speed capable device
    )
    enable both USBRESET and HISPEED interrupts and
    call this function to switch the descriptors.  This function uses
    a __critical section to switch the descriptors and is safe to call
    from the hispeed or reset interrupt.  See \ref fw.c

    \param highspeed Call the function with highspeed = TRUE if 
        calling because the highspeed interrupt was received.
        If calling from usbreset, call with highspeed=false
**/
void handle_hispeed( BOOL highspeed );


/* descriptor types */
#define DSCR_DEVICE_TYPE 1
#define DSCR_CONFIG_TYPE 2
#define DSCR_STRING_TYPE 3
#define DSCR_DEVQUAL_TYPE 6
#define DSCR_OTHERSPD_TYPE 7

/* usb spec 2 */
#define DSCR_BCD 2


/* device descriptor */
#define DSCR_DEVICE_LEN 18

typedef struct {
    BYTE dsc_len; // descriptor length (18 for this )
    BYTE dsc_type; // dscr type
    WORD bcd; // bcd
    BYTE dev_class; // device class
    BYTE dev_subclass; // sub class
    BYTE dev_protocol; // sub sub class
    BYTE max_pkt; // max packet size
    WORD vendor_id;
    WORD product_id;
    WORD dev_version; // product version id
    BYTE idx_manstr; //  manufacturer string index
    BYTE idx_devstr; // product string index
    BYTE idx_serstr; // serial number index
    BYTE num_configs; // number of configurations
        
} DEVICE_DSCR;


/* config descriptor */
#define DSCR_CONFIG_LEN 9
typedef struct {
    BYTE dsc_len; // 9 for this one
    BYTE dsc_type; // dscr type
    
} CONFIG_DSCR;

/* string descriptor */
typedef struct {
    BYTE dsc_len;
    BYTE dsc_type;
    BYTE pstr;
} STRING_DSCR;




#endif
