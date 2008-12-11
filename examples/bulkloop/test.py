import struct
from fx2load import *

openfx2(0x04b4,0x1004)

# send 100 shorts to ep2

buf=struct.pack ( 'H'*100, *[i for i in range(100)] )
f.ep_bulk( buf, 0x02, 1000)

# read them back out
buf='\x00'*200  
f.ep_bulk( buf, 0x86, 1000)

print struct.unpack ( 'H'*100, buf )
