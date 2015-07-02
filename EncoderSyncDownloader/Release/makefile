################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.2

ORDERED_OBJS += \
"./DSP2834x_CodeStartBranch.obj" \
"./DSP2834x_DefaultIsr.obj" \
"./DSP2834x_GlobalVariableDefs.obj" \
"./DSP2834x_PieCtrl.obj" \
"./DSP2834x_PieVect.obj" \
"./DSP2834x_SysCtrl.obj" \
"./DSP2834x_usDelay.obj" \
"./EncSync.obj" \
"C:/ti/controlSUITE/device_support/c2834x/v112/DSP2834x_common/cmd/28346_RAM_lnk.cmd" \
"C:/ti/controlSUITE/device_support/c2834x/v112/DSP2834x_headers/cmd/DSP2834x_Headers_nonBIOS.cmd" \
"../IQmath_fpu32.lib" \
$(GEN_CMDS__FLAG) \
-l"rts2800_ml.lib" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include subdir_rules.mk
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
EncSync.out \

EXE_OUTPUTS__QUOTED += \
"EncSync.out" \


# All Target
all: EncSync.out

# Tool invocations
EncSync.out: $(OBJS) $(CMD_SRCS) $(LIB_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: C2000 Linker'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.2/bin/cl2000" --silicon_version=28 --define="LARGE_MODEL" --super_quiet --diag_warning=225 --issue_remarks --large_memory_model --unified_memory --output_all_syms -z -m"EncSync.map" --stack_size=0x300 --warn_sections -i"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.2/lib" -i"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.2/include" -i"C:/Users/TheGame/workspace_v6_1/EncoderSyncDownloader" -i"/DSP2834x_common/lib" -i"/v15c/lib" -i"/V100/lib" --priority --reread_libs --xml_link_info="EncSync_linkInfo.xml" --make_static --entry_point=code_start --ram_model -o "EncSync.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '
	@$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)
	-$(RM) "DSP2834x_DefaultIsr.pp" "DSP2834x_GlobalVariableDefs.pp" "DSP2834x_PieCtrl.pp" "DSP2834x_PieVect.pp" "DSP2834x_SysCtrl.pp" "EncSync.pp" 
	-$(RM) "DSP2834x_CodeStartBranch.obj" "DSP2834x_DefaultIsr.obj" "DSP2834x_GlobalVariableDefs.obj" "DSP2834x_PieCtrl.obj" "DSP2834x_PieVect.obj" "DSP2834x_SysCtrl.obj" "DSP2834x_usDelay.obj" "EncSync.obj" 
	-$(RM) "DSP2834x_CodeStartBranch.pp" "DSP2834x_usDelay.pp" 
	-@echo 'Finished clean'
	-@echo ' '

post-build:
	-@echo 'Create flash image: Intel-HEX'
	-"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.2/bin/hex2000.exe" "EncSync.out" -boot -i2c8 -i2cpsc 29 -i2cclkh 5 -i2cclkl 10 -b
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets

