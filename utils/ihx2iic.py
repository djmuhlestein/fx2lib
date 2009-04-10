#!/usr/bin/env python
#
# Copyright 2009, Ubixum, Inc
#
# This file copied and modified for fx2lib from the GnuRadio project
#
# Copyright 2004,2006 Free Software Foundation, Inc.
# 
# This file is part of GNU Radio
# 
# GNU Radio is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
# 
# GNU Radio is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with GNU Radio; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.
# 

import re
import sys, struct
import os, os.path
from optparse import OptionParser


def hex_to_bytes (s):
    if len (s) & 0x1:
        raise ValueError, "Length must be even"
    r = []
    for i in range (0, len(s), 2):
        r.append (int (s[i:i+2], 16))
    return r
    
def msb (x):
    return (x >> 8) & 0xff

def lsb (x):
    return x & 0xff

class ihx_rec (object):
    def __init__ (self, addr, type, data):
        self.addr = addr
        self.type = type
        self.data = data

class ihx_file (object):
    def __init__ (self):
        self.pat = re.compile (r':[0-9A-F]{10,}')
    def read (self, file):
        r = []
        for line in file:
            line = line.strip().upper ()
            if not self.pat.match (line):
                raise ValueError, "Invalid hex record format"
            bytes = hex_to_bytes (line[1:])
            sum = reduce (lambda x, y: x + y, bytes, 0) % 256
            if sum != 0:
                raise ValueError, "Bad hex checksum"
            lenx = bytes[0]
            addr = (bytes[1] << 8) + bytes[2]
            type = bytes[3]
            data = bytes[4:-1]
            if lenx != len (data):
                raise ValueError, "Invalid hex record (bad length)"
            if type != 0:
                break;
            r.append (ihx_rec (addr, type, data))

        return r


def build_eeprom_image (filename, outfile,vid,pid,devid,cb):
    """Build a ``C2 Load'' EEPROM image.

    For details on this format, see section 3.4.3 of
    the EZ-USB FX2 Technical Reference Manual
    """

    image = [
        0xC2,                           # boot from EEPROM
        lsb (vid),
        msb (vid),
        lsb (pid),
        msb (pid),
        lsb (devid),
        msb (devid),
        cb                               # configuration byte
        ]

    # you could just append all the records..
    # but that would most likely cause a lot of
    # extra headers/addrs to be written
    ihx = ihx_file();
    records = ihx.read(open(filename))

    # create image map of all values we're writing data too
    image_map={}
    for r in records:
        addr=r.addr
        c=0
        l=len(r.data)
        while c<l:
            image_map[addr] = r.data[c]
            addr += 1
            c += 1 
    # now create new records based on contiguous image data 
    max_addr = max(image_map.keys())
    records = []
    start_addr = 0

    while start_addr <= max_addr:
        if not image_map.has_key(start_addr):
            start_addr += 1
            continue
        end_addr = start_addr
        # add continguous data up to 10 bits long (0x3ff)
        # is max size, trm 3.4.3
        size=0
        while image_map.has_key(end_addr) and size < 0x3ff:
            end_addr += 1
            size += 1

        l = end_addr - start_addr
        data = []
        for d in range(l):
            data.append(image_map [ start_addr + d ])
        records.append ( ihx_rec ( start_addr, 0, data ) )
        start_addr = end_addr

    
    # 4 byte header that indicates where to load
    # the immediately follow code bytes.

    for r in records:
        image.extend( [
             msb (len (r.data)),
             lsb (len (r.data)),
             msb (r.addr),
             lsb (r.addr)
             ])
        image.extend(r.data)


    # writes 0 to CPUCS reg (brings FX2 out of reset)
    image.extend (  [
        0x80,
        0x01,
        0xe6,
        0x00,
        0x00
        ] )

    buf=struct.pack ( "B"*len(image), *image )
    print "iic Image Size" , len(buf)
    out=open( outfile, 'w') 
    out.write(buf)
    out.close();

if __name__ == '__main__':
    usage = "usage: %prog [options] firmware.ihx outfile"
    parser = OptionParser (usage=usage)
    parser.add_option ( "-v", "--vid", type="int", default=0x04b4,
                        help="Vendor ID for iic c2 image." )
    parser.add_option ( "-p", "--pid", type="int", default=0x0082,
                        help="Product ID for iic c2 image." )
    parser.add_option ( "-d", "--devid", type="int", default=0,
                        help="Device ID for iic c2 image." )
    parser.add_option ( "-c", "--configbyte", type="int", default=0x04,
                        help="Configuration Byte (i2c & disconnect polarity, default 0x04)" )
    (options, args) = parser.parse_args ()
    if len (args) != 2:
        parser.print_help ()
        sys.exit (1)

    ihx_filename = args[0]
    iic_filename = args[1]
    build_eeprom_image ( ihx_filename, iic_filename, options.vid, options.pid, options.devid, options.configbyte )


