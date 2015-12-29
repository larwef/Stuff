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
all: LEUART_test.axf

# Tool invocations
LEUART_test.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU ARM C Linker'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb -T "LEUART_test.ld" -Xlinker --gc-sections -Xlinker -Map="LEUART_test.map" --specs=nano.specs -o LEUART_test.axf "./src/leuart_test.o" "./emlib/em_cmu.o" "./emlib/em_emu.o" "./emlib/em_gpio.o" "./emlib/em_lcd.o" "./emlib/em_leuart.o" "./emlib/em_system.o" "./Drivers/segmentlcd.o" "./CMSIS/efm32gg/startup_efm32gg.o" "./CMSIS/efm32gg/system_efm32gg.o" -Wl,--start-group -lgcc -lc -lnosys -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

	@echo 'Building hex file: LEUART_test.hex'
	arm-none-eabi-objcopy -O ihex "LEUART_test.axf" "LEUART_test.hex"
	@echo ' '

	@echo 'Building bin file: LEUART_test.bin'
	arm-none-eabi-objcopy -O binary "LEUART_test.axf" "LEUART_test.bin"
	@echo ' '

	@echo 'Running size tool'
	arm-none-eabi-size "LEUART_test.axf"
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES) LEUART_test.axf
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
