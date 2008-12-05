
#ifndef FX2_H
#define FX2_H

#include <libusb-1.0/libusb.h>

const int VID=0x04b4;
const int PID=0x0082;

class fx2 {
    
    private:
        libusb_context* libusb_ctx;
        libusb_device_handle* dev_handle;
        
    public:
        fx2();
        ~fx2();
        
        void open(int vid=VID,int pid=PID);
        bool isopen() { return dev_handle != NULL; }
        void close();
        int do_usb_command(char* buf, int size, unsigned char type, unsigned char request, unsigned short value, unsigned short index, unsigned short length );
        bool ep_bulk(char* buf, int size, unsigned char ep, int timeout);

};

#endif
