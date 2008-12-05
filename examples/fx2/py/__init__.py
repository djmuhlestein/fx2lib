from time import sleep
from fx2 import fx2

f=fx2.fx2()

# use this functions 1st

def opendefault(vid=0x04b4,pid=0x0082):
    f.open(vid,pid)

def reset_device(reset):
 print reset and "Put device in reset" or "Set device to run"
 write_ram (0xe600,reset and '\x01' or '\x00', 1)
 
def write_ram(addr,data,length):
 transferred=0
 while(transferred<length):
  this_transfer_size=length-transferred>1024 and 1024 or length-transferred
  buf=data[transferred:]
  ret=f.do_usb_command( buf,
    0x40,
    0xa0,
    addr+transferred, 0,
    this_transfer_size )
  if (ret>0):
   print "wrote %d bytes" % ret
   transferred+=ret
  else:
   print "Error: %d" % ret
   return

def reset_bix(filename):
 """
  Use this function to reset your firmware.  You'll need to reopen the device afterward.
 """
 reset_device(True)
 bix=open(filename).read()
 print "loading bix file of length: %d" % len(bix) 
 write_ram( 0, bix,len(bix) );
 reset_device(False)
 print "Closing device after reset"
 f.close();

