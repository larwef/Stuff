################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include emlib/subdir.mk
-include Drivers/subdir.mk
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
all: Periodical_wakeup.axf

# Tool invocations
Periodical_wakeup.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU ARM C Linker'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb -T "Periodical_wakeup.ld" -Xlinker --gc-sections -Xlinker -Map="Periodical_wakeup.map" --specs=nano.specs -o Periodical_wakeup.axf "./src/periodical_wakeup.o" "./emlib/em_burtc.o" "./emlib/em_cmu.o" "./emlib/em_emu.o" "./emlib/em_lcd.o" "./emlib/em_rmu.o" "./emlib/em_system.o" "./Drivers/segmentlcd.o" "./CMSIS/efm32gg/startup_efm32gg.o" "./CMSIS/efm32gg/system_efm32gg.o" -Wl,--start-group -lgcc -lc -lnosys -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

	@echo 'Building hex file: Periodical_wakeup.hex'
	arm-none-eabi-objcopy -O ihex "Periodical_wakeup.axf" "Periodical_wakeup.hex"
	@echo ' '

	@echo 'Building bin file: Periodical_wakeup.bin'
	arm-none-eabi-objcopy -O binary "Periodical_wakeup.axf" "Periodical_wakeup.bin"
	@echo ' '

	@echo 'Running size tool'
	arm-none-eabi-size "Periodical_wakeup.axf"
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES) Periodical_wakeup.axf
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
