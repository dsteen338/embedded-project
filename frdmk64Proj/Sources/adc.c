/*
 * adc.c
 *
 *  Created on: Mar 2, 2019
 *      Author: Alex Everett, Dylan Steen
 */

#include "fsl_device_registers.h"
#include "timer.h"

void setUpAdc(void) {
	// Enable clock to module
	SIM_SCGC3 |= SIM_SCGC3_ADC1_MASK;
}

unsigned char readAdc1Ch14() {
	// Enable channel
	ADC1_SC1A = ADC_SC1_ADCH(14);

	// Monitor COCO
	while(!(ADC1_SC1A & ADC_SC1_COCO_MASK));

	// read from ADC
	return ADC1_RA;
}

unsigned char readAdc1Ch15() {
	// Enable channel
	ADC1_SC1A = ADC_SC1_ADCH(15);

	// Monitor COCO
	while(!(ADC1_SC1A & ADC_SC1_COCO_MASK));

	// read from ADC
	return ADC1_RA;
}

unsigned char readAdc1Ch18(void) {
	// Enable channel
	ADC1_SC1A = ADC_SC1_ADCH(18);

	// Monitor COCO
	while(!(ADC1_SC1A & ADC_SC1_COCO_MASK));

	// read from ADC
	return ADC1_RA;
}


