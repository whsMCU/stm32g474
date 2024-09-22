################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/drivers/usb/usb_cdc/usbd_cdc.c \
../src/drivers/usb/usb_cdc/usbd_cdc_if.c \
../src/drivers/usb/usb_cdc/usbd_desc.c 

OBJS += \
./src/drivers/usb/usb_cdc/usbd_cdc.o \
./src/drivers/usb/usb_cdc/usbd_cdc_if.o \
./src/drivers/usb/usb_cdc/usbd_desc.o 

C_DEPS += \
./src/drivers/usb/usb_cdc/usbd_cdc.d \
./src/drivers/usb/usb_cdc/usbd_cdc_if.d \
./src/drivers/usb/usb_cdc/usbd_desc.d 


# Each subdirectory must supply rules for building sources it contributes
src/drivers/usb/usb_cdc/%.o src/drivers/usb/usb_cdc/%.su src/drivers/usb/usb_cdc/%.cyclo: ../src/drivers/usb/usb_cdc/%.c src/drivers/usb/usb_cdc/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G474xx -c -I"D:/STM32CubeIDE/stm32g474/lib/STM32G4xx_HAL_Driver/Inc" -I"D:/STM32CubeIDE/stm32g474/lib/STM32G4xx_HAL_Driver/Inc/Legacy" -I"D:/STM32CubeIDE/stm32g474/lib/CMSIS/Device/ST/STM32G4xx/Include" -I"D:/STM32CubeIDE/stm32g474/lib/CMSIS/Include" -I"D:/STM32CubeIDE/stm32g474/src" -I"D:/STM32CubeIDE/stm32g474/src/bsp" -I"D:/STM32CubeIDE/stm32g474/src/common" -I"D:/STM32CubeIDE/stm32g474/src/drivers" -I"D:/STM32CubeIDE/stm32g474/src/drivers/usb" -I"D:/STM32CubeIDE/stm32g474/src/drivers/usb/core" -I"D:/STM32CubeIDE/stm32g474/src/drivers/usb/usb_cdc" -I"D:/STM32CubeIDE/stm32g474/src/hw" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-src-2f-drivers-2f-usb-2f-usb_cdc

clean-src-2f-drivers-2f-usb-2f-usb_cdc:
	-$(RM) ./src/drivers/usb/usb_cdc/usbd_cdc.cyclo ./src/drivers/usb/usb_cdc/usbd_cdc.d ./src/drivers/usb/usb_cdc/usbd_cdc.o ./src/drivers/usb/usb_cdc/usbd_cdc.su ./src/drivers/usb/usb_cdc/usbd_cdc_if.cyclo ./src/drivers/usb/usb_cdc/usbd_cdc_if.d ./src/drivers/usb/usb_cdc/usbd_cdc_if.o ./src/drivers/usb/usb_cdc/usbd_cdc_if.su ./src/drivers/usb/usb_cdc/usbd_desc.cyclo ./src/drivers/usb/usb_cdc/usbd_desc.d ./src/drivers/usb/usb_cdc/usbd_desc.o ./src/drivers/usb/usb_cdc/usbd_desc.su

.PHONY: clean-src-2f-drivers-2f-usb-2f-usb_cdc

