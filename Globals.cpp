#include "LedController.hpp"
#include <Globals.h>

const int LED_TURNON = 32;
const int LED_1 = 26;
const int LED_2 = 33;

const int BTN_1 = 18;
const int BTN_2 = 19;

const int BTN_PLUS = 23;
const int BTN_MINUS = 21;
const int BTN_OK = 22;

const bool SERIAL_ENABLED = true;


/* we always wait a bit between updates of the display */
unsigned long delaytime=1000;

LedController<1,1> lc;
