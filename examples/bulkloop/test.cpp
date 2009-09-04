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
#include <libusb-1.0/libusb.h>

int main(int argc, char* argv[]) {

 libusb_context* ctx;
 libusb_init(&ctx);

 libusb_device_handle* hndl = libusb_open_device_with_vid_pid(ctx,0x04b4,0x1004);
 libusb_claim_interface(hndl,0);
 libusb_set_interface_alt_setting(hndl,0,0);
 
 unsigned short buf[100];
 for (int i=0;i<100;++i) {
  buf[i]=i;
 }
 int transferred;
 int rv=libusb_bulk_transfer(hndl,0x02,(unsigned char*)buf,sizeof(buf),&transferred,100);
 if(rv) {
  printf ( "OUT Transfer failed: %d\n", rv );
  return rv;
 }

 unsigned short buf2[100];
 rv=libusb_bulk_transfer(hndl,0x86,(unsigned char*)buf2,sizeof(buf2),&transferred,100); 
 if(rv) {
  printf ( "IN Transfer failed: %d\n", rv );
  return rv;
 }
 for (int i=0;i<100;++i) {
  printf ( "%d ", buf2[i] );
 }
 printf("\n");

 return 0;
}
