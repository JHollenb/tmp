/* vt100.h */

#ifndef VT100_H_
#define VT100_H_

#define PRINTS(arg)							puts(arg)
#define VT100_INIT()						{VT100_HOME();VT100_CLEAR();VT100_HIDE_CURSOR();}
#define VT100_ESC 							"\x1b"
#define VT100_HOME() 						PRINTS(VT100_ESC "[H")
#define VT100_CLEAR() 						PRINTS(VT100_ESC "[2J")
#define VT100_HIDE_CURSOR() 				PRINTS(VT100_ESC "[?25l")
#define VT100_POS(row, col)					PRINTS(VT100_ESC "[" #row ";" #col "H")
#define VT100_prints(row, col, str)			printf("\x1b[" #row ";" #col "H" str )
#define VT100_printf(row, col, fmt,...)		printf("\x1b[" #row ";" #col "H" fmt , __VA_ARGS__)

#endif /* VT100_H_ */