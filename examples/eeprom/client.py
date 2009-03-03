# Copyright (C) 2009 Ubixum, Inc. 
#
# This library is free software; you can redistribute it and/or
#
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
# 
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
# 
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

import sys
from fx2load import *


def get_eeprom(addr,length):
 assert f.isopen()

 prom_val = '';
 while len(prom_val)<length:
     buf='\x00'*1024 # read 1024 bytes max at a time
     transfer_len = length-len(prom_val) > 1024 and 1024 or length-len(prom_val)
     ret=f.do_usb_command ( buf,
         0xc0,
         0xb1,
       addr+len(prom_val),0,transfer_len )
     if (ret>=0):
        prom_val += buf[:ret]
     else: 
        raise Exception("eeprom read didn't work: %d" % ret )
 return prom_val
  
  
def hexchartoint(c):
    return int(c.encode('hex'),16)
  

def fetch_eeprom():
 """
   See TRM 3.4.2, 3.4,3.
   This function dynamically determines how much data to read for c2 eeprom data and downloads
   the eeprom iic file.
 """
 assert f.isopen()
 # fetch 1st 8 bytes
 prom=get_eeprom(0,8)
 if prom[0] == '\xc0':
    return prom # c0 blocks are 8 bytes long
 if prom[0] != '\xc2': raise Exception ( "Envalid eeprom (%s)" % prom[0].encode('hex') )
 # the length of the 1st data block is bytes 8,9 (0 based)
 read_addr=8
 while True:
    size_read = get_eeprom(read_addr,4) # get the data length and start address
    prom += size_read
    read_addr+=4
    # if this is the end 0x80 0x01 0xe6 0x00, then break
    if size_read == '\x80\x01\xe6\x00': break
    # else it is a data block 
    size = (hexchartoint(size_read[0]) << 8) + hexchartoint(size_read[1])
    print "Next eeprom data size %d" % size
    prom += get_eeprom(read_addr,size)
    read_addr+=size
 # one last byte
 prom += get_eeprom(read_addr,1) # should always be 0
 assert prom[-1] == '\x00'
 return prom
 

def set_eeprom(prom):
   assert f.isopen()
   bytes_written=0;
   while bytes_written<len(prom):
        # attemp 1024 at a time
        to_write=len(prom)-bytes_written > 1024 and 1024 or len(prom)-bytes_written
        print "Writing %d Bytes.." % to_write
        ret=f.do_usb_command(prom[bytes_written:bytes_written+to_write], 0x40,0xb1,bytes_written, 0, to_write, 10000)
        if ret>0:
            bytes_written += ret;
        else:
            raise Exception ( "eeprom write didn't work: %d" % ret )
 

if __name__=='__main__':

   openfx2(0x04b4,0x0083) # vid/pid of eeprom firmware 

