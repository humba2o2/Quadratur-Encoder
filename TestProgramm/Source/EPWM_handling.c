// TI File $Revision: /main/2 $
// Checkin $Date: July 31, 2009   09:55:50 $
//###########################################################################
//
// FILE:	Example_EpwmSetup.c
//
// TITLE:	Frequency measurement using EQEP peripheral
//
//
//###########################################################################
// Original Author: SD
//
// $TI Release: DSP2834x C/C++ Header Files V1.10 $
// $Release Date: July 27, 2009 $
//###########################################################################

#include <EPWM_handling.h>

#define CPU_CLK   300e6				// CPU CLK = 300'000'000Hz

#define TBCTLVAL  0x200E            // Up-down cnt, timebase = SYSCLKOUT

void EPwmSetup2(unsigned long long pwmClk, char inverted);


void EPwmSetup(unsigned long long pwmClk, char inverted) {

	float sp = CPU_CLK / (2 * pwmClk);
	EPwm1Regs.TBSTS.all = 0;
	EPwm1Regs.TBPHS.half.TBPHS = 0;
	EPwm1Regs.TBCTR = 0;

	EPwm1Regs.CMPCTL.all = 0x50;     // immediate mode for CMPA and CMPB
	EPwm1Regs.CMPA.half.CMPA = sp / (float) 2;
	EPwm1Regs.CMPB = 0;

	EPwm1Regs.AQCTLA.all = inverted; // CTR=CMPA when inc->EPWM1A=1, when dec->EPWM1A=0
	EPwm1Regs.AQCTLB.all = 0x09;     // CTR=PRD ->EPWM1B=1, CTR=0 ->EPWM1B=0
	EPwm1Regs.AQSFRC.all = 0;
	EPwm1Regs.AQCSFRC.all = 0;

	EPwm1Regs.TZSEL.all = 0;
	EPwm1Regs.TZCTL.all = 0;
	EPwm1Regs.TZEINT.all = 0;
	EPwm1Regs.TZFLG.all = 0;
	EPwm1Regs.TZCLR.all = 0;
	EPwm1Regs.TZFRC.all = 0;

	EPwm1Regs.ETSEL.all = 0x0A;      // Interrupt on PRD
	EPwm1Regs.ETPS.all = 1;
	EPwm1Regs.ETFLG.all = 0;
	EPwm1Regs.ETCLR.all = 0;
	EPwm1Regs.ETFRC.all = 0;

	EPwm1Regs.PCCTL.all = 0;

	EPwm1Regs.TBCTL.all = 0x0010 + TBCTLVAL; // Enable Timer
	EPwm1Regs.TBPRD = sp;

	EPwmSetup2(pwmClk, inverted);
}

void EPwmSetup2(unsigned long long pwmClk, char inverted) {

	float sp = CPU_CLK / (2 * pwmClk);
	EPwm2Regs.TBSTS.all = 0;
	EPwm2Regs.TBPHS.half.TBPHS = 0;
	EPwm2Regs.TBCTR = 0;

	EPwm2Regs.CMPCTL.all = 0x50;     // immediate mode for CMPA and CMPB
	EPwm2Regs.CMPA.half.CMPA = sp / (float) 2;
	EPwm2Regs.CMPB = 0;

	EPwm2Regs.AQCTLA.all = inverted; // CTR=CMPA when inc->EPWM1A=1, when dec->EPWM1A=0
	EPwm2Regs.AQCTLB.all = 0x09;     // CTR=PRD ->EPWM1B=1, CTR=0 ->EPWM1B=0
	EPwm2Regs.AQSFRC.all = 0;
	EPwm2Regs.AQCSFRC.all = 0;

	EPwm2Regs.TZSEL.all = 0;
	EPwm2Regs.TZCTL.all = 0;
	EPwm2Regs.TZEINT.all = 0;
	EPwm2Regs.TZFLG.all = 0;
	EPwm2Regs.TZCLR.all = 0;
	EPwm2Regs.TZFRC.all = 0;

	EPwm2Regs.ETSEL.all = 0x0A;      // Interrupt on PRD
	EPwm2Regs.ETPS.all = 1;
	EPwm2Regs.ETFLG.all = 0;
	EPwm2Regs.ETCLR.all = 0;
	EPwm2Regs.ETFRC.all = 0;

	EPwm2Regs.PCCTL.all = 0;

	EPwm2Regs.TBCTL.all = 0x0010 + TBCTLVAL; // Enable Timer
	EPwm2Regs.TBPRD = sp;

}
