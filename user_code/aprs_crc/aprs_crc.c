#include <stdio.h>
#include <stdint.h>

#include "aprs_crc.h"

#define POLY 0x8408
#define LSB 0x0001

uint16_t calc_crc(char *data, int length)
{
	int i;
	int j;
	uint16_t crc_reg = 0xFFFF;

	/* No data so return zeros */
	if (length == 0)
	    return (~crc_reg);

	/* Loop through each byte */
	for (i = 0; i < length; i++) {
		/* Loop through each bit */
		for (j=0; j < 8; j++, data[i] >>= 1) {
			if ((crc_reg & LSB) ^ (data[i] & LSB))
				crc_reg = (crc_reg >> 1) ^ POLY;
          			else
          				crc_reg >>= 1;
	    	}
	}
	/* Return 1's complement */
	return (~crc_reg);
}