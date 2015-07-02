################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.2

ORDERED_OBJS += \
"./main.obj" \
"./Source/DSP2834x_CodeStartBranch.obj" \
"./Source/DSP2834x_CpuTimers.obj" \
"./Source/DSP2834x_DBGIER.obj" \
"./Source/DSP2834x_DMA.obj" \
"./Source/DSP2834x_DefaultIsr.obj" \
"./Source/DSP2834x_DisInt.obj" \
"./Source/DSP2834x_ECan.obj" \
"./Source/DSP2834x_ECap.obj" \
"./Source/DSP2834x_EPwm.obj" \
"./Source/DSP2834x_EQep.obj" \
"./Source/DSP2834x_GlobalVariableDefs.obj" \
"./Source/DSP2834x_Gpio.obj" \
"./Source/DSP2834x_I2C.obj" \
"./Source/DSP2834x_Mcbsp.obj" \
"./Source/DSP2834x_MemCopy.obj" \
"./Source/DSP2834x_PieCtrl.obj" \
"./Source/DSP2834x_PieVect.obj" \
"./Source/DSP2834x_Sci.obj" \
"./Source/DSP2834x_Spi.obj" \
"./Source/DSP2834x_SysCtrl.obj" \
"./Source/DSP2834x_Xintf.obj" \
"./Source/DSP2834x_usDelay.obj" \
"./Source/EPWM_handling.obj" \
"./Source/freqcalc.obj" \
"./Source/own_gpio_setup.obj" \
"../28346_RAM_lnk.cmd" \
"../DSP2834x_Headers_nonBIOS.cmd" \
"../IQmath_fpu32.lib" \
$(GEN_CMDS__FLAG) \
-l"libc.a" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include Source/subdir_vars.mk
-include subdir_rules.mk
-include Source/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
TestProgramm.out \

EXE_OUTPUTS__QUOTED += \
"TestProgramm.out" \

BIN_OUTPUTS += \
TestProgramm.hex \

BIN_OUTPUTS__QUOTED += \
"TestProgramm.hex" \


# All Target
all: TestProgramm.out

# Tool invocations
TestProgramm.out: $(OBJS) $(CMD_SRCS) $(LIB_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: C2000 Linker'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.2/bin/cl2000" -v28 -ml -mt --float_support=fpu32 -O2 --diag_warning=225 --display_error_number --diag_wrap=off -z -m"TestProgramm.map" --stack_size=0x300 --warn_sections -i"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.2/lib" -i"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.2/include" --reread_libs --display_error_number --diag_wrap=off --xml_link_info="TestProgramm_linkInfo.xml" --rom_model -o "TestProgramm.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

TestProgramm.hex: $(EXE_OUTPUTS)
	@echo 'Invoking: C2000 Hex Utility'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.2/bin/hex2000"  -o "TestProgramm.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)$(BIN_OUTPUTS__QUOTED)
	-$(RM) "main.pp" "Source\DSP2834x_CpuTimers.pp" "Source\DSP2834x_DMA.pp" "Source\DSP2834x_DefaultIsr.pp" "Source\DSP2834x_ECan.pp" "Source\DSP2834x_ECap.pp" "Source\DSP2834x_EPwm.pp" "Source\DSP2834x_EQep.pp" "Source\DSP2834x_GlobalVariableDefs.pp" "Source\DSP2834x_Gpio.pp" "Source\DSP2834x_I2C.pp" "Source\DSP2834x_Mcbsp.pp" "Source\DSP2834x_MemCopy.pp" "Source\DSP2834x_PieCtrl.pp" "Source\DSP2834x_PieVect.pp" "Source\DSP2834x_Sci.pp" "Source\DSP2834x_Spi.pp" "Source\DSP2834x_SysCtrl.pp" "Source\DSP2834x_Xintf.pp" "Source\EPWM_handling.pp" "Source\freqcalc.pp" "Source\own_gpio_setup.pp" 
	-$(RM) "main.obj" "Source\DSP2834x_CodeStartBranch.obj" "Source\DSP2834x_CpuTimers.obj" "Source\DSP2834x_DBGIER.obj" "Source\DSP2834x_DMA.obj" "Source\DSP2834x_DefaultIsr.obj" "Source\DSP2834x_DisInt.obj" "Source\DSP2834x_ECan.obj" "Source\DSP2834x_ECap.obj" "Source\DSP2834x_EPwm.obj" "Source\DSP2834x_EQep.obj" "Source\DSP2834x_GlobalVariableDefs.obj" "Source\DSP2834x_Gpio.obj" "Source\DSP2834x_I2C.obj" "Source\DSP2834x_Mcbsp.obj" "Source\DSP2834x_MemCopy.obj" "Source\DSP2834x_PieCtrl.obj" "Source\DSP2834x_PieVect.obj" "Source\DSP2834x_Sci.obj" "Source\DSP2834x_Spi.obj" "Source\DSP2834x_SysCtrl.obj" "Source\DSP2834x_Xintf.obj" "Source\DSP2834x_usDelay.obj" "Source\EPWM_handling.obj" "Source\freqcalc.obj" "Source\own_gpio_setup.obj" 
	-$(RM) "Source\DSP2834x_CodeStartBranch.pp" "Source\DSP2834x_DBGIER.pp" "Source\DSP2834x_DisInt.pp" "Source\DSP2834x_usDelay.pp" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

