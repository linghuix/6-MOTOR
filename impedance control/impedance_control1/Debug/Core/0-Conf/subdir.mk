################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/0-Conf/BSP.c \
../Core/0-Conf/conf_Jlink.c \
../Core/0-Conf/conf_can.c \
../Core/0-Conf/conf_global.c \
../Core/0-Conf/conf_gpio.c \
../Core/0-Conf/conf_rtc.c \
../Core/0-Conf/conf_spi.c \
../Core/0-Conf/conf_tim.c \
../Core/0-Conf/conf_usart.c 

OBJS += \
./Core/0-Conf/BSP.o \
./Core/0-Conf/conf_Jlink.o \
./Core/0-Conf/conf_can.o \
./Core/0-Conf/conf_global.o \
./Core/0-Conf/conf_gpio.o \
./Core/0-Conf/conf_rtc.o \
./Core/0-Conf/conf_spi.o \
./Core/0-Conf/conf_tim.o \
./Core/0-Conf/conf_usart.o 

C_DEPS += \
./Core/0-Conf/BSP.d \
./Core/0-Conf/conf_Jlink.d \
./Core/0-Conf/conf_can.d \
./Core/0-Conf/conf_global.d \
./Core/0-Conf/conf_gpio.d \
./Core/0-Conf/conf_rtc.d \
./Core/0-Conf/conf_spi.d \
./Core/0-Conf/conf_tim.d \
./Core/0-Conf/conf_usart.d 


# Each subdirectory must supply rules for building sources it contributes
Core/0-Conf/BSP.o: ../Core/0-Conf/BSP.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Core/0-Conf -I../Core/1-Func -I../Core/2-Task -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/0-Conf/BSP.d" -MT"$@"  -mfloat-abi=soft -mthumb -o "$@"
Core/0-Conf/conf_Jlink.o: ../Core/0-Conf/conf_Jlink.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Core/0-Conf -I../Core/1-Func -I../Core/2-Task -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/0-Conf/conf_Jlink.d" -MT"$@"  -mfloat-abi=soft -mthumb -o "$@"
Core/0-Conf/conf_can.o: ../Core/0-Conf/conf_can.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Core/0-Conf -I../Core/1-Func -I../Core/2-Task -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/0-Conf/conf_can.d" -MT"$@"  -mfloat-abi=soft -mthumb -o "$@"
Core/0-Conf/conf_global.o: ../Core/0-Conf/conf_global.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Core/0-Conf -I../Core/1-Func -I../Core/2-Task -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/0-Conf/conf_global.d" -MT"$@"  -mfloat-abi=soft -mthumb -o "$@"
Core/0-Conf/conf_gpio.o: ../Core/0-Conf/conf_gpio.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Core/0-Conf -I../Core/1-Func -I../Core/2-Task -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/0-Conf/conf_gpio.d" -MT"$@"  -mfloat-abi=soft -mthumb -o "$@"
Core/0-Conf/conf_rtc.o: ../Core/0-Conf/conf_rtc.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Core/0-Conf -I../Core/1-Func -I../Core/2-Task -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/0-Conf/conf_rtc.d" -MT"$@"  -mfloat-abi=soft -mthumb -o "$@"
Core/0-Conf/conf_spi.o: ../Core/0-Conf/conf_spi.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Core/0-Conf -I../Core/1-Func -I../Core/2-Task -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/0-Conf/conf_spi.d" -MT"$@"  -mfloat-abi=soft -mthumb -o "$@"
Core/0-Conf/conf_tim.o: ../Core/0-Conf/conf_tim.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Core/0-Conf -I../Core/1-Func -I../Core/2-Task -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/0-Conf/conf_tim.d" -MT"$@"  -mfloat-abi=soft -mthumb -o "$@"
Core/0-Conf/conf_usart.o: ../Core/0-Conf/conf_usart.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Core/0-Conf -I../Core/1-Func -I../Core/2-Task -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/0-Conf/conf_usart.d" -MT"$@"  -mfloat-abi=soft -mthumb -o "$@"

