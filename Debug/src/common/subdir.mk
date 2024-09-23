################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/common/cli.c \
../src/common/cli_gui.c \
../src/common/log.c \
../src/common/maths.c \
../src/common/qbuffer.c 

OBJS += \
./src/common/cli.o \
./src/common/cli_gui.o \
./src/common/log.o \
./src/common/maths.o \
./src/common/qbuffer.o 

C_DEPS += \
./src/common/cli.d \
./src/common/cli_gui.d \
./src/common/log.d \
./src/common/maths.d \
./src/common/qbuffer.d 


# Each subdirectory must supply rules for building sources it contributes
src/common/%.o src/common/%.su src/common/%.cyclo: ../src/common/%.c src/common/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G474xx -c -I"C:/Users/jjins/Documents/Project/stm32g474/lib/STM32G4xx_HAL_Driver/Inc" -I"C:/Users/jjins/Documents/Project/stm32g474/lib/STM32G4xx_HAL_Driver/Inc/Legacy" -I"C:/Users/jjins/Documents/Project/stm32g474/lib/CMSIS/Device/ST/STM32G4xx/Include" -I"C:/Users/jjins/Documents/Project/stm32g474/lib/CMSIS/Include" -I"C:/Users/jjins/Documents/Project/stm32g474/src" -I"C:/Users/jjins/Documents/Project/stm32g474/src/bsp" -I"C:/Users/jjins/Documents/Project/stm32g474/src/common" -I"C:/Users/jjins/Documents/Project/stm32g474/src/drivers" -I"C:/Users/jjins/Documents/Project/stm32g474/src/drivers/lcd" -I"C:/Users/jjins/Documents/Project/stm32g474/src/drivers/lcd/hangul" -I"C:/Users/jjins/Documents/Project/stm32g474/src/drivers/usb" -I"C:/Users/jjins/Documents/Project/stm32g474/src/drivers/usb/core" -I"C:/Users/jjins/Documents/Project/stm32g474/src/drivers/usb/usb_cdc" -I"C:/Users/jjins/Documents/Project/stm32g474/src/hw" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-src-2f-common

clean-src-2f-common:
	-$(RM) ./src/common/cli.cyclo ./src/common/cli.d ./src/common/cli.o ./src/common/cli.su ./src/common/cli_gui.cyclo ./src/common/cli_gui.d ./src/common/cli_gui.o ./src/common/cli_gui.su ./src/common/log.cyclo ./src/common/log.d ./src/common/log.o ./src/common/log.su ./src/common/maths.cyclo ./src/common/maths.d ./src/common/maths.o ./src/common/maths.su ./src/common/qbuffer.cyclo ./src/common/qbuffer.d ./src/common/qbuffer.o ./src/common/qbuffer.su

.PHONY: clean-src-2f-common

