/**
 * Copyright (C) 2008 Ubixum, Inc. 
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


fx2::fx2():dev_handle(NULL),interface(0),alt_setting(0) {

 int rv=libusb_init(&libusb_ctx);
 assert(!rv);

}

fx2::~fx2() {

 if (isopen()) close();
 
 libusb_exit(libusb_ctx);
}


void fx2::open(int vid,int pid) {
    dev_handle=libusb_open_device_with_vid_pid (libusb_ctx,vid,pid);
    assert(dev_handle);
    int rv=libusb_claim_interface(dev_handle,interface);
    assert(!rv);
    rv=libusb_set_interface_alt_setting(dev_handle,interface,alt_setting);
    assert(!rv);
}
void fx2::set_interface(int iface, int alt){
    assert(dev_handle);
    if (interface != iface) {
        libusb_release_interface(dev_handle,this->interface);
    }
    int rv=libusb_claim_interface(dev_handle,iface);
    assert(!rv);
    rv=libusb_set_interface_alt_setting(dev_handle,iface,alt);
    assert(!rv);
    this->interface=iface;
    this->alt_setting=alt;
}
void fx2::close() {
    assert(dev_handle);
    libusb_release_interface(dev_handle,interface);
    libusb_close(dev_handle);
    dev_handle=NULL;
    interface=0;alt_setting=0;
}


int fx2::do_usb_command(char* buf, int size, unsigned char type, unsigned char request, unsigned short value, unsigned short index, unsigned short length ) {
 assert(dev_handle);
 return libusb_control_transfer (
    dev_handle,
    type,
    request,
    value,
    index,
    (unsigned char*)buf,
    length,
    1000);
}



bool fx2::ep_bulk(char* buf, int size, unsigned char ep, int timeout) {
 assert(dev_handle);
 int transferred;
 int rv=libusb_bulk_transfer ( dev_handle, ep, (unsigned char*)buf, size, &transferred, timeout );

 if (!rv) 
 {
  printf ( "Transfer Succeeded. (Bytes: %d)\n", transferred );
  return true;
 }

 if (rv==LIBUSB_ERROR_TIMEOUT) {
    printf ( "Transfer Timeout.  %d bytes transferred.\n", transferred );
 } else if (rv<0) {
    printf ( "Transfer Error: %d\n", rv );
 }

 return false;

}
