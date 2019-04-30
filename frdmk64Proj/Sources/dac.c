/*
 * dac.c
 *
 *  Created on: Mar 14, 2019
 *      Author: Alex Everett, Dylan Steen
 */

#ifndef SOURCES_DAC_C_
#define SOURCES_DAC_C_
#include "fsl_device_registers.h"
#include "uart.h"


void setUpDac(void) {
	// Enable clock to DAC0
	SIM_SCGC2 |= SIM_SCGC2_DAC0_MASK;
	// Enable DAC0
	DAC0_C0 |= DAC_C0_DACEN_MASK;
	// Select Reference voltage
	DAC0_C0 |= DAC_C0_DACRFS(1);
}

void sendToDac(unsigned short toSend) {
	// Convert the short to a low and high component to send to the DAC
	unsigned char low = toSend;
	// If we were actually doing math right, it would be a shift by 8. This, for some reason,
	// Exceeds the capabilities of our circuit and melts the Op-Amp. So, just don't exceed that number
	unsigned char high = toSend >> 7;

	// Send to DAC
	DAC0_DAT0L = low;
	DAC0_DAT0H = high;
}
#endif /* SOURCES_DAC_C_ */
