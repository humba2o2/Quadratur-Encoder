// Graph-Tech AG
// 02.07.2015
//###########################################################################
//
// FILE:    EncSync.c
//
// TITLE:   Test Program. 
//
// ASSUMPTIONS:
//
//    This program requires the DSP2834x header files.  
//
//    As supplied, this project is configured for "boot to SARAM" 
//    operation.  The 2834x Boot Mode table is shown below.  
//
//         GPIO87   GPIO86     GPIO85   GPIO84
//          XA15     XA14       XA13     XA12
//           PU       PU         PU       PU
//        ==========================================
//            1        1          0        0    I2C-A boot timing 1
//
// DESCRIPTION:
//
// //

#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File


// Prototype statements for functions found within this file.
void 	Gpio_select(void);
void   	I2CA_Init(void);
Uint16 	I2CA_WriteData(struct I2CMSG *msg);
void 	scia_fifo_init(void);

// Interrupt prototyps
interrupt void i2c_int1a_isr(void);
interrupt void sciaTxFifoIsr(void);
interrupt void sciaRxFifoIsr(void);

// defines
#define I2C_NUMBYTES          8

// Global variables

Uint16 	DldCounter;
long 	Download;
char   	far *DldReadMsgPtr;			
char   	far *DldWriteMsgPtr;		

// Global variables
// Two bytes will be used for the outgoing address,
// thus only setup 14 bytes maximum
struct I2CMSG I2cMsgOut1;
struct I2CMSG *CurrentMsgPtr;				// Used in interrupts

