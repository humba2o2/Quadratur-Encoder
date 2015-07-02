//###########################################################################
// Patrick Walther, 21.04.2015 gpio setup for led and buttons
// everything is copyed from TI examples
//###########################################################################

#include <own_gpio_setup.h>
#include <EPWM_handling.h>

Uint16 LoopCount;
Uint16 ErrorCount;

void gpioSetup(void) {
	// Setup LED/buttons

	EALLOW;

	// Outputs (LEDs)
	GpioCtrlRegs.GPBPUD.bit.GPIO44 = 1;  	// Disable pullup on GPIO44
	GpioDataRegs.GPBCLEAR.bit.GPIO44 = 1;  	// Load output latch
	GpioCtrlRegs.GPBMUX1.bit.GPIO44 = 0;
	GpioCtrlRegs.GPBDIR.bit.GPIO44 = 1;  	// GPIO44 = output

	GpioCtrlRegs.GPBPUD.bit.GPIO45 = 1;  	// Disable pullup on GPIO45
	GpioDataRegs.GPBCLEAR.bit.GPIO45 = 1;  	// Load output latch
	GpioCtrlRegs.GPBMUX1.bit.GPIO45 = 0;
	GpioCtrlRegs.GPBDIR.bit.GPIO45 = 1;  	// GPIO45 = output

	GpioCtrlRegs.GPBPUD.bit.GPIO46 = 1;  	// Disable pullup on GPIO46
	GpioDataRegs.GPBCLEAR.bit.GPIO46 = 1;  	// Load output latch
	GpioCtrlRegs.GPBMUX1.bit.GPIO46 = 0;
	GpioCtrlRegs.GPBDIR.bit.GPIO46 = 1;  	// GPIO46 = output

	GpioCtrlRegs.GPBPUD.bit.GPIO47 = 1;  	// Disable pullup on GPIO47
	GpioDataRegs.GPBCLEAR.bit.GPIO47 = 1;  	// Load output latch
	GpioCtrlRegs.GPBMUX1.bit.GPIO47 = 0;
	GpioCtrlRegs.GPBDIR.bit.GPIO47 = 1; 	// GPIO47 = output

	// Inputs (BUTTONs)
	GpioCtrlRegs.GPBPUD.bit.GPIO36 = 1;  	// Disable pullup on GPIO36
	GpioDataRegs.GPBCLEAR.bit.GPIO36 = 1;  	// Load output latch
	GpioCtrlRegs.GPBMUX1.bit.GPIO36 = 0;
	GpioCtrlRegs.GPBDIR.bit.GPIO36 = 0;  	// GPIO36 = output

	GpioCtrlRegs.GPBPUD.bit.GPIO37 = 1;  	// Disable pullup on GPIO37
	GpioDataRegs.GPBCLEAR.bit.GPIO37 = 1;  	// Load output latch
	GpioCtrlRegs.GPBMUX1.bit.GPIO37 = 0;
	GpioCtrlRegs.GPBDIR.bit.GPIO37 = 0;  	// GPIO76 = output

	GpioCtrlRegs.GPBPUD.bit.GPIO38 = 1;  	// Disable pullup on GPIO38
	GpioDataRegs.GPBCLEAR.bit.GPIO38 = 1;  	// Load output latch
	GpioCtrlRegs.GPBMUX1.bit.GPIO38 = 0;
	GpioCtrlRegs.GPBDIR.bit.GPIO38 = 0;  	// GPIO38 = output

	GpioCtrlRegs.GPBPUD.bit.GPIO39 = 1;  	// Disable pullup on GPIO39
	GpioDataRegs.GPBCLEAR.bit.GPIO39 = 1;  	// Load output latch
	GpioCtrlRegs.GPBMUX1.bit.GPIO39 = 0;
	GpioCtrlRegs.GPBDIR.bit.GPIO39 = 0;  	// GPIO39 = Input
	EDIS;

	// Rotary enc A
	GpioCtrlRegs.GPAPUD.bit.GPIO24 = 1;  // Enable pullup on GPIO24
	GpioDataRegs.GPACLEAR.bit.GPIO24 = 1;  // Load output latch
	GpioCtrlRegs.GPAMUX2.bit.GPIO24 = 0;
	GpioCtrlRegs.GPADIR.bit.GPIO24 = 0;  // GPIO24 = Input
	GpioDataRegs.GPACLEAR.bit.GPIO24 = 1;  // Load output latch

	// Rotary enc B
	GpioCtrlRegs.GPAPUD.bit.GPIO25 = 1;  // Enable pullup on GPIO25
	GpioDataRegs.GPACLEAR.bit.GPIO25 = 1;  // Load output latch
	GpioCtrlRegs.GPAMUX2.bit.GPIO25 = 0;
	GpioCtrlRegs.GPADIR.bit.GPIO25 = 0;  // GPIO25 = Input
	GpioDataRegs.GPACLEAR.bit.GPIO25 = 1;  // Load output latch

	// Rotary enc PUSH
	GpioCtrlRegs.GPAPUD.bit.GPIO26 = 1;  // Enable pullup on GPIO26
	GpioDataRegs.GPACLEAR.bit.GPIO26 = 1;  // Load output latch
	GpioCtrlRegs.GPAMUX2.bit.GPIO26 = 0;
	GpioCtrlRegs.GPADIR.bit.GPIO26 = 0;  // GPIO26 = Input
	GpioDataRegs.GPACLEAR.bit.GPIO26 = 1;  // Load output latch

	InitEQep1Gpio();	// EQEP 1A/B init
	InitEPwm1Gpio();	// Setup EPWM1
	InitEPwm2Gpio();	// Setup EPwM2
	InitSciaGpio();		// Setup UART
	EPwmSetup(STANDARTPWMCLK, INVERTED);		// Start EPWM

	// Init uart
	scia_fifo_init();	   // Initialize the SCI FIFO
	scia_echoback_init();  // Initalize SCI for echoback
}

