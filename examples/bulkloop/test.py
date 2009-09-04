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
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USAimport struct


import struct 

from fx2load import *

openfx2(0x04b4,0x1004)


def do_bulk():
    # send 100 shorts to ep2
    
    buf=struct.pack ( 'H'*100, *[i for i in range(100)] )
    f.ep_bulk( buf, 0x02, 1000)
    
    # read them back out
    buf='\x00'*200  
    f.ep_bulk( buf, 0x86, 1000)
    

    print struct.unpack ( 'H'*100, buf )
    
[do_bulk() for i in range(3)]
