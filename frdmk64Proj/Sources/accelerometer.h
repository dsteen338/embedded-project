/*
 * accelerometer.h
 *
 *  Created on: Mar 22, 2019
 *      Author: aeverett
 */

#ifndef SOURCES_ACCELEROMETER_H_
#define SOURCES_ACCELEROMETER_H_

/// @return the acceleration in the x direction of the accelerometer
unsigned char readX(void);
/// @return the acceleration in the y direction of the accelerometer
unsigned char readY(void);
/// @return the acceleration in the z direction of the accelerometer
unsigned char readZ(void);

/**
 *
 * @param x a vector in the x direction
 * @param y a vector in the y direction
 * @param z z verctor in the z direction
 * @return the magnitude of the combined vector
 */
unsigned int calcMag(unsigned char x, unsigned char y, unsigned char z);


#endif /* SOURCES_ACCELEROMETER_H_ */
