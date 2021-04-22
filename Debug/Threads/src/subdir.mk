################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Threads/src/display.c \
../Threads/src/keyboard.c \
../Threads/src/wifi.c 

OBJS += \
./Threads/src/display.o \
./Threads/src/keyboard.o \
./Threads/src/wifi.o 

C_DEPS += \
./Threads/src/display.d \
./Threads/src/keyboard.d \
./Threads/src/wifi.d 


# Each subdirectory must supply rules for building sources it contributes
Threads/src/display.o: ../Threads/src/display.c Threads/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Admin/Desktop/Project_people/Firmwares/Control/Control_board/Threads/inc" -I"C:/Users/Admin/Desktop/Project_people/Firmwares/Control/Control_board/Threads/src" -I"C:/Users/Admin/Desktop/Project_people/Firmwares/Control/Control_board/Library/wh0802" -I"C:/Users/Admin/Desktop/Project_people/Firmwares/Control/Control_board/Library/Menu" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Threads/src/display.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Threads/src/keyboard.o: ../Threads/src/keyboard.c Threads/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Admin/Desktop/Project_people/Firmwares/Control/Control_board/Threads/inc" -I"C:/Users/Admin/Desktop/Project_people/Firmwares/Control/Control_board/Threads/src" -I"C:/Users/Admin/Desktop/Project_people/Firmwares/Control/Control_board/Library/wh0802" -I"C:/Users/Admin/Desktop/Project_people/Firmwares/Control/Control_board/Library/Menu" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Threads/src/keyboard.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Threads/src/wifi.o: ../Threads/src/wifi.c Threads/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Admin/Desktop/Project_people/Firmwares/Control/Control_board/Threads/inc" -I"C:/Users/Admin/Desktop/Project_people/Firmwares/Control/Control_board/Threads/src" -I"C:/Users/Admin/Desktop/Project_people/Firmwares/Control/Control_board/Library/wh0802" -I"C:/Users/Admin/Desktop/Project_people/Firmwares/Control/Control_board/Library/Menu" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Threads/src/wifi.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

