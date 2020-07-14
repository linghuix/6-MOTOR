################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/2-Task/prinf_debug_ITM.c 

OBJS += \
./Core/2-Task/prinf_debug_ITM.o 

C_DEPS += \
./Core/2-Task/prinf_debug_ITM.d 


# Each subdirectory must supply rules for building sources it contributes
Core/2-Task/prinf_debug_ITM.o: ../Core/2-Task/prinf_debug_ITM.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Core/0-Conf -I../Core/1-Func -I../Core/2-Task -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/2-Task/prinf_debug_ITM.d" -MT"$@"  -mfloat-abi=soft -mthumb -o "$@"

