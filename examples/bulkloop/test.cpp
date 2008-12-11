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
