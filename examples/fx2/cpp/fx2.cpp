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

#include <cstdio>
#include <cassert>

#include "fx2.h"


fx2::fx2():dev_handle(NULL) {

 int rv=libusb_init(&libusb_ctx);
 assert(!rv);
 libusb_set_debug(libusb_ctx,0);
}

void fx2::set_debug_level(int n) {
 libusb_set_debug(libusb_ctx,n);
}

fx2::~fx2() {

 if (isopen()) close();
 
 libusb_exit(libusb_ctx);
}

#define CHECK_OPEN(r) if (!dev_handle) {\
    printf ( "Device not opened.\n" ); \
    return r;\
    }


void fx2::open(int vid,int pid,int idx) {

    libusb_device **list;
    int devices = libusb_get_device_list( libusb_ctx, &list );
    int cur_idx=0;
    for ( int i=0;i<devices;++i) {
       libusb_device_descriptor dscr;
       if ( !libusb_get_device_descriptor ( list[i], &dscr ) ) {
          if ( dscr.idVendor == vid && dscr.idProduct == pid ) {
             if ( idx == cur_idx++ ) {
                int rv = libusb_open( list[i], &dev_handle);
                if (!rv) {
                    rv=libusb_claim_interface(dev_handle,0);
                    if (!rv) {                     interface=0;
                     rv=libusb_set_interface_alt_setting(dev_handle,0,0);
                     if (rv) {
                        libusb_close(dev_handle);
                        dev_handle=NULL;
                     }
                     alt_setting=0;
                   } else {
                    libusb_close(dev_handle);
                    dev_handle=NULL;
                   }
                } else {
                    printf ( "Unable to open device idx: %d, ret: %d\n", idx, rv );
                }
             }
          }
       }
    }
    
    if (!dev_handle) {
        printf ( "Device not opened.\n" );
    }
    libusb_free_device_list(list,1);
}
void fx2::set_interface(int iface, int alt){
    CHECK_OPEN()
    if (interface != iface) {
        libusb_release_interface(dev_handle,interface);
        int rv=libusb_claim_interface(dev_handle,iface);
        assert(!rv);
        this->interface=iface;
    }
    int rv=libusb_set_interface_alt_setting(dev_handle,interface,alt);
    assert(!rv);
    alt_setting=alt;
}
void fx2::close() {
    CHECK_OPEN()
    libusb_release_interface(dev_handle,interface);
    libusb_close(dev_handle);
    dev_handle=NULL;
    interface=0;alt_setting=0;
}


int fx2::do_usb_command(char* buf, int size, unsigned char type, unsigned char request, unsigned short value, unsigned short index, unsigned short length, int timeout ) {
 CHECK_OPEN(-1)
 return libusb_control_transfer (
    dev_handle,
    type,
    request,
    value,
    index,
    (unsigned char*)buf,
    length,
    timeout);
}

int fx2::clear_halt(char ep) {
    CHECK_OPEN(-1)
    return libusb_clear_halt(dev_handle,(unsigned char)ep);
}

int fx2::reset() {
    CHECK_OPEN(-1)
    int rv=libusb_reset_device(dev_handle);
    if (rv==LIBUSB_ERROR_NO_DEVICE) {
        printf ( "Device Changed.  Closing\n");
        libusb_close(dev_handle);
        interface=0;alt_setting=0;
    }
    return rv;
}

int fx2::set_configuration(int configuration) {
    CHECK_OPEN(-1)
    libusb_release_interface(dev_handle,interface);
    int rv=libusb_set_configuration(dev_handle,configuration);
    if (!rv) {
        libusb_claim_interface(dev_handle,interface);
    }
}


bool fx2::ep_bulk(char* buf, int size, unsigned char ep, int timeout) {
 CHECK_OPEN(-1)
 int transferred;
 int rv=libusb_bulk_transfer ( dev_handle, ep, (unsigned char*)buf, size, &transferred, timeout );

 if (!rv) return true; 

 if (rv==LIBUSB_ERROR_TIMEOUT) {
    printf ( "Transfer Timeout.  %d bytes transferred.\n", transferred );
 } else if (rv<0) {
    printf ( "Transfer Error: %d\n", rv );
 }

 return false;

}
