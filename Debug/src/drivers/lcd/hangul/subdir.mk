################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/drivers/lcd/hangul/han.c 

OBJS += \
./src/drivers/lcd/hangul/han.o 

C_DEPS += \
./src/drivers/lcd/hangul/han.d 


# Each subdirectory must supply rules for building sources it contributes
src/drivers/lcd/hangul/%.o src/drivers/lcd/hangul/%.su src/drivers/lcd/hangul/%.cyclo: ../src/drivers/lcd/hangul/%.c src/drivers/lcd/hangul/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G474xx -c -I"D:/STM32CubeIDE/stm32g474/lib/STM32G4xx_HAL_Driver/Inc" -I"D:/STM32CubeIDE/stm32g474/lib/STM32G4xx_HAL_Driver/Inc/Legacy" -I"D:/STM32CubeIDE/stm32g474/lib/CMSIS/Device/ST/STM32G4xx/Include" -I"D:/STM32CubeIDE/stm32g474/lib/CMSIS/Include" -I"D:/STM32CubeIDE/stm32g474/src" -I"D:/STM32CubeIDE/stm32g474/src/bsp" -I"D:/STM32CubeIDE/stm32g474/src/common" -I"D:/STM32CubeIDE/stm32g474/src/drivers" -I"D:/STM32CubeIDE/stm32g474/src/drivers/lcd" -I"D:/STM32CubeIDE/stm32g474/src/drivers/lcd/hangul" -I"D:/STM32CubeIDE/stm32g474/src/drivers/usb" -I"D:/STM32CubeIDE/stm32g474/src/drivers/usb/core" -I"D:/STM32CubeIDE/stm32g474/src/drivers/usb/usb_cdc" -I"D:/STM32CubeIDE/stm32g474/src/hw" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-src-2f-drivers-2f-lcd-2f-hangul

clean-src-2f-drivers-2f-lcd-2f-hangul:
	-$(RM) ./src/drivers/lcd/hangul/han.cyclo ./src/drivers/lcd/hangul/han.d ./src/drivers/lcd/hangul/han.o ./src/drivers/lcd/hangul/han.su

.PHONY: clean-src-2f-drivers-2f-lcd-2f-hangul