void main(void)
{
   Uint16 count    = 0;
   Uint16 iiCCount = 0;
   long wait;
   	
// Step 1. Initialize System Control:
// PLL, WatchDog, enable Peripheral Clocks
// This example function is found in the DSP2834x_SysCtrl.c file.
   InitSysCtrl();
   
// 	Step 2. Initalize GPIO: 
// 	This example function is found in the DSP2834x_Gpio.c file and
// 	illustrates how to set the GPIO to it's default state.
//  InitGpio(); 
 
// 	For this example use the following configuration:
   	Gpio_select();	  

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

// Interrupts that are used in this example are re-mapped to
// ISR functions found within this file.
   EALLOW;	// This is needed to write to EALLOW protected registers
   PieVectTable.I2CINT1A  = &i2c_int1a_isr;
   PieVectTable.SCIRXINTA = &sciaRxFifoIsr;
   EDIS;   // This is needed to disable write to EALLOW protected registers

// Step 4. Initialize all the Device Peripherals:
// This function is found in DSP2834x_InitPeripherals.c

   I2CA_Init();
   scia_fifo_init();  // Init SCI-A

// Step 5. User specific code
	
	DldCounter   	= 0;
	Download		= 0;
	
// Enable interrupts required for this example

   	PieCtrlRegs.PIECTRL.bit.ENPIE 	= 1;   		// Enable the PIE block
   	PieCtrlRegs.PIEIER8.bit.INTx1 	= 1;		// PIE Group 8		IIC
   	PieCtrlRegs.PIEIER9.bit.INTx1	= 1;     	// PIE Group 9

// Enable CPU INT8/9 which is connected to PIE group 8/9
   
   	IER |= M_INT8;
   	IER |= M_INT9;
   
   	EINT;
	
	CurrentMsgPtr 				= &I2cMsgOut1;
	
  	// Application loop
   	for(;;)
   	{
   		if(Download)
   		{	
   			if(--Download == 0)
			{
				I2cMsgOut1.MsgStatus = I2C_MSGSTAT_INACTIVE;
	   		
	    		for(count = 0 ; count < DldCounter ; count += I2C_NUMBYTES)
	   			{
					while(I2cMsgOut1.MsgStatus != I2C_MSGSTAT_INACTIVE)
						;
 	   				
	   				for(wait = 0 ; wait < 0x10000 ; wait++)	// todo wait for eeprom write is done
	   					;
 	   				
	   				I2cMsgOut1.MsgStatus		= I2C_MSGSTAT_SEND_WITHSTOP;
					I2cMsgOut1.SlaveAddress 	= 0x50;
					I2cMsgOut1.MemoryHighAddr 	= (count >> 8) & 0xff;
					I2cMsgOut1.MemoryLowAddr 	= (count >> 0) & 0xff;
					I2cMsgOut1.NumOfBytes		= I2C_NUMBYTES;
					
					DldReadMsgPtr				= (char far *)(0x320000 + count);
					
					for (iiCCount = 0 ; iiCCount < I2C_NUMBYTES ; iiCCount++)
						I2cMsgOut1.MsgBuffer[iiCCount]		= *DldReadMsgPtr++;
	
				    while(I2CA_WriteData(&I2cMsgOut1) != I2C_SUCCESS)
						;
									            
					I2cMsgOut1.MsgStatus 		= I2C_MSGSTAT_WRITE_BUSY;
	      		}
	      		
	      		DldCounter	= 0;
			}
      	}
 
 		// TEST TEST TEST
 		if(GpioDataRegs.GPBDAT.bit.GPIO50)					// A Sig Encoder 1
 		{
			GpioDataRegs.GPCSET.bit.GPIO80		= 1;		// Encoder 1
			GpioDataRegs.GPCSET.bit.GPIO78		= 1;		// Encoder 2
			GpioDataRegs.GPCSET.bit.GPIO77		= 1;		// Encoder 3
			GpioDataRegs.GPCSET.bit.GPIO71		= 1;		// Encoder 4
			GpioDataRegs.GPCSET.bit.GPIO74		= 1;		// Encoder 5
			GpioDataRegs.GPCSET.bit.GPIO73		= 1;		// Encoder 6
			GpioDataRegs.GPCSET.bit.GPIO68		= 1;		// Encoder 7
			GpioDataRegs.GPCSET.bit.GPIO67		= 1;		// Encoder 8
			GpioDataRegs.GPCSET.bit.GPIO64		= 1;		// Encoder 9
 		}
 		else
 		{
			GpioDataRegs.GPCCLEAR.bit.GPIO80	= 1;		// Encoder 1
			GpioDataRegs.GPCCLEAR.bit.GPIO78	= 1;		// Encoder 2
			GpioDataRegs.GPCCLEAR.bit.GPIO77	= 1;		// Encoder 3
			GpioDataRegs.GPCCLEAR.bit.GPIO71	= 1;		// Encoder 4
			GpioDataRegs.GPCCLEAR.bit.GPIO74	= 1;		// Encoder 5
			GpioDataRegs.GPCCLEAR.bit.GPIO73	= 1;		// Encoder 6
			GpioDataRegs.GPCCLEAR.bit.GPIO68	= 1;		// Encoder 7
			GpioDataRegs.GPCCLEAR.bit.GPIO67	= 1;		// Encoder 8
			GpioDataRegs.GPCCLEAR.bit.GPIO64	= 1;		// Encoder 9
 		}
 		
  
 		if(GpioDataRegs.GPADAT.bit.GPIO2)					// Input 1
			GpioDataRegs.GPCSET.bit.GPIO72	= 1;			// PG 1
 	 	else
			GpioDataRegs.GPCCLEAR.bit.GPIO72	= 1;
 
 		if(GpioDataRegs.GPADAT.bit.GPIO9)					// Input 2
 			GpioDataRegs.GPCSET.bit.GPIO81	= 1;			// PG 2
 	 	else
			GpioDataRegs.GPCCLEAR.bit.GPIO81	= 1;
 
 		if(GpioDataRegs.GPADAT.bit.GPIO6)					// Input 3
 			GpioDataRegs.GPCSET.bit.GPIO76	= 1;			// PG 3
 	 	else
			GpioDataRegs.GPCCLEAR.bit.GPIO76	= 1;
 
 		if(GpioDataRegs.GPADAT.bit.GPIO3)					// Input 4
 			GpioDataRegs.GPCSET.bit.GPIO75	= 1;			// PG 4
 	 	else
			GpioDataRegs.GPCCLEAR.bit.GPIO75	= 1;
 		
 		if(GpioDataRegs.GPADAT.bit.GPIO5)					// Input 5
			GpioDataRegs.GPCSET.bit.GPIO70	= 1;			// PG 5
 	 	else
			GpioDataRegs.GPCCLEAR.bit.GPIO70	= 1;
 
 		if(GpioDataRegs.GPADAT.bit.GPIO10)					// Input 6
 			GpioDataRegs.GPCSET.bit.GPIO79	= 1;			// PG 6
 	 	else
			GpioDataRegs.GPCCLEAR.bit.GPIO79	= 1;
 
 		if(GpioDataRegs.GPADAT.bit.GPIO11)					// Input 7
 			GpioDataRegs.GPCSET.bit.GPIO66	= 1;			// PG 7
 	 	else
			GpioDataRegs.GPCCLEAR.bit.GPIO66	= 1;
 
 		if(GpioDataRegs.GPADAT.bit.GPIO8)					// Input 8
 			GpioDataRegs.GPCSET.bit.GPIO69	= 1;			// PG 8
 	 	else
			GpioDataRegs.GPCCLEAR.bit.GPIO69	= 1;
			
		if(GpioDataRegs.GPADAT.bit.GPIO7)					// Input 9
			GpioDataRegs.GPCSET.bit.GPIO65	= 1;			// PG 9
 	 	else
			GpioDataRegs.GPCCLEAR.bit.GPIO65	= 1;
 		
  		GpioDataRegs.GPBTOGGLE.bit.GPIO42    = 1;
    }
} 	

