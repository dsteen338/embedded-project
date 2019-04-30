/*
 * dac.h
 *
 *  Created on: Mar 14, 2019
 *      Author: dsteen
 */

#ifndef SOURCES_DAC_H_
#define SOURCES_DAC_H_

/// Initializes the DAC
void setUpDac(void);

/// @param toSend an unsigned 16 bit value to write out to the DAC, corresponding to a voltage between 0-3.3V.
void sendToDac(unsigned short toSend);

#endif /* SOURCES_DAC_H_ */
