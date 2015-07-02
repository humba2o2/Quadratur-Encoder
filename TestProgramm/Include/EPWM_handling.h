// TI File $Revision: /main/2 $
// Checkin $Date: July 31, 2009   09:55:50 $
//###########################################################################
//
// FILE:	Example_EpwmSetup.c
//
// TITLE:	Frequency measurement using EQEP peripheral
//
// DESCRIPTION:
//
// This file contains source for the ePWM initialization for the
// freq calculation module
//
//###########################################################################
// Original Author: SD
//
// $TI Release: DSP2834x C/C++ Header Files V1.10 $
// $Release Date: July 27, 2009 $
//###########################################################################

#ifndef __EPWMHANDLER__
#define __EPWMHANDLER__

#include "DSP28x_Project.h"
#include "DSP2834x_Gpio.h"
#include "DSP2834x_Examples.h"
#include "DSP2834x_EPwm.h"
#include "DSP2834x_EPwm_defines.h"

void EPwmSetup(unsigned long long pwmClk, char inverted);

#endif /*  __EPWMHANDLER__ */
