################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/wm8994/wm8994.c 

OBJS += \
./Drivers/BSP/wm8994/wm8994.o 

C_DEPS += \
./Drivers/BSP/wm8994/wm8994.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/wm8994/wm8994.o: ../Drivers/BSP/wm8994/wm8994.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32F746xx -c -I../Inc -I"C:/STM32F746_32k_ADX_QSO_RTC_Bands_ADIF_DX_Un0_EditRTC_2/Katy/Drivers/BSP/STM32746G_DISCOVERY" -I"C:/STM32F746_32k_ADX_QSO_RTC_Bands_ADIF_DX_Un0_EditRTC_2/Katy/Drivers/BSP/wm8994" -I"C:/STM32F746_32k_ADX_QSO_RTC_Bands_ADIF_DX_Un0_EditRTC_2/Katy/Drivers/BSP/ft5336" -I"C:/STM32F746_32k_ADX_QSO_RTC_Bands_ADIF_DX_Un0_EditRTC_2/Katy/Drivers/STM32F7xx_HAL_Driver/Inc" -I"C:/STM32F746_32k_ADX_QSO_RTC_Bands_ADIF_DX_Un0_EditRTC_2/Katy/Drivers/CMSIS/Include" -I"C:/STM32F746_32k_ADX_QSO_RTC_Bands_ADIF_DX_Un0_EditRTC_2/Katy/Drivers/CMSIS/Device/ST/STM32F7xx/Include" -I"C:/STM32F746_32k_ADX_QSO_RTC_Bands_ADIF_DX_Un0_EditRTC_2/Katy/Utilities" -I"C:/STM32F746_32k_ADX_QSO_RTC_Bands_ADIF_DX_Un0_EditRTC_2/Katy/Utilities/Fonts" -I"C:/STM32F746_32k_ADX_QSO_RTC_Bands_ADIF_DX_Un0_EditRTC_2/Katy/Drivers/BSP/rk043fn48h" -I"C:/STM32F746_32k_ADX_QSO_RTC_Bands_ADIF_DX_Un0_EditRTC_2/Katy/FT8_library" -I"C:/STM32F746_32k_ADX_QSO_RTC_Bands_ADIF_DX_Un0_EditRTC_2/Katy/Middlewares/src" -Os -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/BSP/wm8994/wm8994.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

