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

//#define DEBUG_SETUPDAT

#ifdef DEBUG_SETUPDAT
#include <stdio.h> // NOTE this needs deleted
#else
#define printf(...)
#define NULL (void*)0;
#endif

#include <fx2regs.h>
#include <fx2macros.h>
#include <eputils.h>
#include <setupdat.h>


extern BOOL handle_vendorcommand(BYTE cmd);
extern BOOL handle_set_configuration(BYTE cfg);
extern BOOL handle_get_interface(BYTE ifc, BYTE* alt_ifc);
extern BOOL handle_set_interface(BYTE ifc,BYTE alt_ifc);
extern BYTE handle_get_configuration();
extern BOOL handle_set_configuration(BYTE cfg);
extern void handle_reset_ep(BYTE ep);

/**
 * Predefs for handlers
 **/


//  GET_STATUS,
BOOL handle_get_status();
//  CLEAR_FEATURE,
BOOL handle_clear_feature();
  // 0x02 is reserved
//  SET_FEATURE=0x03,
BOOL handle_set_feature();
  // 0x04 is reserved
//  SET_ADDRESS=0x05, // this is handled by EZ-USB core unless RENUM=0
//  GET_DESCRIPTOR,
void handle_get_descriptor();
//  SET_DESCRIPTOR,
//  GET_CONFIGURATION, // handled by callback
//  SET_CONFIGURATION, // handled by callback
//  GET_INTERFACE, // handled by callback
//  SET_INTERFACE, // handled by callback
//  SYNC_FRAME // not yet implemented

/*
 TRM 2.2
 Setup Token ->
 data transfer ->
 handshake
*/

void handle_setupdata() {
    //printf ( "Handle setupdat: %02x\n", SETUPDAT[1] );

    switch ( SETUPDAT[1] ) {

        case GET_STATUS:
            if (!handle_get_status())
                STALLEP0();
            break;
        case CLEAR_FEATURE:
            if (!handle_clear_feature()) {
                STALLEP0();
            }
            break;
        case SET_FEATURE:
            if (!handle_set_feature()) {
                STALLEP0();
            }
            break;
        case GET_DESCRIPTOR:
            handle_get_descriptor();
            break;
        case GET_CONFIGURATION:            
            EP0BUF[0] = handle_get_configuration();
            EP0BCH=0;
            EP0BCL=1;
            break;
        case SET_CONFIGURATION:
            // user callback
            if( !handle_set_configuration(SETUPDAT[2])) {
                STALLEP0();
            }
            break;
        case GET_INTERFACE:
            {
                BYTE alt_ifc;
                if (!handle_get_interface(SETUPDAT[4],&alt_ifc)) {
                    STALLEP0();
                } else {
                 EP0BUF[0] = alt_ifc;
                 EP0BCH=0;
                 EP0BCL=1;
                }
            }
            break;
        case SET_INTERFACE:
            // user callback
            if ( !handle_set_interface(SETUPDAT[4],SETUPDAT[2])) {
                STALLEP0();
            }
            break;
        default:
         if (!handle_vendorcommand(SETUPDAT[1])) {
            printf ( "Unhandled Vendor Command: %02x\n" , SETUPDAT[1] );
            STALLEP0();
         }
        
        
    }
    
    // do the handshake
    EP0CS |= bmHSNAK;
    
}

xdata BYTE* ep_addr(BYTE ep) { // bit 8 of ep_num is the direction
 BYTE ep_num = ep&~0x80; // mask the direction
 switch (ep_num) {
  case 0: return &EP0CS;
  case 1: return ep&0x80? &EP1INCS : &EP1OUTCS;
  case 2: return &EP2CS;
  case 4: return &EP4CS;
  case 6: return &EP6CS;
  case 8: return &EP8CS;
  default: return NULL;
 }
}


// Get status has three request types
#define GS_DEVICE 0x80
#define GS_INTERFACE 0x81
#define GS_ENDPOINT 0x82


volatile BOOL self_powered=FALSE;
volatile BOOL remote_wakeup_allowed=FALSE;

BOOL handle_get_status() {
    
    switch ( SETUPDAT[0] ) {

//        case 0: // sometimes we get a 0 status too
        case GS_INTERFACE: 
            EP0BUF[0] = 0;
            EP0BUF[1] = 0;
            EP0BCH=0;
            EP0BCL=2;
            break;
        case GS_DEVICE:

            // two byte response
            // byte 0 bit 0 = self powered bit 1 = remote wakeup
            EP0BUF[0] = (remote_wakeup_allowed << 1) | self_powered;
            // byte 1 = 0
            EP0BUF[1] = 0;
            EP0BCH = 0;
            EP0BCL = 2;
            break;
        case GS_ENDPOINT:
            {
                xdata BYTE* pep=ep_addr(SETUPDAT[4]);
                if ( !pep ) return FALSE;
                // byte 0 bit 0 = stall bit
                EP0BUF[0] = *pep & bmEPSTALL ? 1 : 0;
                EP0BUF[1] = 0;
                EP0BCH=0;
                EP0BCL=2;
            }
            break;
        default:
            printf ( "Unexpected Get Status: %02x\n", SETUPDAT[0] );
            return FALSE;
            
                        
    }
    return TRUE;
}


#define GF_DEVICE 0
#define GF_ENDPOINT 2

