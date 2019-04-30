/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * main.c
 *
 *  Created on: Mar 22, 2019
 *      Author: Dylan Steen, Alex Everett
 */


#include "fsl_device_registers.h"
#include "stdlib.h"
#include "timer.h"
#include "uart.h"
#include "adc.h"
#include "timer.h"
#include "alarm.h"
#include "dac.h"
#include "accelerometer.h"
#include "gpio.h"
#include "uart.h"

#define samplesPerAvg 10

//unsigned int ZERO_MOVEMENT_MAG = 221; // Calculated by doing square root of sum of squares at rest for all 3 components in x direction
unsigned int ZERO_MOVEMENT_MAG = 239; // Calculated by doing square root of sum of squares at rest
int threshold = 5;

unsigned int recentMovement[samplesPerAvg];
// 300 = 1 average per second * 60 seconds per minute * 5 minutes. We're storing last 5 minutes to determine if they're sleeping
unsigned int recentAverages[300];

// Globals counters for the small and large buffers
int recentAverageCounter = 0;
int recentMovementCounter = 0;
int rollover = 0;

// Boolean alarm signal
int shouldSoundAlarm = 0;
int totalSleep = 0;


// Simple arithmetic mean of recent movement calculates average of values in small buffer
unsigned int calcAverage() {
	unsigned int sum = 0;
	unsigned int result = 0;
	for (int i=0; i<samplesPerAvg; ++i) {
		sum += recentMovement[i];
	}


	if (sum != 0) {
		result = sum / samplesPerAvg;
	}

	return result;
}

// Arithmetic mean of averages (large buffer), and see if user is sleeping or not
void determineSleeping(void) {
	unsigned int sum = 0;
	float avg = 0;

	for (int i=0; i<300; ++i) {
		sum += recentAverages[i];
	}

	// Avoid dividing by zero
	if (sum != 0) {
		avg = (float)sum / 300.0;
	}

	// If compute average less than predefined "this much movement means you're awake" threshold,
	// Then you're asleep so increment total sleep counter.
	if (avg < threshold) {
		totalSleep += 5;
	}
}


//
void analyzeMovementReading(unsigned int movement) {
	// Only compute average and send to Python program the average of last 10 samples
	if (recentMovementCounter >= samplesPerAvg) {
		recentMovementCounter = 0;
		rollover++;

		// get average of last 10 samples
		unsigned int averageLastN = calcAverage();
		recentAverages[recentAverageCounter] = averageLastN;

		++recentAverageCounter;

		// send average of last 10 samples to Python program
		sendChar(averageLastN);
		// Check if Python program sent alarm signal
		shouldSoundAlarm = receiveChar();

		// Every 300 samples, compute average of averages and determine if user sleeping
		if (recentAverageCounter == 300) {
			recentAverageCounter = 0;
			determineSleeping();
		}
	}

	// Place movement into buffer to be averaged
	recentMovement[recentMovementCounter] = movement;
	++recentMovementCounter;
}
// Contains all "init" functions to set up modules to be used.
void initialize(void) {
    setUpUart();
    setUpAdc();
    ftmInit();
    setUpDac();
    setUpGpio();
    turnOnLed();
}

int main(void) {
    // Set up all modules
    initialize();

    // Set PORTB pins for input for ADC input channels
    PORTB_PCR10 |= PORT_PCR_MUX(0);
    GPIOB_PDDR = 0;

	unsigned char xMovement;
	unsigned char yMovement;
	unsigned char zMovement;
	unsigned int movementMag;
	int done = 0;

	// Loop until alarm has been activated and turned off
	while(!done) {
	    // Delay for 10000 microseconds (10ms)
		myDelay(10000);
		// Read in all 3 directions
		xMovement = readX();
		yMovement = readY();
		zMovement = readZ();

		// Because of the bidirectionality of the movement, a value of 127 is 0g.
		// Also, gravity will effect at least one direction.
		// Therefore, we need to normalize the magnitude by the pre-measured magnitude of the vector when
		// The device is at rest.

		// Calculate the magnitude by doing square root sum of the squares.
		movementMag = calcMag(xMovement, yMovement, zMovement) - ZERO_MOVEMENT_MAG;

		// Anything bigger than 140 is almost certainly an error due to wires disconnecting
		if (movementMag < 140) {
			analyzeMovementReading(movementMag);
		} else {
			analyzeMovementReading(0);
		}

		// Once we receive the sound alarm signal from the python program, sound the alarm and then exit.
		if (shouldSoundAlarm) {
			soundAlarm2();
			done = 1;
		}
	}
}





