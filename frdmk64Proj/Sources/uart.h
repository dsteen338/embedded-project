/*
 * uart.h
 *
 *  Created on: Mar 2, 2019
 *      Author: aeverett
 */

#ifndef SOURCES_UART_H_
#define SOURCES_UART_H_

/**
 *
 * @param inputChar a digit between 0-9 represented by it's actual value
 * @return the same digit, but encoded as ASCII
 */
unsigned char charNumberToAscii(unsigned char inputChar);

/// Initializes the UART0 module
void setUpUart(void);

/// @param toSend a char to send to the UART0 module
void sendChar(char toSend);

/// @return a character read from the UART0 module
char receiveChar(void);
/// @param toOutput an unsigned number between 0-999 to display on the PUTTY (or similar) interface
void sendCharNumberToUart(unsigned int toOutput);

/// @param stringToSend a string to send to the UART0 module
void sendString(char* stringToSend);


#endif /* SOURCES_UART_H_ */
