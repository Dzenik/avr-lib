
#include <avr/pgmspace.h>

#include "crc8_elsy.h"

static uint8_t elsy_crc_tbl[256] PROGMEM =
{
	0x00, 0xa9, 0xfb, 0x52, 0x5f, 0xf6, 0xa4, 0x0d,
	0xbe, 0x17, 0x45, 0xec,	0xe1, 0x48, 0x1a, 0xb3,
	0xd5, 0x7c, 0x2e, 0x87, 0x8a, 0x23, 0x71, 0xd8,
	0x6b, 0xc2, 0x90, 0x39, 0x34, 0x9d, 0xcf, 0x66,
	0x03, 0xaa, 0xf8, 0x51,	0x5c, 0xf5, 0xa7, 0x0e,
	0xbd, 0x14, 0x46, 0xef, 0xe2, 0x4b, 0x19, 0xb0,
	0xd6, 0x7f, 0x2d, 0x84, 0x89, 0x20, 0x72, 0xdb,
	0x68, 0xc1, 0x93, 0x3a,	0x37, 0x9e, 0xcc, 0x65,
	0x06, 0xaf, 0xfd, 0x54, 0x59, 0xf0, 0xa2, 0x0b,
	0xb8, 0x11, 0x43, 0xea, 0xe7, 0x4e, 0x1c, 0xb5,
	0xd3, 0x7a, 0x28, 0x81,	0x8c, 0x25, 0x77, 0xde,
	0x6d, 0xc4, 0x96, 0x3f, 0x32, 0x9b, 0xc9, 0x60,
	0x05, 0xac, 0xfe, 0x57, 0x5a, 0xf3, 0xa1, 0x08,
	0xbb, 0x12, 0x40, 0xe9,	0xe4, 0x4d, 0x1f, 0xb6,
	0xd0, 0x79, 0x2b, 0x82, 0x8f, 0x26, 0x74, 0xdd,
	0x6e, 0xc7, 0x95, 0x3c, 0x31, 0x98, 0xca, 0x63,
	0x0c, 0xa5, 0xf7, 0x5e,	0x53, 0xfa, 0xa8, 0x01,
	0xb2, 0x1b, 0x49, 0xe0, 0xed, 0x44, 0x16, 0xbf,
	0xd9, 0x70, 0x22, 0x8b, 0x86, 0x2f, 0x7d, 0xd4,
	0x67, 0xce, 0x9c, 0x35,	0x38, 0x91, 0xc3, 0x6a,
	0x0f, 0xa6, 0xf4, 0x5d, 0x50, 0xf9, 0xab, 0x02,
	0xb1, 0x18, 0x4a, 0xe3, 0xee, 0x47, 0x15, 0xbc,
	0xda, 0x73, 0x21, 0x88,	0x85, 0x2c, 0x7e, 0xd7,
	0x64, 0xcd, 0x9f, 0x36, 0x3b, 0x92, 0xc0, 0x69,
	0x0a, 0xa3, 0xf1, 0x58, 0x55, 0xfc, 0xae, 0x07,
	0xb4, 0x1d, 0x4f, 0xe6,	0xeb, 0x42, 0x10, 0xb9,
	0xdf, 0x76, 0x24, 0x8d, 0x80, 0x29, 0x7b, 0xd2,
	0x61, 0xc8, 0x9a, 0x33, 0x3e, 0x97, 0xc5, 0x6c,
	0x09, 0xa0, 0xf2, 0x5b,	0x56, 0xff, 0xad, 0x04,
	0xb7, 0x1e, 0x4c, 0xe5, 0xe8, 0x41, 0x13, 0xba,
	0xdc, 0x75, 0x27, 0x8e, 0x83, 0x2a, 0x78, 0xd1,
	0x62, 0xcb, 0x99, 0x30,	0x3d, 0x94, 0xc6, 0x6f
};

uint8_t calc_crc(const void *data, uint8_t len);
uint8_t update_crc(uint8_t data, uint8_t crc);

unsigned char elsy_make_crc(const void *data, unsigned char len)
{
	const unsigned char* const p = (unsigned char *)data;
	unsigned char crc;
	unsigned char i;

	crc = 0;
	for (i = 0; i < len; i++)
	{
		crc = pgm_read_byte(&(elsy_crc_tbl[p[i]^crc]));
	}
	return crc;
}

uint8_t calc_crc(const void *data, uint8_t len) {
	uint8_t crc;

	crc = 0;
	for (;len > 0; --len) {
		crc = update_crc(*(uint8_t*)data++, crc)
	}
	return crc;
}

uint8_t update_crc(uint8_t data, uint8_t crc) {
	return pgm_read_byte(&(elsy_crc_tbl[data^crc]));
}