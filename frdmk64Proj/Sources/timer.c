/*
 * timer.c
 *
 *  Created on: Mar 4, 2019
 *      Author: Dylan Steen, Alex Everett
 */

#include "fsl_device_registers.h"
#include "timer.h"

// Clock frequency defined in the system header file
#define CLOCK_FREQUENCY 20971520.0
// Max 16 bit unsigned val = 2^16
#define MAX_16_BIT_VAL 65536.0

void ftmInit(void) {
	// Enable clock to FTM0
	SIM_SCGC6 |= SIM_SCGC6_FTM0_MASK;
	// Enable clock to PORTA, PORTB, and PORTC
	SIM_SCGC5 |= (SIM_SCGC5_PORTA_MASK | SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTC_MASK);

	// Set PORTC1 to FTM
	PORTC_PCR1|=PORT_PCR_MUX(4);

	// Turn on FTM and disable write protection
	FTM0_MODE |= (FTM_MODE_FTMEN_MASK | FTM_MODE_WPDIS_MASK);
	// Set up Mod value to be max value
	FTM0_MOD |= FTM_MOD_MOD(0xFFFF);
	// Select clock to be system clock (20971520Hz)
	FTM0_SC |= FTM_SC_CLKS(1);
}


void myDelay(int waitTimeMicros) {
	int overflows = 0;

	// Convert microseconds to seconds
	float waitTimeSeconds = (float)waitTimeMicros/1000000.0;
	float cycles = CLOCK_FREQUENCY*waitTimeSeconds;

	// Reset counter to 0
	FTM0_CNTIN = 0x0;
	FTM0_CNT = 0x0;

	// Loop until # of cycles has passed
	// Since 1 overflow = 2^16 cycles,
	// numOverflows * 2^16 + current value in counter = total cycles passed
	while (overflows*MAX_16_BIT_VAL + FTM0_CNT < cycles) {
		// Check overflow bit
		if (FTM0_SC & FTM_SC_TOF_MASK) {
			// If overflow bit = 1, overflow occurred so increment counter
			++overflows;
			// Reset overflow bit
			FTM0_SC &= ~(FTM_SC_TOF_MASK);
		}
	}
}
