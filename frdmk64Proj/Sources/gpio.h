/*
 * gpio.h
 *
 *  Created on: Mar 22, 2019
 *      Author: dsteen
 */

#ifndef SOURCES_GPIO_H_
#define SOURCES_GPIO_H_


/// turns on the Red LED
void turnOnLed(void);

/// Initializes the GPIO module for use with the button and Red LED
void setUpGpio(void);

/// @return a nonzero value (true) if the button has been pressed, otherwise 0
int checkButton(void);


#endif /* SOURCES_GPIO_H_ */
