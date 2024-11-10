################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Utilities/lcd_log.c 

OBJS += \
./Utilities/lcd_log.o 

C_DEPS += \
./Utilities/lcd_log.d 


# Each subdirectory must supply rules for building sources it contributes
Utilities/lcd_log.o: ../Utilities/lcd_log.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32F746xx -c -I../Inc -I"C:/STM32F746_32k_ADX_QSO_RTC_Bands_ADIF_DX_Un0_EditRTC_2/Katy/Drivers/BSP/STM32746G_DISCOVERY" -I"C:/STM32F746_32k_ADX_QSO_RTC_Bands_ADIF_DX_Un0_EditRTC_2/Katy/Drivers/BSP/wm8994" -I"C:/STM32F746_32k_ADX_QSO_RTC_Bands_ADIF_DX_Un0_EditRTC_2/Katy/Drivers/BSP/ft5336" -I"C:/STM32F746_32k_ADX_QSO_RTC_Bands_ADIF_DX_Un0_EditRTC_2/Katy/Drivers/STM32F7xx_HAL_Driver/Inc" -I"C:/STM32F746_32k_ADX_QSO_RTC_Bands_ADIF_DX_Un0_EditRTC_2/Katy/Drivers/CMSIS/Include" -I"C:/STM32F746_32k_ADX_QSO_RTC_Bands_ADIF_DX_Un0_EditRTC_2/Katy/Drivers/CMSIS/Device/ST/STM32F7xx/Include" -I"C:/STM32F746_32k_ADX_QSO_RTC_Bands_ADIF_DX_Un0_EditRTC_2/Katy/Utilities" -I"C:/STM32F746_32k_ADX_QSO_RTC_Bands_ADIF_DX_Un0_EditRTC_2/Katy/Utilities/Fonts" -I"C:/STM32F746_32k_ADX_QSO_RTC_Bands_ADIF_DX_Un0_EditRTC_2/Katy/Drivers/BSP/rk043fn48h" -I"C:/STM32F746_32k_ADX_QSO_RTC_Bands_ADIF_DX_Un0_EditRTC_2/Katy/FT8_library" -I"C:/STM32F746_32k_ADX_QSO_RTC_Bands_ADIF_DX_Un0_EditRTC_2/Katy/Middlewares/src" -Os -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"Utilities/lcd_log.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

