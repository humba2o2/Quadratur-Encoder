#include <DSP28x_Project.h>		// For some init functions
#include <DSP2834x_Examples.h>	// Some example functions
#include <freqcalc.h>			// Freq meassuring
#include <own_gpio_setup.h>		// Own init function and TI init function calls
#include <EPWM_handling.h>		// EPWM setup function to change frequency
#include <stdio.h>				// sprintf()

// Defines
#define STANDART_ENC_DELAY 10000	// Standart delay for the enc signal to prevent bad positions of the rotary encoder.
#define MIN_ENC_OUT_SPEED	5000	// Minimal encoder speed
#define MAX_ENC_OUT_SPEED	5000000	// Maximal encoder speed

#define UP		1
#define DOWN 	0
#define HIGH 	1
#define LOW		0

// Prototype statements for functions found within this file.
void evalRotaryEnc(void);
unsigned long long evalpwmClk(int upDown);

// Global virable for the clock speed
unsigned long long pwmClk = STANDARTPWMCLK; // Initial frequency defined in own_gpio_setup
// Global msg pointer for SCI msg's
char *msg;
// Global variable to hold what signal is actually leading
char inv = ALEADING;
// Global variable to hold the status of the rotary encoder signals
int rotaryAPos = 0;
int rotaryBPos = 0;

// Init standart
FREQCAL freq=FREQCAL_DEFAULTS;

void main(void) {

// Step 1. Initialize System Control:
// PLL, WatchDog, enable Peripheral Clocks
// This example function is found in the DSP2834x_SysCtrl.c file.
	InitSysCtrl();

// Step 2. Initalize GPIO:
	gpioSetup();

	///* This is only to test the external 24V encoder
	EALLOW;
	GpioCtrlRegs.GPCPUD.bit.GPIO73 = 1;  	// Disable pullup on GPIO44
	GpioDataRegs.GPCCLEAR.bit.GPIO73 = 1;  	// Load output latch
	GpioCtrlRegs.GPCMUX1.bit.GPIO73 = 0;
	GpioCtrlRegs.GPCDIR.bit.GPIO73 = 1;  	// GPIO44 = output
	EDIS;
	GpioDataRegs.GPCCLEAR.bit.GPIO73 = 1;
	//*/

// Step 3. Clear all interrupts and initialize PIE vector table:
// Disable CPU interrupts
	DINT;

// Initialize PIE control registers to their default state.
// The default state is all PIE interrupts disabled and flags
// are cleared.
// This function is found in the DSP2834x_PieCtrl.c file.
	InitPieCtrl();

// Disable CPU interrupts and clear all CPU interrupt flags:
	IER = 0x0000;
	IFR = 0x0000;

// Initialize the PIE vector table with pointers to the shell Interrupt
// Service Routines (ISR).
// This will populate the entire table, even if the interrupt
// is not used in this example.  This is useful for debug purposes.
// The shell ISR routines are found in DSP2834x_DefaultIsr.c.
// This function is found in DSP2834x_PieVect.c.
	InitPieVectTable();

	// Send startup msg
	msg = "\r\nStartin QuadratorEncoderIPA\0";
	scia_msg(msg);

	freq.init(&freq);

	for (;;) {

		// Output Frequency and direction meassuring if BUTTON 1 is pressed
		if(GpioDataRegs.GPBDAT.bit.GPIO36 == HIGH){
			// Calculated frequency
			freq.calc(&freq);

			// Get calculated frequency and direction
			unsigned long long fr =  (unsigned long long)freq.freqhz_pr;
			unsigned long long direction = (unsigned long long)freq.direction;

			scia_msg("\r\n\n\n###################################################\0");
			msg[0] = '\0';
			// Send meassured frequency
			scia_msg("\r\nMeassured frequency: \0");
			msg[0] = '\0';
			while (msg[0] == '\0') {
				sprintf(msg, "%llu", fr);
			}
			scia_msg(msg);

			// Send direction to PC
			if(direction == UP){
				scia_msg("\r\nDirection: Signal A is leading");
			} else {
				scia_msg("\r\nDirection: Signal B is leading");
			}
			scia_msg("\r\n###################################################\0");
			msg[0] = '\0';
			while(GpioDataRegs.GPBDAT.bit.GPIO36 == HIGH){};
		}

		// Read rotary enc
		evalRotaryEnc();
	}

}

