/*
 * adc.h
 *
 *  Created on: Mar 2, 2019
 *      Author: aeverett
 */

#ifndef SOURCES_ADC_H_
#define SOURCES_ADC_H_

/// Initializes ADC1
void setUpAdc(void);

/// @return an unsigned value between 0-256 corresponding to a positive voltage read between 0-3.3V from ADC1 channel 15
unsigned char readAdc1Ch15(void);
/// @return an unsigned value between 0-256 corresponding to a positive voltage read between 0-3.3V from ADC1 channel 14
unsigned char readAdc1Ch14(void);
/// @return an unsigned value between 0-256 corresponding to a positive voltage read between 0-3.3V from ADC1 channel 18
unsigned char readAdc1Ch18(void);
#endif /* SOURCES_ADC_H_ */
