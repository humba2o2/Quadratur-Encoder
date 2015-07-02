//###########################################################################
// Patrick Walther, 21.04.2015 gpio setup for led and buttons
//###########################################################################


#ifndef __GPIOSETUP__
#define __GPIOSETUP__

#include "DSP28x_Project.h"
#include "DSP2834x_Gpio.h"
#include "DSP2834x_Examples.h"

#define ALEADING 0x60
#define BLEADING 0x90
#define STANDARTPWMCLK 5000 // Define PWM standart clk
#define INVERTED ALEADING		// Encoder signal A is leading (change to BLEADING for B as the leading signal)

void gpioSetup(void);
void scia_echoback_init(void);
void scia_fifo_init(void);
void scia_xmit(int a);
void scia_msg(char *msg);
char scia_get_char(void);

#endif /*  __GPIOSETUP__ */
