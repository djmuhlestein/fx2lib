/**
 * Copyright (C) 2009 Ubixum, Inc.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 **/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <libusb-1.0/libusb.h>


int main(int argc __attribute__((unused)),
	 char **argv __attribute__((unused)))
{
	int transferred, rv, i, ret = 1;;
	libusb_device_handle *hndl;
	libusb_context *ctx;
	unsigned char buf[512];


	libusb_init(&ctx);

	hndl = libusb_open_device_with_vid_pid(ctx, 0x4b4, 0x8613);

	if (!hndl) {
		fprintf(stderr, "failed to open device\n");
		goto out;
	}

	libusb_claim_interface(hndl, 0);

	libusb_set_interface_alt_setting(hndl, 0, 0);

for(;;) {
	for (i = 0; i < (int)sizeof(buf); i++)
		buf[i] = i;

	printf("OUT transfer to device\n");
	transferred = 0;
	rv = libusb_bulk_transfer(hndl, 0x02, bufl, 32, &transferred, 500);
	if(rv) {
		fprintf(stderr, "OUT Transfer failed: %d (%d transferred)\n", rv, transferred);
//		goto out;
	}

	rv = libusb_bulk_transfer(hndl, 0x02, buf, 0, &transferred, 500);
	if(rv) {
		fprintf(stderr, "OUT0 Transfer failed: %d (%d transferred)\n", rv, transferred);
//		goto out;
	}

	printf("IN transfer to device\n");

	memset(buf, 0, sizeof(buf));
	transferred = 0;

	rv=libusb_bulk_transfer(hndl, 0x86, (unsigned char*)buf ,sizeof(buf), &transferred, 500);
	if(rv) {
		fprintf(stderr, "IN Transfer failed: %d (%d transferred)\n", rv, transferred);
//			goto out;
	} else {
			printf("received %d bytes:\n", transferred);

			for (i = 0; i < transferred; i++)
				printf ("%02x ", buf[i]);
			printf("\n");
	}
	sleep(1);
}
	ret = 0;
out:
	libusb_close(hndl);
	return ret;
}
