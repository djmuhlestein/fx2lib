Starting a new firmware is easy.

1) The fw should build without modification.

> make # builds firmware.ihx
> make bix # builds firmware.bix
> make iic # builds firmware.iic

2) modify device.c to initialize your device and
   handle data according to your needs.


3) add more sources, gpif data etc.

4) modify the device descriptor (dscr.a51)


For a fast way to deploy, you can use the fx2load
package provided in examples/fx2