// Test 1,SCIA  DLB, 8-bit word, baud rate 0x000F, default, 1 STOP bit, no parity
void scia_echoback_init() {
	// Note: Clocks were turned on to the SCIA peripheral
	// in the InitSysCtrl() function

	SciaRegs.SCICCR.all = 0x0007;   // 1 stop bit,  No loopback
									// No parity,8 char bits,
									// async mode, idle-line protocol
	SciaRegs.SCICTL1.all = 0x0003;  // enable TX, RX, internal SCICLK,
									// Disable RX ERR, SLEEP, TXWAKE
	SciaRegs.SCICTL2.all = 0x0003;
	SciaRegs.SCICTL2.bit.TXINTENA = 1;
	SciaRegs.SCICTL2.bit.RXBKINTENA = 1;
#if (CPU_FRQ_300MHZ)
	SciaRegs.SCIHBAUD = 0;  // 115200 baud @LSPCLK = 75.0MHz.
	SciaRegs.SCILBAUD = 81;
#endif
#if (CPU_FRQ_250MHZ)
	SciaRegs.SCIHBAUD =0x0003;  // 9600 baud @LSPCLK = 62.5MHz.
	SciaRegs.SCILBAUD =0x002D;
#endif
#if (CPU_FRQ_200MHZ)
	SciaRegs.SCIHBAUD =0x0002;  // 9600 baud @LSPCLK = 50.0MHz.
	SciaRegs.SCILBAUD =0x008A;
#endif
	SciaRegs.SCICTL1.all = 0x0023;  // Relinquish SCI from Reset
}

// Transmit a character from the SCI
void scia_xmit(int a) {
	while (SciaRegs.SCIFFTX.bit.TXFFST != 0) {
	}
	SciaRegs.SCITXBUF = a;

}

void scia_msg(char * msg) {
	int i;
	i = 0;
	while (msg[i] != '\0') {
		scia_xmit(msg[i]);
		i++;
	}
}

// Initalize the SCI FIFO
void scia_fifo_init() {
	SciaRegs.SCIFFTX.all = 0xE040;
	SciaRegs.SCIFFRX.all = 0x204f;
	SciaRegs.SCIFFCT.all = 0x0;
}

char scia_get_char (void){
	Uint16 ReceivedChar;
	// Handle UART
	// If character arrives
	if (SciaRegs.SCIFFRX.bit.RXFFST == 1) {

		// Get character
		ReceivedChar = SciaRegs.SCIRXBUF.all;
		LoopCount++;
		return ReceivedChar;
	} else {
		return 0;
	}
}
