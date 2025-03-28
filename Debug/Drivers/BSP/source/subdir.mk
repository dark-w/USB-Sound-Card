################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/source/cs43l22.c \
../Drivers/BSP/source/lis3dsh.c \
../Drivers/BSP/source/oled_sh1106.c \
../Drivers/BSP/source/stm32f4_discovery.c \
../Drivers/BSP/source/stm32f4_discovery_accelerometer.c 

OBJS += \
./Drivers/BSP/source/cs43l22.o \
./Drivers/BSP/source/lis3dsh.o \
./Drivers/BSP/source/oled_sh1106.o \
./Drivers/BSP/source/stm32f4_discovery.o \
./Drivers/BSP/source/stm32f4_discovery_accelerometer.o 

C_DEPS += \
./Drivers/BSP/source/cs43l22.d \
./Drivers/BSP/source/lis3dsh.d \
./Drivers/BSP/source/oled_sh1106.d \
./Drivers/BSP/source/stm32f4_discovery.d \
./Drivers/BSP/source/stm32f4_discovery_accelerometer.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/source/%.o Drivers/BSP/source/%.su Drivers/BSP/source/%.cyclo: ../Drivers/BSP/source/%.c Drivers/BSP/source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I"E:/workspace/project/ST/stm32f407vgt6-0/Drivers/BSP/include" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/AUDIO/Inc -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-source

clean-Drivers-2f-BSP-2f-source:
	-$(RM) ./Drivers/BSP/source/cs43l22.cyclo ./Drivers/BSP/source/cs43l22.d ./Drivers/BSP/source/cs43l22.o ./Drivers/BSP/source/cs43l22.su ./Drivers/BSP/source/lis3dsh.cyclo ./Drivers/BSP/source/lis3dsh.d ./Drivers/BSP/source/lis3dsh.o ./Drivers/BSP/source/lis3dsh.su ./Drivers/BSP/source/oled_sh1106.cyclo ./Drivers/BSP/source/oled_sh1106.d ./Drivers/BSP/source/oled_sh1106.o ./Drivers/BSP/source/oled_sh1106.su ./Drivers/BSP/source/stm32f4_discovery.cyclo ./Drivers/BSP/source/stm32f4_discovery.d ./Drivers/BSP/source/stm32f4_discovery.o ./Drivers/BSP/source/stm32f4_discovery.su ./Drivers/BSP/source/stm32f4_discovery_accelerometer.cyclo ./Drivers/BSP/source/stm32f4_discovery_accelerometer.d ./Drivers/BSP/source/stm32f4_discovery_accelerometer.o ./Drivers/BSP/source/stm32f4_discovery_accelerometer.su

.PHONY: clean-Drivers-2f-BSP-2f-source

