################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/drivers/usb/core/usbd_core.c \
../src/drivers/usb/core/usbd_ctlreq.c \
../src/drivers/usb/core/usbd_ioreq.c 

OBJS += \
./src/drivers/usb/core/usbd_core.o \
./src/drivers/usb/core/usbd_ctlreq.o \
./src/drivers/usb/core/usbd_ioreq.o 

C_DEPS += \
./src/drivers/usb/core/usbd_core.d \
./src/drivers/usb/core/usbd_ctlreq.d \
./src/drivers/usb/core/usbd_ioreq.d 


# Each subdirectory must supply rules for building sources it contributes
src/drivers/usb/core/%.o src/drivers/usb/core/%.su src/drivers/usb/core/%.cyclo: ../src/drivers/usb/core/%.c src/drivers/usb/core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G474xx -c -I"C:/Users/jjins/Documents/Project/stm32g474/lib/STM32G4xx_HAL_Driver/Inc" -I"C:/Users/jjins/Documents/Project/stm32g474/lib/STM32G4xx_HAL_Driver/Inc/Legacy" -I"C:/Users/jjins/Documents/Project/stm32g474/lib/CMSIS/Device/ST/STM32G4xx/Include" -I"C:/Users/jjins/Documents/Project/stm32g474/lib/CMSIS/Include" -I"C:/Users/jjins/Documents/Project/stm32g474/src" -I"C:/Users/jjins/Documents/Project/stm32g474/src/bsp" -I"C:/Users/jjins/Documents/Project/stm32g474/src/common" -I"C:/Users/jjins/Documents/Project/stm32g474/src/drivers" -I"C:/Users/jjins/Documents/Project/stm32g474/src/drivers/lcd" -I"C:/Users/jjins/Documents/Project/stm32g474/src/drivers/lcd/hangul" -I"C:/Users/jjins/Documents/Project/stm32g474/src/drivers/usb" -I"C:/Users/jjins/Documents/Project/stm32g474/src/drivers/usb/core" -I"C:/Users/jjins/Documents/Project/stm32g474/src/drivers/usb/usb_cdc" -I"C:/Users/jjins/Documents/Project/stm32g474/src/hw" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-src-2f-drivers-2f-usb-2f-core

clean-src-2f-drivers-2f-usb-2f-core:
	-$(RM) ./src/drivers/usb/core/usbd_core.cyclo ./src/drivers/usb/core/usbd_core.d ./src/drivers/usb/core/usbd_core.o ./src/drivers/usb/core/usbd_core.su ./src/drivers/usb/core/usbd_ctlreq.cyclo ./src/drivers/usb/core/usbd_ctlreq.d ./src/drivers/usb/core/usbd_ctlreq.o ./src/drivers/usb/core/usbd_ctlreq.su ./src/drivers/usb/core/usbd_ioreq.cyclo ./src/drivers/usb/core/usbd_ioreq.d ./src/drivers/usb/core/usbd_ioreq.o ./src/drivers/usb/core/usbd_ioreq.su

.PHONY: clean-src-2f-drivers-2f-usb-2f-core

