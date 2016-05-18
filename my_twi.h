#ifndef _MY_TWI_H
#define _MY_TWI_H

#include <stdio.h>
#include <stdint.h>
#include <asf.h>
#include "vt100.h"


#define TWI_MASTER       	TWIC
#define TWI_MASTER_PORT  	PORTC
#define TWI_SLAVE        	TWIC
#define TWI_SPEED        	400000
#define TWI_MASTER_ADDR  	0x50
#define TWI_SLAVE_ADDR   	0x68


void twi_init(void);

uint8_t writeBytes(uint8_t reg_addr, uint16_t byte, uint8_t len);
uint8_t writeByte(uint8_t reg_addr, uint8_t byte);
uint8_t writeBits(uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t data);

uint8_t readBytes(uint8_t reg_addr, uint8_t * byte, uint8_t len);
uint8_t readByte(uint8_t reg_addr, uint8_t * byte);

#endif