void Gpio_select(void)
{
 	EALLOW;
	
	GpioCtrlRegs.GPAMUX1.all = 0x00000000;  // 00 - 15
	GpioCtrlRegs.GPAMUX2.all = 0x552A0055;  // 16 - 31 
	GpioCtrlRegs.GPBMUX1.all = 0x00000005;  // 32 - 47
	GpioCtrlRegs.GPBMUX2.all = 0x000CF450;  // 48 - 63
	GpioCtrlRegs.GPCMUX1.all = 0x00000000;  // 64 - 79
	GpioCtrlRegs.GPCMUX2.all = 0x00000000;  // 80 - 87

    GpioCtrlRegs.GPADIR.all = 0xA8FEF000;  	// dir
    GpioCtrlRegs.GPBDIR.all = 0xFD13FDFE;   // dir
    GpioCtrlRegs.GPCDIR.all = 0x000FFFFF;   // dir
         
    EDIS;
}

void I2CA_Init(void)
{
   // Initialize I2C
   I2caRegs.I2CSAR 		= 0x050;		// Slave address - EEPROM control code
   I2caRegs.I2CPSC.all 	= 29;   		// Prescaler - need 7-12 Mhz on module clk (300/30 = 10MHz)
   I2caRegs.I2CCLKL 	= 10;			// NOTE: must be non zero
   I2caRegs.I2CCLKH 	= 5;			// NOTE: must be non zero
   
   I2caRegs.I2CIER.all 	= 0x24;			// Enable SCD & ARDY interrupts

   I2caRegs.I2CMDR.all 	= 0x0020;		// Take I2C out of reset
   										// Stop I2C when suspended

   I2caRegs.I2CFFTX.all = 0x6000;		// Enable FIFO mode and TXFIFO
   I2caRegs.I2CFFRX.all = 0x2040;		// Enable RXFIFO, clear RXFFINT,

   return;
}

Uint16 I2CA_WriteData(struct I2CMSG *msg)
{
   Uint16 i;

   // Wait until the STP bit is cleared from any previous master communication.
   // Clearing of this bit by the module is delayed until after the SCD bit is
   // set. If this bit is not checked prior to initiating a new message, the
   // I2C could get confused.
   
   if (I2caRegs.I2CMDR.bit.STP == 1)	return I2C_STP_NOT_READY_ERROR;

   // Setup slave address
   I2caRegs.I2CSAR = 0x050;

   // Check if bus busy
   if (I2caRegs.I2CSTR.bit.BB == 1)		return I2C_BUS_BUSY_ERROR;

   // Setup number of bytes to send
   // MsgBuffer + Address
   I2caRegs.I2CCNT = msg->NumOfBytes+2;

   // Setup data to send
   I2caRegs.I2CDXR = msg->MemoryHighAddr;
   I2caRegs.I2CDXR = msg->MemoryLowAddr;
   
   for (i=0; i<msg->NumOfBytes; i++)
     I2caRegs.I2CDXR = *(msg->MsgBuffer+i);

   // Send start as master transmitter
   I2caRegs.I2CMDR.all = 0x6E20;

   return I2C_SUCCESS;
}

