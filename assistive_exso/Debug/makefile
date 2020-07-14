################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Drivers/STM32F1xx_HAL_Driver/Src/subdir.mk
-include Core/Src/subdir.mk
-include Core/2-Task/subdir.mk
-include Core/1-Func/subdir.mk
-include Core/0-Conf/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
assistive_exso.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
assistive_exso.list \


# All Target
all: assistive_exso.elf secondary-outputs

# Tool invocations
assistive_exso.elf: $(OBJS) $(USER_OBJS) /mnt/Amusements/0-重要文档/workspace_1.0.2/assistive_exso/STM32F103R8TX_FLASH.ld
	arm-none-eabi-gcc -o "assistive_exso.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"/mnt/Amusements/0-重要文档/workspace_1.0.2/assistive_exso/STM32F103R8TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="assistive_exso.map" -Wl,--gc-sections -static  -mfloat-abi=soft -mthumb -u _printf_float -u _scanf_float -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

assistive_exso.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "assistive_exso.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
