/*
 * gpio.c
 *
 *  Created on: Mar 22, 2019
 *      Author: Dylan Steen, Alex Everett
 */


#include "fsl_device_registers.h"

void setUpGpio(void) {
	// Send clock to ports C,B, and E
	SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;
	SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;
	SIM_SCGC5 |= SIM_SCGC5_PORTE_MASK;

	// Select ALT1 on these ports for the LED and the button
	PORTC_PCR6 |= PORT_PCR_MUX(1);
	PORTB_PCR22 |= PORT_PCR_MUX(1);

	// Set LED to output
	GPIOB_PDDR |= 0x01 << 22;

	// Turn off LED
	GPIOB_PSOR |= 0x01 << 22;

}

// Turns on red LED
void turnOnLed(void) {
	// Write to PTB22, which is red LED
	GPIOB_PCOR |= 0x01 << 22;
}

// Checks if button2 is pressed
int checkButton(void) {
	// Check PTC6, which is button2
	return GPIOC_PDIR & 0x40;
}

