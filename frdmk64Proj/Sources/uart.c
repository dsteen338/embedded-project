/*
 * uart.c
 *
 *  Created on: Mar 2, 2019
 *      Author: Dylan Steen, Alex Everett
 */

#include "fsl_device_registers.h"

void setUpUart(void) {

	// Enable clock to module
	SIM_SCGC4 |= SIM_SCGC4_UART0_MASK;
	SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;
	// Multiplex pins
	PORTB_PCR16 |= PORT_PCR_MUX(3);
	PORTB_PCR17 |= PORT_PCR_MUX(3);

	// Turn off TE and RE
	UART0_C2 &= ~(UART_C2_TE_MASK);
	UART0_C2 &= ~(UART_C2_RE_MASK);

	//Set Baud Rate to 9600
	UART0_BDH |= 0x0;
	UART0_BDL |= 0x88;

	//Re-enable TE and RE
	UART0_C2 |= UART_C2_TE_MASK;
	UART0_C2 |= UART_C2_RE_MASK;

}

void sendChar(char toSend) {
	// Monitor Transmit data register empty flag
	while(!(UART0_S1 & UART_S1_TDRE_MASK));
	// Send data
	UART0_D = toSend;
}
char receiveChar(void) {
	// Monitor receive data register full flag
	while(!(UART0_S1 & UART_S1_RDRF_MASK));
	// Receive data
	char received = UART0_D;
	return received;
}

// This is used for debugging only.
// ASCII values are offset 48 from their digit values.
unsigned char charNumberToAscii(unsigned char inputChar) {
	return inputChar + 48;
}

// This is used for debugging only.
// Send digits of the number one by 1 over followed by newline UART to print the number inputted
// only works for 3 digit numbers.
void sendCharNumberToUart(unsigned int toOutput) {
	if (toOutput > 99) {
		sendChar(charNumberToAscii(toOutput / 100));
	}

	if (toOutput > 9) {
		sendChar(charNumberToAscii((toOutput % 100) / 10));
	}

	sendChar(charNumberToAscii(toOutput % 10));
	sendChar('\n');
	sendChar('\r');
}

void sendString(char* stringToSend) {
	char* ptrCopy = stringToSend;

	// Iterate until null terminator reached (end of string)
	while(*ptrCopy != 0) {
		sendChar(*ptrCopy);
		++ptrCopy;
	}

	// Send newline
	sendChar('\n');
	sendChar('\r');
}
