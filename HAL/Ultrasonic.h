/*
 *  @file ultrasonic.h
 *  Created: 12/6/2023 10:05:07 PM
 *  @Author: Abdelrahman Ramadan 
 *  @brief Header file for Ultrasonic Sensor Module
 *  This file contains declarations of functions and typedefs required
 *  for interfacing with ultrasonic sensors.
 */ 


#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_



#define MAX_TIME      2000
#define TRIGG_DELAY   10
/**
 * @brief Enum representing different ultrasonic sensor pins
 *
 * This enum represents different ultrasonic sensor pins, each
 * corresponding to a specific pin on the microcontroller.
 */
typedef enum{
    US1 = PINC5, /**< Ultrasonic Sensor 1 pin */
    US2 = PINC4, /**< Ultrasonic Sensor 2 pin */
    US3 = PINC3, /**< Ultrasonic Sensor 3 pin */
    US4 = PINC2  /**< Ultrasonic Sensor 4 pin */
} ULTRASONIC_type;

/**
 * @brief Initializes the ultrasonic sensor module
 *
 * This function initializes the necessary configurations for
 * using the ultrasonic sensor module.
 */
void ultrasonic_Init ();

/**
 * @brief Measures the distance using an ultrasonic sensor
 *
 * This function measures the distance using an ultrasonic sensor
 * specified by the parameter `us`. The measured distance is stored
 * in the memory location pointed by `dist`.
 *
 * @param us Ultrasonic sensor to be used for distance measurement
 * @param dist Pointer to the variable where the distance measurement will be stored
 * @return Returns 1 if the distance measurement is successful, 0 otherwise
 */
u8 ultrasonic_GetDistance(ULTRASONIC_type us, u8 *dist);

#endif /* ULTRASONIC_H_ */