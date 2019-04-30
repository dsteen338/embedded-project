/*
 * accelerometer.c
 *
 *  Created on: Mar 22, 2019
 *      Author: Alex Everett, Dylan Steen
 */
#include "adc.h"
#include "math.h"

// 127 = 0g
const unsigned char ZERO_MOVEMENT = 127;
unsigned char convertMovementIfNegative(unsigned char movement);

// PTB10 - ADC1CH14
unsigned char readX(void) {
	return convertMovementIfNegative(readAdc1Ch14());
}

// PTB11 - ADC1CH115
unsigned char readY(void) {
	return convertMovementIfNegative(readAdc1Ch15());

}

// ADC1_SE18 - ADC1CH18
unsigned char readZ(void) {
	return convertMovementIfNegative(readAdc1Ch18());
}

// Calc magnitude by doing square root of the sum of squares.
unsigned int calcMag(unsigned char x, unsigned char y, unsigned char z) {
	unsigned int squares = x*x+y*y+z*z;
	unsigned int squareRoot = sqrt(squares);
	return squareRoot;
}

// Since we don't care about direction (-1g and 1g are the same for our purposes)
// Convert any negative acceleration to its equivalent positive acceleration.
unsigned char convertMovementIfNegative(unsigned char movement) {
	if (movement < ZERO_MOVEMENT) {
		return (ZERO_MOVEMENT - movement) + ZERO_MOVEMENT;
	} else {
		return movement;
	}
}
