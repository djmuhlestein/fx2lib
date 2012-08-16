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
#include <cstdio>
#include <cassert>
#include <libusb-1.0/libusb.h>
#include <cstring>

int main(int argc __attribute__((unused)),
	char **argv __attribute__((unused)))
{
	int transferred, rv, i, hdlidx;
	libusb_context* ctx;
	unsigned char buf[256];
	libusb_device_handle *hndl[2];
	ssize_t devcount;
	struct libusb_device_descriptor desc;

	libusb_device **devlist;
	libusb_init(&ctx);

	devcount = libusb_get_device_list(ctx, &devlist);

	for(i = 0, hdlidx = 0; i < devcount && hdlidx < 2; i++) {
		if (libusb_get_device_descriptor(devlist[i], &desc) != 0)
			continue;

		if (desc.idVendor == 0x04b4 && desc.idProduct == 0x8613) {
			if (!(libusb_open(devlist[i], &hndl[hdlidx]))) {
				printf("opened device %d\n", hdlidx);
				hdlidx++;
			}
		}
			
	}

	if (hdlidx != 2) {
		fprintf(stderr, "Need two devices, have %d\n", hdlidx);
		return 1;
	}

	libusb_claim_interface(hndl[0],0);
	libusb_claim_interface(hndl[1],0);

	libusb_set_interface_alt_setting(hndl[0], 0, 0);
	libusb_set_interface_alt_setting(hndl[1], 0, 0);

	for (i = 0; i < (int)sizeof(buf); i++)
		buf[i] = i;

	printf("OUT transfer to device 0, PIPE 2\n");
	rv = libusb_bulk_transfer(hndl[0], 0x02, buf, sizeof(buf), &transferred, sizeof(buf));

	if(rv)
		printf("OUT Transfer failed: %d\n", rv);

	printf("IN transfer to device 1, PIPE 6\n");

	memset(buf, 0, sizeof(buf));
	transferred = 0;

	rv=libusb_bulk_transfer(hndl[1], 0x86, (unsigned char*)buf ,sizeof(buf), &transferred, sizeof(buf));
	if(rv)
		printf("IN Transfer failed: %d\n", rv);

	printf("received %d bytes:\n", transferred);

	for (i = 0; i < transferred; i++)
		printf ("%02x ", buf[i]);
	printf("\n");

	printf("OUT transfer to device 1, PIPE 2\n");
	rv = libusb_bulk_transfer(hndl[1], 0x02, buf, sizeof(buf), &transferred, sizeof(buf));

	if(rv)
		printf("OUT Transfer failed: %d\n", rv);

	printf("IN transfer to device 0, PIPE 6\n");

	memset(buf, 0, sizeof(buf));
	transferred = 0;

	rv=libusb_bulk_transfer(hndl[0], 0x86, (unsigned char*)buf ,sizeof(buf), &transferred, sizeof(buf));
	if(rv)
		printf("IN Transfer failed: %d\n", rv);

	printf("received %d bytes:\n", transferred);

	for (i = 0; i < transferred; i++)
		printf ("%02x ", buf[i]);
	printf("\n");

	libusb_free_device_list(devlist, 1);
	libusb_close(hndl[0]);
	return 0;
}
