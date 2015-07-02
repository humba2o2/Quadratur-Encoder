// TI File $Revision: /main/2 $
// Checkin $Date: July 31, 2009   09:55:52 $
//###########################################################################
//
// FILE:	Example_freqcal.h
//
// TITLE:	Frequency measurement using EQEP peripheral
//
// DESCRIPTION:
//
// Header file containing data type and object definitions and
// initializers.
//
//###########################################################################
// Original Author: SD
//
// $TI Release: DSP2834x C/C++ Header Files V1.10 $
// $Release Date: July 27, 2009 $
//###########################################################################

#ifndef __FREQCAL__
#define __FREQCAL__

#include <IQmathLib.h>         // Include header for IQmath library
/*-----------------------------------------------------------------------------
 Define the structure of the FREQCAL Object
 -----------------------------------------------------------------------------*/
typedef struct {
	Uint32 freqScaler_pr; 	// Parameter : Scaler converting 1/N cycles to a GLOBAL_Q freq (Q0) - independently with global Q
	Uint32 BaseFreq;        // Parameter : Maximum Freq
	_iq freq_pr;            // Output :  Freq in per-unit using capture unit
	int32 freqhz_pr;        // Output: Freq in Hz, measured using Capture unit
	int32 direction; 		// Direction bit
	void (*init)();     	// Pointer to the init funcion
	void (*calc)();    		// Pointer to the calc funtion
} FREQCAL;

/*-----------------------------------------------------------------------------
 Define a QEP_handle
 -----------------------------------------------------------------------------*/
typedef FREQCAL *FREQCAL_handle;

/*-----------------------------------------------------------------------------
 Default initializer for the FREQCAL Object.
 -----------------------------------------------------------------------------*/

#if (CPU_FRQ_300MHZ)
#define FREQCAL_DEFAULTS {\
		60,5000000,0,0,0,\
		(void (*)(long))FREQCAL_Init,\
        (void (*)(long))FREQCAL_Calc }
#endif
#if (CPU_FRQ_250MHZ)
#define FREQCAL_DEFAULTS {\
		195,10000,0,0,0,\
		(void (*)(long))FREQCAL_Init,\
        (void (*)(long))FREQCAL_Calc }
#endif
#if (CPU_FRQ_200MHZ)
#define FREQCAL_DEFAULTS {\
		313,10000,0,0,0,\
		(void (*)(long))FREQCAL_Init,\
        (void (*)(long))FREQCAL_Calc }
#endif

/*-----------------------------------------------------------------------------
 Prototypes for the functions in Example_freqcal.c
 -----------------------------------------------------------------------------*/
void FREQCAL_Init(void);
void FREQCAL_Calc(FREQCAL_handle);

#endif /*  __FREQCAL__ */
