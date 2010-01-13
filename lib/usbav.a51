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

.module INT2AV ; jump table for usb auto vector

.globl _INT2JT ; defined as global so this assembly gets included in project 

.area INT2AV (ABS,OVR)
.org    0x43 ; this is where USBINT ( interrupt 8 ) jumps to
_INT2AV = #. + 2 ; two bytes for ljmp (auto set by INT2IVEC)
    ljmp _INT2JT

; INT2 Jump Table

.area INT2JT ( CODE )
;.org    0x1A00 ; needs to be on a page boundary

_INT2JT:
    ljmp _sudav_isr
    .db 0
    ljmp _sof_isr
    .db 0
    ljmp _sutok_isr
    .db 0
    ljmp _suspend_isr
    .db 0
    ljmp _usbreset_isr
    .db 0
    ljmp _hispeed_isr
    .db 0
    ljmp _ep0ack_isr
    .db 0
    ljmp _spare_isr
    .db 0
    ljmp _ep0in_isr
    .db 0
    ljmp _ep0out_isr
    .db 0
    ljmp _ep1in_isr
    .db 0
    ljmp _ep1out_isr
    .db 0
    ljmp _ep2_isr
    .db 0
    ljmp _ep4_isr
    .db 0
    ljmp _ep6_isr
    .db 0
    ljmp _ep8_isr
    .db 0
    ljmp _ibn_isr
    .db 0
    ljmp _spare_isr
    .db 0
    ljmp _ep0ping_isr
    .db 0
    ljmp _ep1ping_isr
    .db 0
    ljmp _ep2ping_isr
    .db 0
    ljmp _ep4ping_isr
    .db 0
    ljmp _ep6ping_isr
    .db 0
    ljmp _ep8ping_isr
    .db 0
    ljmp _errlimit_isr
    .db 0
    ljmp _spare_isr
    .db 0
    ljmp _spare_isr
    .db 0
    ljmp _spare_isr
    .db 0
    ljmp _ep2isoerr_isr
    .db 0
    ljmp _ep4isoerr_isr
    .db 0
    ljmp _ep6isoerr_isr
    .db 0
    ljmp _ep8isoerr_isr
    .db 0
; INT4JT
    ljmp _ep2pf_isr
    .db 0
    ljmp _ep4pf_isr
    .db 0
    ljmp _ep6pf_isr
    .db 0
    ljmp _ep8pf_isr
    .db 0
    ljmp _ep2ef_isr
    .db 0
    ljmp _ep4ef_isr
    .db 0
    ljmp _ep6ef_isr
    .db 0
    ljmp _ep8ef_isr
    .db 0
    ljmp _ep2ff_isr
    .db 0
    ljmp _ep4ff_isr
    .db 0
    ljmp _ep6ff_isr
    .db 0
    ljmp _ep8ff_isr
    .db 0
    ljmp _gpifdone_isr
    .db 0
    ljmp _gpifwf_isr
    .db 0
    
