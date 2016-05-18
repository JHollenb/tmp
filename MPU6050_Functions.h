#ifndef _MPU6050_FUNCTIONS_H_
#define _MPU6050_FUNCTIONS_H_

#include <stdio.h>
#include <stdint.h>
#include <asf.h>

#include "MPU6050.h"
#include "vt100.h"
#include "my_twi.h"


#define BUFFER_SIZE			14
#define SCALE				1000

// Contains device data
typedef struct{
	uint16_t ax;
	uint16_t ay;
	uint16_t az;
	uint16_t gx;
	uint16_t gy;
	uint16_t gz;
	uint16_t tmp;
} accel_6AxisData_t;


// Used to display values on LCD screen
void display_16X(uint16_t val, uint8_t x, uint8_t y);
void display_8X(uint8_t x);
void clearScreen(void);

// Accel basic function
void MPU6050_init(void);

// Set 6 axis to 0
void init_6AxisData(accel_6AxisData_t * p);

// Print 6 axis to LCD
void print_6AxisData(accel_6AxisData_t * p);

// Get the data from the accelerometer
void get_6AxisData(accel_6AxisData_t * p);

// Set the sensitivty range
void set_Sensitivity(uint8_t level);

#endif