#include <asf.h>
#include "vt100.h"
#include "MPU6050_Functions.h"

int main(void)
{ 
	const usart_serial_options_t usart_serial_options = {
		.baudrate   = 38400,
		.charlength = USART_CHSIZE_8BIT_gc,
		.paritytype = USART_PMODE_DISABLED_gc,
		.stopbits   = false, /* No extra stopbit */
	};

	
	sysclk_init();
	board_init();
	gfx_mono_init();
	
	// My functions
	twi_init();
	MPU6050_init();

	// Set sensitivity 1=lowest, 4=highest
	set_Sensitivity(4);

	/* UART link with board controller */
	stdio_serial_init(&USARTD0, &usart_serial_options);

	// VT100 stuff
	VT100_INIT();

	// create structure
	accel_6AxisData_t data;

	// init 6 axis data to 0
	init_6AxisData(&data);

	while (true) {
		
		get_6AxisData(&data);
		print_6AxisData(&data);
		
			
		/*
		VT100_printf(10,10,"AX: %03d",data.ax);
		VT100_printf(12,10,"AY: %03d",data.ay);
		VT100_printf(14,10,"AZ: %03d",data.az);

		VT100_printf(10,30,"GX: %03d",data.gx);
		VT100_printf(12,30,"GY: %03d",data.gy);
		VT100_printf(14,30,"GZ: %03d",data.gz);		
		//*/
	}
}

