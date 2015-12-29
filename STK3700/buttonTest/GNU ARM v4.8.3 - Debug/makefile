################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include emlib/subdir.mk
-include CMSIS/efm32gg/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: buttonTest.axf

# Tool invocations
buttonTest.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU ARM C Linker'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb -T "buttonTest.ld" -Xlinker --gc-sections -Xlinker -Map="buttonTest.map" --specs=nano.specs -o buttonTest.axf "./src/button_test.o" "./emlib/em_emu.o" "./emlib/em_system.o" "./CMSIS/efm32gg/startup_efm32gg.o" "./CMSIS/efm32gg/system_efm32gg.o" -Wl,--start-group -lgcc -lc -lnosys -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

	@echo 'Building hex file: buttonTest.hex'
	arm-none-eabi-objcopy -O ihex "buttonTest.axf" "buttonTest.hex"
	@echo ' '

	@echo 'Building bin file: buttonTest.bin'
	arm-none-eabi-objcopy -O binary "buttonTest.axf" "buttonTest.bin"
	@echo ' '

	@echo 'Running size tool'
	arm-none-eabi-size "buttonTest.axf"
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES) buttonTest.axf
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
