#include "MPU6050_Functions.h"

// Buffer to hold data from twi
static uint8_t buffer[BUFFER_SIZE];

// Set the clock source
static void set_ClockSource(uint8_t source) {
    writeBits(MPU6050_RA_PWR_MGMT_1, MPU6050_PWR1_CLKSEL_BIT, MPU6050_PWR1_CLKSEL_LENGTH, source);
}

// Control resolution of gyro
static void set_GyroRange(uint8_t range) {
    writeBits(MPU6050_RA_GYRO_CONFIG, MPU6050_GCONFIG_FS_SEL_BIT, MPU6050_GCONFIG_FS_SEL_LENGTH, range);
}

// Control resolution of accel
static void set_AccelRange(uint8_t range) {
    writeBits(MPU6050_RA_ACCEL_CONFIG, MPU6050_ACONFIG_AFS_SEL_BIT, MPU6050_ACONFIG_AFS_SEL_LENGTH, range);
}

// Need to control sleep status
static void set_SleepEnabled(uint8_t val) {
    writeBits(MPU6050_RA_PWR_MGMT_1, MPU6050_PWR1_SLEEP_BIT, 1, val);
}


// Can use to normalize Accel
static void set_ZAccelOffset(int16_t offset) {
    writeBytes(MPU6050_RA_ZA_OFFS_H, offset, 2);
}


// Set data rate for accel
static void set_Rate(uint8_t rate) {
    writeByte(MPU6050_RA_SMPLRT_DIV, rate);
}

// Clear LCD screen
void clearScreen(void)
{
	gfx_mono_init();
}


// Display 8 bits
void display_8X(uint8_t x)
{
  	char string[20];
  	sprintf(string, "x: 0x%X", x);
  	gfx_mono_draw_string(string, 0, 0, &sysfont);
  	
}

// Display 16 bits
void display_16X(uint16_t val, uint8_t x, uint8_t y)
{
	char string[20];
  	sprintf(string, "%03d", val);
  	gfx_mono_draw_string(string, x, y, &sysfont);
}

/* To init MPU6050, need to do 3 things, first set clock source,
next set the sensitivity, finally turn off default sleep mode */
void MPU6050_init(void) {
	// Read that the GYRO clock is slightly better than default clock
    set_ClockSource(0x1);

    // Set sensitivity of both accel and gyro
    set_Sensitivity(4);

    // Disable the default sleep mode
    set_SleepEnabled(0x0); 

    // Default offset is 1, so need to apply an offset of 1
    set_ZAccelOffset(0x1);
}

// Set data to 0 
void init_6AxisData(accel_6AxisData_t * p)
{
	p->ax = 0;
	p->ay = 0;
	p->az = 0;
	p->gx = 0;
	p->gy = 0;
	p->gz = 0;
	p->tmp = 0;
}

// Control sensitivity level from 1 to 4;
/* 	GYRO RATINGS
	0 = 250
	1 = 500
	2 = 1000
	3 = 2000

	ACCEL RATINGS
	0 = 131
	1 = 65.5 
	2 = 32.8
	3 = 16.4
*/	

void set_Sensitivity(uint8_t level) {
	switch(level){
		case 1:
			set_GyroRange(MPU6050_GYRO_FS_2000);
    		set_AccelRange(MPU6050_ACCEL_FS_16);
			break;
		case 2:
    		set_GyroRange(MPU6050_GYRO_FS_1000);
    		set_AccelRange(MPU6050_ACCEL_FS_8);
			break;
		case 3:
    		set_GyroRange(MPU6050_GYRO_FS_500);
    		set_AccelRange(MPU6050_ACCEL_FS_4);
			break;
		case 4:
    		set_GyroRange(MPU6050_GYRO_FS_250);
    		set_AccelRange(MPU6050_ACCEL_FS_2);
			break;
		default:
			set_GyroRange(MPU6050_GYRO_FS_2000);
    		set_AccelRange(MPU6050_ACCEL_FS_16);
    		break;
	}
}

/* Grab data from MPU beginning at 0x3B. Each takes up 16 bits so:
	0x3B AX
	0x3D AY
	0x3F AZ
	0x41 
	0x43 GX
	0x45 GY
	0x47 GZ
*/
void get_6AxisData(accel_6AxisData_t * p)
{
	readBytes(MPU6050_RA_ACCEL_XOUT_H, buffer, BUFFER_SIZE);
	// Want to see negative values so data is converted to int
	p->ax = ((((int16_t)buffer[0]) << 8) | buffer[1])/SCALE; 		// SCALE = 1000
    p->ay = ((((int16_t)buffer[2]) << 8) | buffer[3])/SCALE;
    p->az = ((((int16_t)buffer[4]) << 8) | buffer[5])/SCALE;
    
    p->gx = ((((int16_t)buffer[8]) << 8) | buffer[9])/SCALE;
    p->gy = ((((int16_t)buffer[10]) << 8) | buffer[11])/SCALE;
    p->gz = ((((int16_t)buffer[12]) << 8) | buffer[13])/SCALE;
}

void print_6AxisData(accel_6AxisData_t * p)
{
	char string[20];
  	sprintf(string, "AX: %03d", p->ax);
  	gfx_mono_draw_string(string, 0, 0, &sysfont);
  	sprintf(string, "AY: %03d", p->ay);
  	gfx_mono_draw_string(string, 0, 10, &sysfont);
  	sprintf(string, "AZ: %03d", p->az);
  	gfx_mono_draw_string(string, 0, 20, &sysfont);

  	sprintf(string, "GX: %03d", p->gx);
  	gfx_mono_draw_string(string, 62, 0, &sysfont);
  	sprintf(string, "GY: %03d", p->gy);
  	gfx_mono_draw_string(string, 62, 10, &sysfont);
  	sprintf(string, "GZ: %03d", p->gz);
  	gfx_mono_draw_string(string, 62, 20, &sysfont);
}

