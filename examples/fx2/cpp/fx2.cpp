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


void fx2::open(int vid,int pid) {
    dev_handle=libusb_open_device_with_vid_pid (libusb_ctx,vid,pid);
    assert(dev_handle);
    int rv=libusb_claim_interface(dev_handle,0);
    assert(!rv);
    interface=0;
    rv=libusb_set_interface_alt_setting(dev_handle,0,0);
    assert(!rv);
    alt_setting=0;
    
}
void fx2::set_interface(int iface, int alt){
    assert(dev_handle);
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
    assert(dev_handle);
    libusb_release_interface(dev_handle,interface);
    libusb_close(dev_handle);
    dev_handle=NULL;
    interface=0;alt_setting=0;
}


int fx2::do_usb_command(char* buf, int size, unsigned char type, unsigned char request, unsigned short value, unsigned short index, unsigned short length, int timeout ) {
 assert(dev_handle);
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
    assert(dev_handle);
    return libusb_clear_halt(dev_handle,(unsigned char)ep);
}

int fx2::reset() {
    assert(dev_handle);
    int rv=libusb_reset_device(dev_handle);
    if (rv==LIBUSB_ERROR_NO_DEVICE) {
        printf ( "Device Changed.  Closing\n");
        libusb_close(dev_handle);
        interface=0;alt_setting=0;
    }
    return rv;
}

int fx2::set_configuration(int configuration) {
    assert(dev_handle);
    libusb_release_interface(dev_handle,interface);
    int rv=libusb_set_configuration(dev_handle,configuration);
    if (!rv) {
        libusb_claim_interface(dev_handle,interface);
    }
}


bool fx2::ep_bulk(char* buf, int size, unsigned char ep, int timeout) {
 assert(dev_handle);
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