void evalRotaryEnc(void) {

	// If the first high signal to appear is "A", A is leading -> Set A = High and wait for B (else if case)
	if ((GpioDataRegs.GPADAT.bit.GPIO24 == LOW) && (rotaryBPos == LOW)
			&& (rotaryAPos == LOW)) {
		rotaryAPos = HIGH;
	} else if ((GpioDataRegs.GPADAT.bit.GPIO24 == LOW) && (rotaryBPos == HIGH)
			&& (rotaryAPos == LOW)) {

		/*
		 * If A is leading, we count the encoder speed up.
		 * First i send the old encoder speed to the pc, then i check if there is an overflow (speed = 5'000'000),
		 * if so i set the speed to 5000 instead of going higher. If not i increment the speed logarithmically.
		 * That means that i always add 1/10 of the actual decade. e.g -> 2'000'000 -> + 100'000
		 * this is done in the evalpwmClk function.
		 * After that i send the new speed to the pc and re-init the epwm-module with the new speed.
		 * To prevent intermediate positions i check twice with a 10ms delay if both signals are low
		 */
		scia_msg("\r\n\n\n###################################################\0");
		msg[0] = '\0';

		scia_msg("\r\nEncoder going up\0");
		scia_msg("\r\nOld Encoder speed: \0");
		msg[0] = '\0';
		while (msg[0] == '\0') {
			sprintf(msg, "%llu", pwmClk);
		}
		scia_msg(msg);
		if (pwmClk < MAX_ENC_OUT_SPEED) {
			pwmClk += evalpwmClk(UP);
		} else {
			pwmClk = MIN_ENC_OUT_SPEED;
		}
		scia_msg("\r\nNew Encoder speed: \0");
		msg[0] = '\0';
		while (msg[0] == '\0') {
			sprintf(msg, "%llu", pwmClk);
		}
		scia_msg(msg);

		scia_msg("\r\n###################################################\0");
		msg[0] = '\0';

		EPwmSetup(pwmClk, inv);
		while (((GpioDataRegs.GPADAT.bit.GPIO24 == LOW)
				|| (GpioDataRegs.GPADAT.bit.GPIO25 == LOW))) {
			DELAY_US(STANDART_ENC_DELAY);
			while (((GpioDataRegs.GPADAT.bit.GPIO24 == LOW)
					|| (GpioDataRegs.GPADAT.bit.GPIO25 == LOW))) {
				DELAY_US(STANDART_ENC_DELAY);
			};
		};
		rotaryAPos = LOW;
		rotaryBPos = LOW;

	}

	// If the first high signal to appear is "B", B is leading -> Set B = High and wait for A (else if case)
	if ((GpioDataRegs.GPADAT.bit.GPIO25 == LOW) && (rotaryAPos == LOW)
			&& (rotaryBPos == LOW)) {
		rotaryBPos = HIGH;
	} else if ((GpioDataRegs.GPADAT.bit.GPIO25 == LOW) && (rotaryAPos == HIGH)
			&& (rotaryBPos == LOW)) {

		/*
		 * If B is leading, we count the encoder speed down.
		 * First i send the old encoder speed to the pc, then i check if there is an underflow (speed = 5'000),
		 * if so i set the speed to 5'000'000 instead of going down. If not i decrement the speed logarithmically.
		 * That means that i always remove 1/10 of the actual decade. e.g -> 2'000'000 -> - 100'000
		 * this is done in the evalpwmClk function.
		 * After that i send the new speed to the pc and re-init the epwm-module with the new speed.
		 * To prevent intermediate positions i check twice with a 10ms delay if both signals are low
		 */

		scia_msg("\r\n\n\n###################################################\0");
		msg[0] = '\0';

		scia_msg("\r\nEncoder going down\0");
		scia_msg("\r\nOld Encoder speed: \0");
		msg[0] = '\0';
		while (msg[0] == '\0') {
			sprintf(msg, "%llu", pwmClk);
		}
		scia_msg(msg);
		if (pwmClk > MIN_ENC_OUT_SPEED) {
			pwmClk -= evalpwmClk(DOWN);
		} else {
			pwmClk = MAX_ENC_OUT_SPEED;
		}
		scia_msg("\r\nNew Encoder speed: \0");
		msg[0] = '\0';
		while (msg[0] == '\0') {
			sprintf(msg, "%llu", pwmClk);
		}
		scia_msg(msg);

		scia_msg("\r\n###################################################\0");
		msg[0] = '\0';

		EPwmSetup(pwmClk, inv);
		DELAY_US(STANDART_ENC_DELAY);
		while (((GpioDataRegs.GPADAT.bit.GPIO24 == LOW)
				|| (GpioDataRegs.GPADAT.bit.GPIO25 == LOW))) {
		};
		DELAY_US(STANDART_ENC_DELAY);
		while (((GpioDataRegs.GPADAT.bit.GPIO24 == LOW)
				|| (GpioDataRegs.GPADAT.bit.GPIO25 == LOW))) {
		};
		rotaryAPos = LOW;
		rotaryBPos = LOW;
	}

	/*
	 * Here im reading the push button of the rotary encoder. If the button is high,
	 * i chage the leading signal to trailing. After that i re-init the epwm modul
	 * with the new configuration.
	 */
	if (GpioDataRegs.GPADAT.bit.GPIO26 == HIGH) {

		scia_msg("\r\n\n\n###################################################\0");
		msg[0] = '\0';

		scia_msg("\r\nEncoder push pressed\0");
		if (inv == BLEADING) {
			inv = ALEADING;
			scia_msg("\r\nEncoder b nacheilend\0");
		} else {
			inv = BLEADING;
			scia_msg("\r\nEncoder a nacheilend\0");
		}

		scia_msg("\r\n###################################################\0");
		msg[0] = '\0';

		EPwmSetup(pwmClk, inv);
		DELAY_US(STANDART_ENC_DELAY);
		while (GpioDataRegs.GPADAT.bit.GPIO26) {
		};


	}
}


/*
 * This function returns the amount the encoder has to
 * increase/decrease every step depending on the actual speed
 */
unsigned long long evalpwmClk(int upDown) {
	if (upDown) {
		if (pwmClk < 10000) {
			return 1000;
		} else if (pwmClk < 100000) {
			return 10000;
		} else if (pwmClk < 1000000) {
			return 100000;
		} else {
			return 100000;
		}
	} else {
		if (pwmClk <= 10000) {
			return 1000;
		} else if (pwmClk <= 100000) {
			return 10000;
		} else if (pwmClk <= 1000000) {
			return 100000;
		} else {
			return 100000;
		}
	}
}
