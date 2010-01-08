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

#ifndef FX2_H
#define FX2_H

#include <libusb-1.0/libusb.h>

const int VID=0x04b4;
const int PID=0x0082;

class fx2 {
    
    private:
        libusb_context* libusb_ctx;
        libusb_device_handle* dev_handle;
        int interface,alt_setting;
        
    public:
        fx2();
        ~fx2();
        /**
         * open
         * vid = vendor id
         * pid = product id
         * idx = nth device if there are more than one.
         *
         * Opens device with vid,pid and claims alt 0 of interface 0
         **/
        void open(int vid=VID,int pid=PID, int idx=0);
        void set_interface(int interface, int alt_setting);
        bool isopen() { return dev_handle != NULL; }
        void close();
        /**
         * level n = 0-3
         */
        void set_debug_level(int n);
        int do_usb_command(char* buf, int size, unsigned char type, unsigned char request, unsigned short value, unsigned short index, unsigned short length, int timeout=1000 );
        int clear_halt(char ep);
        int reset();
        int set_configuration(int config);
        bool ep_bulk(char* buf, int size, unsigned char ep, int timeout);

};

#endif