interrupt void i2c_int1a_isr(void)     	// I2C-A
{
   	Uint16 IntSource;

   	IntSource 	= I2caRegs.I2CISRC.all;	// Read interrupt source
   	
   	if(IntSource == I2C_SCD_ISRC)		// Interrupt source = stop condition detected
   	{
      	// If completed message was writing data, reset msg to inactive state
      	if (CurrentMsgPtr->MsgStatus == I2C_MSGSTAT_WRITE_BUSY)
         	CurrentMsgPtr->MsgStatus = I2C_MSGSTAT_INACTIVE;
   	}
   	else 
   	{
   		if(IntSource == I2C_ARDY_ISRC)
   		{
     		if(I2caRegs.I2CSTR.bit.NACK == 1)
      		{
      		   	I2caRegs.I2CMDR.bit.STP = 1;
      		   	I2caRegs.I2CSTR.all 	= I2C_CLR_NACK_BIT;
      		}
   		}  // end of register access ready
   	}
   	// Enable future I2C (PIE Group 8) interrupts
   	PieCtrlRegs.PIEACK.all = PIEACK_GROUP8;
}

interrupt void sciaTxFifoIsr(void)
{
	SciaRegs.SCIFFTX.bit.TXFFINTCLR	 =1;					// Clear SCI Interrupt flag
	PieCtrlRegs.PIEACK.all			|= PIEACK_GROUP9;      	// Issue PIE ACK
}

interrupt void sciaRxFifoIsr(void)
{   
	char data;
	
	data	= SciaRegs.SCIRXBUF.all;	 // Read data

	if(DldCounter == 0)
	{
		if(data != 0xAA)	// Download Start
			DldCounter	= 0;
		else
		{
			DldWriteMsgPtr	= (char far *)(0x320000);

			*DldWriteMsgPtr++ = data;
			DldCounter++;				
		}
	}
	else
	{
		*DldWriteMsgPtr++ = data;
		DldCounter++;				
	}

	if(DldCounter)
		Download 	= 0x10000;
		
	SciaRegs.SCIFFRX.bit.RXFFOVRCLR		= 1;   // Clear Overflow flag
	SciaRegs.SCIFFRX.bit.RXFFINTCLR		= 1;   // Clear Interrupt flag

	PieCtrlRegs.PIEACK.all				|= PIEACK_GROUP9;       // Issue PIE ack
}

void scia_fifo_init()
{
   SciaRegs.SCICCR.all 					= 0x0007;   // 1 stop bit,  No loopback
                                  					// No parity,8 char bits,
                                  					// async mode, idle-line protocol
   SciaRegs.SCICTL1.all 				= 0x0003;  	// enable TX, RX, internal SCICLK,
                                  					// Disable RX ERR, SLEEP, TXWAKE
   SciaRegs.SCICTL2.bit.TXINTENA 		= 1;
   SciaRegs.SCICTL2.bit.RXBKINTENA 		= 1;
   SciaRegs.SCIHBAUD 					= 0x0000;
   //SciaRegs.SCILBAUD 					= SCI_PRD;

   SciaRegs.SCILBAUD 					= 81;		// 115200

   SciaRegs.SCICCR.bit.LOOPBKENA 		= 0; 		// Disable loop back
   SciaRegs.SCIFFTX.all					= 0xC021;
   SciaRegs.SCIFFRX.all					= 0x0021;
   SciaRegs.SCIFFCT.all					= 0x00;

   SciaRegs.SCICTL1.all 				= 0x0023;   // Relinquish SCI from Reset
   SciaRegs.SCIFFTX.bit.TXFIFOXRESET	= 1;
   SciaRegs.SCIFFRX.bit.RXFIFORESET		= 1;
}     
//===========================================================================
// No more.
//===========================================================================

