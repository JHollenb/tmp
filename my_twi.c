#include "my_twi.h"

void twi_init()
{
  twi_options_t m_options = {
        .speed     = TWI_SPEED,
        .chip      = TWI_MASTER_ADDR,
        .speed_reg = TWI_BAUD(sysclk_get_cpu_hz(), TWI_SPEED)
    };

    // Internal pull up lines. Used for communicatign between two twi pins
    //TWI_MASTER_PORT.PIN0CTRL = PORT_OPC_WIREDANDPULL_gc;
    //TWI_MASTER_PORT.PIN1CTRL = PORT_OPC_WIREDANDPULL_gc;
    
    irq_initialize_vectors();
    sysclk_enable_peripheral_clock(&TWI_MASTER);
    twi_fast_mode_enable(&TWI_MASTER);
    twi_slave_fast_mode_enable(&TWI_SLAVE);
    twi_master_init(&TWI_MASTER, &m_options);
    twi_master_enable(&TWI_MASTER);
    sysclk_enable_peripheral_clock(&TWI_SLAVE);
}

uint8_t writeBytes(uint8_t reg_addr, uint16_t byte, uint8_t len)
{
    twi_package_t p;
    p.chip = TWI_SLAVE_ADDR;
    p.addr[0] = reg_addr;
    p.addr_length = 1;
    p.buffer= &byte;
    p.length = len;

    
    return twi_master_write(&TWI_MASTER, &p);
}

// Write a single byte to the given register
uint8_t writeByte(uint8_t reg_addr, uint8_t byte)
{
    twi_package_t p;
    p.chip = TWI_SLAVE_ADDR;        // device address
    p.addr[0] = reg_addr;           // register address
    p.addr_length = 1;              // size of reg_address
    p.buffer= &byte;                // data
    p.length = 1;                   // size of data
  
    // twi function
 	return twi_master_write(&TWI_MASTER, &p);
}

// Write a certain length of bits to the device
uint8_t writeBits(uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t data) {
    uint8_t bit;
    if (readByte(regAddr, &bit) != 0) {
        uint8_t mask = ((1 << length) - 1) << (bitStart - length + 1);
        data <<= (bitStart - length + 1);
        data &= mask; 
        bit &= ~(mask); 
        bit |= data; 
        return writeByte(regAddr, bit);
    } else {
        return 0;
    }
}

// Read a requested number of bytes from the device
uint8_t readBytes(uint8_t reg_addr, uint8_t * byte, uint8_t len)
{
    twi_package_t p;
    p.chip = TWI_SLAVE_ADDR;
    p.addr[0] = reg_addr;
    p.addr_length = 1;
    p.buffer = byte;
    p.length = len;

    return twi_master_read(&TWI_MASTER, &p);
}


// Read a single byte from the given register
uint8_t readByte(uint8_t reg_addr, uint8_t * byte)
{
	twi_package_t p;
	p.chip = TWI_SLAVE_ADDR;       // device address
	p.addr[0] = reg_addr;          // register address
	p.addr_length = 1;             // size of register address
	p.buffer = byte;               // where you want data to go
	p.length = 1;                  // size of 1 byte

    // twi function
	return twi_master_read(&TWI_MASTER, &p);
}

