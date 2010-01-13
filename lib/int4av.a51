; Copyright (C) 2010 Ubixum, Inc. 
;
; This library is free software; you can redistribute it and/or
; modify it under the terms of the GNU Lesser General Public
; License as published by the Free Software Foundation; either
; version 2.1 of the License, or (at your option) any later version.
; 
; This library is distributed in the hope that it will be useful,
; but WITHOUT ANY WARRANTY; without even the implied warranty of
; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
; Lesser General Public License for more details.
; 
; You should have received a copy of the GNU Lesser General Public
; License along with this library; if not, write to the Free Software
; Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

.module INT4AV ; jump table for int4AV (GPIF & endpoint interrupts)

.globl _INT4JT

.area INT4AV (ABS,OVR)
.org    0x53 ; where INT4 jumps to 
_INT4AV = #. + 2
    ljmp _INT2JT ; the addr gets replaced so this really goes to int4jt locations


.area INT4JT ( CODE )
_INT4JT: ; doesn't do anything but forces this module to be linked in if gpif macro used.
