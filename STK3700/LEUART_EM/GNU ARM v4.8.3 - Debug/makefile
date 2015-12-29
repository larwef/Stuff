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
all: LEUART_EM.axf

# Tool invocations
LEUART_EM.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU ARM C Linker'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb -T "LEUART_EM.ld" -Xlinker --gc-sections -Xlinker -Map="LEUART_EM.map" --specs=nano.specs -o LEUART_EM.axf "./src/empty_project.o" "./emlib/em_cmu.o" "./emlib/em_emu.o" "./emlib/em_gpio.o" "./emlib/em_leuart.o" "./emlib/em_system.o" "./CMSIS/efm32gg/startup_efm32gg.o" "./CMSIS/efm32gg/system_efm32gg.o" -Wl,--start-group -lgcc -lc -lnosys -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

	@echo 'Building hex file: LEUART_EM.hex'
	arm-none-eabi-objcopy -O ihex "LEUART_EM.axf" "LEUART_EM.hex"
	@echo ' '

	@echo 'Building bin file: LEUART_EM.bin'
	arm-none-eabi-objcopy -O binary "LEUART_EM.axf" "LEUART_EM.bin"
	@echo ' '

	@echo 'Running size tool'
	arm-none-eabi-size "LEUART_EM.axf"
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES) LEUART_EM.axf
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