BOOL handle_clear_feature() {
 //printf ( "Clear Feature\n" );
 switch ( SETUPDAT[0] ) {
   case GF_DEVICE:
    if (SETUPDAT[2] == 1) {
        remote_wakeup_allowed=FALSE;
        break;
    }
    return FALSE;
   case GF_ENDPOINT:
    if (SETUPDAT[2] == 0) { // ep stall feature
        xdata BYTE* pep=ep_addr(SETUPDAT[4]);
        printf ( "unstall endpoint %02X\n" , SETUPDAT[4] );
        *pep &= ~bmEPSTALL;        
    } else {
        printf ( "unsupported ep feature %02x", SETUPDAT[2] );
        return FALSE;
    }

    break;
   default:
    return handle_vendorcommand(SETUPDAT[1]);
 }
 return TRUE;
}

BOOL handle_set_feature() {
 printf ( "Set Feature %02x\n", SETUPDAT[0] );
 switch ( SETUPDAT[0] ) {
  case GF_DEVICE:
    if (SETUPDAT[2] == 2) break; // this is TEST_MODE and we simply need to return the handshake
    if (SETUPDAT[2] == 1) {
       remote_wakeup_allowed=TRUE; 
       break;
    }
    return FALSE;
  case GF_ENDPOINT:
    if ( SETUPDAT[2] == 0 ) { // ep stall feature
        // set TRM 2.3.2
        // stall and endpoint
        xdata BYTE* pep = ep_addr(SETUPDAT[4]);
        printf ( "Stall ep %d\n", SETUPDAT[4] );
        if (!pep) {            
            return FALSE;
        }
        
        *pep |= bmEPSTALL;
        // should now reset data toggles
        // write ep+dir to TOGCTL
        RESETTOGGLE(SETUPDAT[4]);
        // restore stalled ep to default condition
        // NOTE
        //handle_reset_ep(SETUPDAT[4]);
        
    } else {
        printf ( "unsupported ep feature %02x\n", SETUPDAT[2] );
        return FALSE;
    }  
   break;
   default:
    return handle_vendorcommand(SETUPDAT[1]);
 }
 return TRUE;
}

/* these are devined in dscr.asm
   and need to be customized then
   linked in by the firmware manually */
extern code WORD dev_dscr;
extern code WORD dev_qual_dscr;
extern code WORD highspd_dscr;
extern code WORD fullspd_dscr;
extern code WORD dev_strings;

WORD pDevConfig = (WORD)&fullspd_dscr;
WORD pOtherConfig = (WORD)&highspd_dscr;

void handle_hispeed(BOOL highspeed) {
 __critical { 
     printf ( "Hi Speed or reset Interrupt\n" );
     if (highspeed) {
         pDevConfig=(WORD)&highspd_dscr;
         pOtherConfig=(WORD)&fullspd_dscr;
     } else {
        pDevConfig=(WORD)&fullspd_dscr;
        pOtherConfig=(WORD)&highspd_dscr;
     }
 }
}

/**
 * Handle:
 *  Device Descriptor
 *  Device Qualifier
 *  Configuration
 *  String
 *  Other-Speed
 **/
void handle_get_descriptor() {
    //printf ( "Get Descriptor\n" );
    
    switch ( SETUPDAT[3] ) {
        case DSCR_DEVICE_TYPE:
            printf ( "Get Device Config\n" );
            SUDPTRH = MSB((WORD)&dev_dscr);
            SUDPTRL = LSB((WORD)&dev_dscr);
            break;
        case DSCR_CONFIG_TYPE:
            // get the config descriptor
            printf ( "Get Config Descriptor\n");
            SUDPTRH = MSB(pDevConfig);
            SUDPTRL = LSB(pDevConfig);
            break;        
        case DSCR_STRING_TYPE:
            //printf ( "Get String Descriptor idx: %d\n", SETUPDAT[2] );
            {
                STRING_DSCR* pStr = (STRING_DSCR*)&dev_strings;
                // pStr points to string 0
                BYTE idx = SETUPDAT[2];
                BYTE cur=0; // current check
                do {
                    if (idx==cur++) break;
                    //printf ( "Length of pStr: %d\n", pStr->dsc_len );
                    //printf ( "pstr: %04x to ", pStr );
                    pStr = (STRING_DSCR*)((BYTE*)pStr + pStr->dsc_len);
                    //printf ( "%04x\n" , pStr );
                    if (pStr->dsc_type != DSCR_STRING_TYPE) pStr=NULL;
                } while ( pStr && cur<=idx);
                
                if (pStr) {
                    /* BYTE i;
                    //printf ( "found str: '");
                    for (i=0;i<pStr->dsc_len-2;++i) {
                       printf ( i%2==0?"%c":"%02x", *((BYTE*)(&pStr->pstr)+i));
                    } printf ( "\n"); */
                    
                    SUDPTRH = MSB((WORD)pStr);
                    SUDPTRL = LSB((WORD)pStr);
                    //SUDPTRH = MSB((WORD)&dev_strings);
                    //SUDPTRL = LSB((WORD)&dev_strings);
                } else {STALLEP0();}
                
            }
            
            break;
        case DSCR_DEVQUAL_TYPE:
            printf ( "Get Device Qualifier Descriptor\n");
            // assumes this is a high speed capable device
            SUDPTRH = MSB((WORD)&dev_qual_dscr);
            SUDPTRL = LSB((WORD)&dev_qual_dscr);
            break;
        case DSCR_OTHERSPD_TYPE:
            printf ( "Other Speed Descriptor\n");
            SUDPTRH = MSB(pOtherConfig);
            SUDPTRL = LSB(pOtherConfig);
            break;
        default:
            printf ( "Unhandled Get Descriptor: %02x\n", SETUPDAT[3]);
            STALLEP0();
    }
    
}

