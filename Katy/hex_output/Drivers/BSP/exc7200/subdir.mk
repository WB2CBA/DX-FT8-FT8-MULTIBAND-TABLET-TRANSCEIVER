################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/exc7200/exc7200.c 

OBJS += \
./Drivers/BSP/exc7200/exc7200.o 

C_DEPS += \
./Drivers/BSP/exc7200/exc7200.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/exc7200/exc7200.o: ../Drivers/BSP/exc7200/exc7200.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32F746xx -c -I../Inc -I"C:/STM32F746_32k_ADX_QSO_GPS_RTC_Si4732_GPZDA_Bands_ADIF/Katy/Drivers/BSP/STM32746G_DISCOVERY" -I"C:/STM32F746_32k_ADX_QSO_GPS_RTC_Si4732_GPZDA_Bands_ADIF/Katy/Drivers/BSP/wm8994" -I"C:/STM32F746_32k_ADX_QSO_GPS_RTC_Si4732_GPZDA_Bands_ADIF/Katy/Drivers/BSP/ft5336" -I"C:/STM32F746_32k_ADX_QSO_GPS_RTC_Si4732_GPZDA_Bands_ADIF/Katy/Drivers/STM32F7xx_HAL_Driver/Inc" -I"C:/STM32F746_32k_ADX_QSO_GPS_RTC_Si4732_GPZDA_Bands_ADIF/Katy/Drivers/CMSIS/Include" -I"C:/STM32F746_32k_ADX_QSO_GPS_RTC_Si4732_GPZDA_Bands_ADIF/Katy/Drivers/CMSIS/Device/ST/STM32F7xx/Include" -I"C:/STM32F746_32k_ADX_QSO_GPS_RTC_Si4732_GPZDA_Bands_ADIF/Katy/Utilities" -I"C:/STM32F746_32k_ADX_QSO_GPS_RTC_Si4732_GPZDA_Bands_ADIF/Katy/Utilities/Fonts" -I"C:/STM32F746_32k_ADX_QSO_GPS_RTC_Si4732_GPZDA_Bands_ADIF/Katy/Middlewares/STM32_USBH_Library/Class/HID" -I"C:/STM32F746_32k_ADX_QSO_GPS_RTC_Si4732_GPZDA_Bands_ADIF/Katy/Middlewares/STM32_USBH_Library/Core" -I"C:/STM32F746_32k_ADX_QSO_GPS_RTC_Si4732_GPZDA_Bands_ADIF/Katy/Drivers/BSP/rk043fn48h" -Os -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/BSP/exc7200/exc7200.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

