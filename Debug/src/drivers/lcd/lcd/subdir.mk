################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/drivers/lcd/lcd/lcd_fonts.c \
../src/drivers/lcd/lcd/ssd1306.c \
../src/drivers/lcd/lcd/st7735.c 

OBJS += \
./src/drivers/lcd/lcd/lcd_fonts.o \
./src/drivers/lcd/lcd/ssd1306.o \
./src/drivers/lcd/lcd/st7735.o 

C_DEPS += \
./src/drivers/lcd/lcd/lcd_fonts.d \
./src/drivers/lcd/lcd/ssd1306.d \
./src/drivers/lcd/lcd/st7735.d 


# Each subdirectory must supply rules for building sources it contributes
src/drivers/lcd/lcd/%.o src/drivers/lcd/lcd/%.su src/drivers/lcd/lcd/%.cyclo: ../src/drivers/lcd/lcd/%.c src/drivers/lcd/lcd/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G474xx -c -I"C:/Users/jjins/Documents/Project/stm32g474/lib/STM32G4xx_HAL_Driver/Inc" -I"C:/Users/jjins/Documents/Project/stm32g474/lib/STM32G4xx_HAL_Driver/Inc/Legacy" -I"C:/Users/jjins/Documents/Project/stm32g474/lib/CMSIS/Device/ST/STM32G4xx/Include" -I"C:/Users/jjins/Documents/Project/stm32g474/lib/CMSIS/Include" -I"C:/Users/jjins/Documents/Project/stm32g474/src" -I"C:/Users/jjins/Documents/Project/stm32g474/src/bsp" -I"C:/Users/jjins/Documents/Project/stm32g474/src/common" -I"C:/Users/jjins/Documents/Project/stm32g474/src/drivers" -I"C:/Users/jjins/Documents/Project/stm32g474/src/drivers/lcd" -I"C:/Users/jjins/Documents/Project/stm32g474/src/drivers/lcd/hangul" -I"C:/Users/jjins/Documents/Project/stm32g474/src/drivers/lcd/lcd" -I"C:/Users/jjins/Documents/Project/stm32g474/src/drivers/usb" -I"C:/Users/jjins/Documents/Project/stm32g474/src/drivers/usb/core" -I"C:/Users/jjins/Documents/Project/stm32g474/src/drivers/usb/usb_cdc" -I"C:/Users/jjins/Documents/Project/stm32g474/src/hw" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-src-2f-drivers-2f-lcd-2f-lcd

clean-src-2f-drivers-2f-lcd-2f-lcd:
	-$(RM) ./src/drivers/lcd/lcd/lcd_fonts.cyclo ./src/drivers/lcd/lcd/lcd_fonts.d ./src/drivers/lcd/lcd/lcd_fonts.o ./src/drivers/lcd/lcd/lcd_fonts.su ./src/drivers/lcd/lcd/ssd1306.cyclo ./src/drivers/lcd/lcd/ssd1306.d ./src/drivers/lcd/lcd/ssd1306.o ./src/drivers/lcd/lcd/ssd1306.su ./src/drivers/lcd/lcd/st7735.cyclo ./src/drivers/lcd/lcd/st7735.d ./src/drivers/lcd/lcd/st7735.o ./src/drivers/lcd/lcd/st7735.su

.PHONY: clean-src-2f-drivers-2f-lcd-2f-lcd

