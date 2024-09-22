################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/hw/can.c \
../src/hw/cdc.c \
../src/hw/flash.c \
../src/hw/gpio.c \
../src/hw/i2c.c \
../src/hw/lcd.c \
../src/hw/reset.c \
../src/hw/rtc.c \
../src/hw/tim.c \
../src/hw/uart.c \
../src/hw/usb.c 

OBJS += \
./src/hw/can.o \
./src/hw/cdc.o \
./src/hw/flash.o \
./src/hw/gpio.o \
./src/hw/i2c.o \
./src/hw/lcd.o \
./src/hw/reset.o \
./src/hw/rtc.o \
./src/hw/tim.o \
./src/hw/uart.o \
./src/hw/usb.o 

C_DEPS += \
./src/hw/can.d \
./src/hw/cdc.d \
./src/hw/flash.d \
./src/hw/gpio.d \
./src/hw/i2c.d \
./src/hw/lcd.d \
./src/hw/reset.d \
./src/hw/rtc.d \
./src/hw/tim.d \
./src/hw/uart.d \
./src/hw/usb.d 


# Each subdirectory must supply rules for building sources it contributes
src/hw/%.o src/hw/%.su src/hw/%.cyclo: ../src/hw/%.c src/hw/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G474xx -c -I"D:/STM32CubeIDE/stm32g474/lib/STM32G4xx_HAL_Driver/Inc" -I"D:/STM32CubeIDE/stm32g474/lib/STM32G4xx_HAL_Driver/Inc/Legacy" -I"D:/STM32CubeIDE/stm32g474/lib/CMSIS/Device/ST/STM32G4xx/Include" -I"D:/STM32CubeIDE/stm32g474/lib/CMSIS/Include" -I"D:/STM32CubeIDE/stm32g474/src" -I"D:/STM32CubeIDE/stm32g474/src/bsp" -I"D:/STM32CubeIDE/stm32g474/src/common" -I"D:/STM32CubeIDE/stm32g474/src/drivers" -I"D:/STM32CubeIDE/stm32g474/src/drivers/usb" -I"D:/STM32CubeIDE/stm32g474/src/drivers/usb/core" -I"D:/STM32CubeIDE/stm32g474/src/drivers/usb/usb_cdc" -I"D:/STM32CubeIDE/stm32g474/src/hw" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-src-2f-hw

clean-src-2f-hw:
	-$(RM) ./src/hw/can.cyclo ./src/hw/can.d ./src/hw/can.o ./src/hw/can.su ./src/hw/cdc.cyclo ./src/hw/cdc.d ./src/hw/cdc.o ./src/hw/cdc.su ./src/hw/flash.cyclo ./src/hw/flash.d ./src/hw/flash.o ./src/hw/flash.su ./src/hw/gpio.cyclo ./src/hw/gpio.d ./src/hw/gpio.o ./src/hw/gpio.su ./src/hw/i2c.cyclo ./src/hw/i2c.d ./src/hw/i2c.o ./src/hw/i2c.su ./src/hw/lcd.cyclo ./src/hw/lcd.d ./src/hw/lcd.o ./src/hw/lcd.su ./src/hw/reset.cyclo ./src/hw/reset.d ./src/hw/reset.o ./src/hw/reset.su ./src/hw/rtc.cyclo ./src/hw/rtc.d ./src/hw/rtc.o ./src/hw/rtc.su ./src/hw/tim.cyclo ./src/hw/tim.d ./src/hw/tim.o ./src/hw/tim.su ./src/hw/uart.cyclo ./src/hw/uart.d ./src/hw/uart.o ./src/hw/uart.su ./src/hw/usb.cyclo ./src/hw/usb.d ./src/hw/usb.o ./src/hw/usb.su

.PHONY: clean-src-2f-hw

