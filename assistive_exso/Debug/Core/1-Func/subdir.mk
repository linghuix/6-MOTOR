################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/1-Func/AO.c \
../Core/1-Func/ECON_controller_I.c \
../Core/1-Func/PO.c \
../Core/1-Func/debug.c \
../Core/1-Func/func_BLE_HC05.c \
../Core/1-Func/func_accelerate.c \
../Core/1-Func/func_beep.c 

OBJS += \
./Core/1-Func/AO.o \
./Core/1-Func/ECON_controller_I.o \
./Core/1-Func/PO.o \
./Core/1-Func/debug.o \
./Core/1-Func/func_BLE_HC05.o \
./Core/1-Func/func_accelerate.o \
./Core/1-Func/func_beep.o 

C_DEPS += \
./Core/1-Func/AO.d \
./Core/1-Func/ECON_controller_I.d \
./Core/1-Func/PO.d \
./Core/1-Func/debug.d \
./Core/1-Func/func_BLE_HC05.d \
./Core/1-Func/func_accelerate.d \
./Core/1-Func/func_beep.d 


# Each subdirectory must supply rules for building sources it contributes
Core/1-Func/AO.o: ../Core/1-Func/AO.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Core/0-Conf -I../Core/1-Func -I../Core/2-Task -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/1-Func/AO.d" -MT"$@"  -mfloat-abi=soft -mthumb -o "$@"
Core/1-Func/ECON_controller_I.o: ../Core/1-Func/ECON_controller_I.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Core/0-Conf -I../Core/1-Func -I../Core/2-Task -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/1-Func/ECON_controller_I.d" -MT"$@"  -mfloat-abi=soft -mthumb -o "$@"
Core/1-Func/PO.o: ../Core/1-Func/PO.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Core/0-Conf -I../Core/1-Func -I../Core/2-Task -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/1-Func/PO.d" -MT"$@"  -mfloat-abi=soft -mthumb -o "$@"
Core/1-Func/debug.o: ../Core/1-Func/debug.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Core/0-Conf -I../Core/1-Func -I../Core/2-Task -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/1-Func/debug.d" -MT"$@"  -mfloat-abi=soft -mthumb -o "$@"
Core/1-Func/func_BLE_HC05.o: ../Core/1-Func/func_BLE_HC05.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Core/0-Conf -I../Core/1-Func -I../Core/2-Task -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/1-Func/func_BLE_HC05.d" -MT"$@"  -mfloat-abi=soft -mthumb -o "$@"
Core/1-Func/func_accelerate.o: ../Core/1-Func/func_accelerate.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Core/0-Conf -I../Core/1-Func -I../Core/2-Task -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/1-Func/func_accelerate.d" -MT"$@"  -mfloat-abi=soft -mthumb -o "$@"
Core/1-Func/func_beep.o: ../Core/1-Func/func_beep.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Core/0-Conf -I../Core/1-Func -I../Core/2-Task -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/1-Func/func_beep.d" -MT"$@"  -mfloat-abi=soft -mthumb -o "$@"

