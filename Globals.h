#ifndef GLOBALS_H
#define GLOBALS_H

#include "LedController.hpp"

extern const int LED_TURNON;
extern const int LED_1;
extern const int LED_2;

extern const int BTN_1;
extern const int BTN_2;

extern const int BTN_PLUS;
extern const int BTN_MINUS;
extern const int BTN_OK;

extern const bool SERIAL_ENABLED;


/* we always wait a bit between updates of the display */
extern unsigned long delaytime;


/*
 You might need to change the following 3 Variables depending on your board.
 pin 15 is connected to the DataIn
 pin 14 is connected to the CLK
 pin 13 is connected to LOAD/ChipSelect
*/
#define DIN 15
#define CS 13
#define CLK 14

/*
 Now we need a LedController Variable to work with.
 We have only a single MAX72XX so the Dimensions are 1,1.
 */
extern LedController<1,1> lc;

#endif
