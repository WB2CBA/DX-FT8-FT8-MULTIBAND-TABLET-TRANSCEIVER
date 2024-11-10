################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Utilities/subdir.mk
-include Src/subdir.mk
-include Middlewares/src/option/subdir.mk
-include Middlewares/src/subdir.mk
-include Middlewares/STM32_USBH_Library/Core/subdir.mk
-include Middlewares/STM32_USBH_Library/Class/HID/subdir.mk
-include FT8_library/subdir.mk
-include Drivers/STM32F7xx_HAL_Driver/Src/subdir.mk
-include Drivers/CMSIS/Device/ST/STM32F7xx/Source/Templates/gcc/subdir.mk
-include Drivers/CMSIS/Device/ST/STM32F7xx/Source/Templates/subdir.mk
-include Drivers/BSP/wm8994/subdir.mk
-include Drivers/BSP/ts3510/subdir.mk
-include Drivers/BSP/stmpe811/subdir.mk
-include Drivers/BSP/st7735/subdir.mk
-include Drivers/BSP/s5k5cag/subdir.mk
-include Drivers/BSP/ov9655/subdir.mk
-include Drivers/BSP/mfxstm32l152/subdir.mk
-include Drivers/BSP/ft5336/subdir.mk
-include Drivers/BSP/exc7200/subdir.mk
-include Drivers/BSP/STM32746G_DISCOVERY/subdir.mk
-include DSP_CMSIS/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

BUILD_ARTIFACT_NAME := Katy_Release
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX := 
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME).$(BUILD_ARTIFACT_EXTENSION)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
Katy_Release.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
Katy_Release.list \

OBJCOPY_BIN += \
Katy_Release.bin \


# All Target
all:
	+@$(MAKE) --no-print-directory main-build && $(MAKE) --no-print-directory post-build

# Main-build Target
main-build: Katy_Release.elf secondary-outputs

# Tool invocations
Katy_Release.elf: $(OBJS) $(USER_OBJS) ../STM32F746NGHx_FLASH.ld
	arm-none-eabi-gcc -o "Katy_Release.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m7 -T"../STM32F746NGHx_FLASH.ld" --specs=nosys.specs -Wl,-Map="Katy.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

Katy_Release.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "Katy_Release.list"
	@echo 'Finished building: $@'
	@echo ' '

Katy_Release.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "Katy_Release.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

post-build:
	arm-none-eabi-objcopy -O ihex "Katy_Release.elf" "Katy_Release.hex"
	arm-none-eabi-size "Katy_Release.elf"
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents fail-specified-linker-script-missing warn-no-linker-script-specified
.SECONDARY: post-build

-include ../makefile.targets
