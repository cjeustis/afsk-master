#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdint.h>
#include <string.h>

#include "ax25.h"
#include "aprs_crc.h"

#define DEST_SUB_SSID 0x0B + '0'
#define SOURCE_SUB "APZUME"
#define SOURCE_SUB_SSID 0x00 + '0'
#define L2RA_SUB "WIDE2"
#define L2RA_SUB_SSID 0x01 + '0'

#define CONTROL_FIELD_1 0x03 + '0'
#define CONTROL_FIELD_2 0xF0

char *ax25(char *callSign, char *infoField, char *ax25_frame)
{
	int i;
	int infoFieldLength;
	int frameLength;
	int totalFrameLength;
	uint16_t crc;

	/* Determine length of Info Field string */
	infoFieldLength = strlen(infoField);

	/* Get lengths of ax25 frame */
	totalFrameLength = strlen(ax25_frame);
	frameLength = totalFrameLength - 2;

	/* Set destination subfield of address field */
	for (i = 0; i < 6; ++i)
	{
		ax25_frame[i] = callSign[i];
	}
	ax25_frame[6] = DEST_SUB_SSID;

	/* Set source subfield of address field */
	for (i = 7; i < 13; ++i) {
		ax25_frame[i] = SOURCE_SUB[i-7];
	}
	ax25_frame[13] = SOURCE_SUB_SSID;

	/* Set Layer 2 Repeater Address Subfield of address field */
	for (i = 14; i < 20; ++i) {
		ax25_frame[i] = L2RA_SUB[i-14];
	}
	ax25_frame[20] = L2RA_SUB_SSID;

	/* Add control field */
	ax25_frame[21] = CONTROL_FIELD_1;
	ax25_frame[22] = CONTROL_FIELD_2;

	/* Add Info Field string into frame */
	for (i = 23; i < frameLength; i++) {
		ax25_frame[i] = infoField[i-23];
	}

	/* Calculate CRC */
	crc = calc_crc(ax25_frame, frameLength);

	/* Append crc to end */
	ax25_frame[i] = crc>>8;
	ax25_frame[i+1] = crc & 0xFF;

	return ax25_frame;
}