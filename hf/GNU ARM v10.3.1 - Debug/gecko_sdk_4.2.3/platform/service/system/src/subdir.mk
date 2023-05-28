################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/Users/dominikpapp/SimplicityStudio/SDKs/gecko_sdk/platform/service/system/src/sl_system_init.c \
/Users/dominikpapp/SimplicityStudio/SDKs/gecko_sdk/platform/service/system/src/sl_system_kernel.c 

OBJS += \
./gecko_sdk_4.2.3/platform/service/system/src/sl_system_init.o \
./gecko_sdk_4.2.3/platform/service/system/src/sl_system_kernel.o 

C_DEPS += \
./gecko_sdk_4.2.3/platform/service/system/src/sl_system_init.d \
./gecko_sdk_4.2.3/platform/service/system/src/sl_system_kernel.d 


# Each subdirectory must supply rules for building sources it contributes
gecko_sdk_4.2.3/platform/service/system/src/sl_system_init.o: /Users/dominikpapp/SimplicityStudio/SDKs/gecko_sdk/platform/service/system/src/sl_system_init.c gecko_sdk_4.2.3/platform/service/system/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb -std=c99 '-DDEBUG=1' '-DDEBUG_EFM=1' '-DEFM32GG990F1024=1' '-DSL_BOARD_NAME="BRD2200A"' '-DSL_BOARD_REV="B05"' '-DconfigNUM_SDK_THREAD_LOCAL_STORAGE_POINTERS=2' '-DSL_COMPONENT_CATALOG_PRESENT=1' -I"/Users/dominikpapp/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/EFM32GG_STK3700/config" -I"/Users/dominikpapp/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/common/bsp" -I"/Users/dominikpapp/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/common/drivers" -I"/Users/dominikpapp/SimplicityStudio/v5_workspace/hf/config" -I"/Users/dominikpapp/SimplicityStudio/v5_workspace/hf/autogen" -I"/Users/dominikpapp/SimplicityStudio/v5_workspace/hf" -I"/Users/dominikpapp/SimplicityStudio/SDKs/gecko_sdk//platform/Device/SiliconLabs/EFM32GG/Include" -I"/Users/dominikpapp/SimplicityStudio/SDKs/gecko_sdk//platform/common/inc" -I"/Users/dominikpapp/SimplicityStudio/SDKs/gecko_sdk//hardware/board/inc" -I"/Users/dominikpapp/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/Core/Include" -I"/Users/dominikpapp/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/RTOS2/Include" -I"/Users/dominikpapp/SimplicityStudio/SDKs/gecko_sdk//platform/service/device_init/inc" -I"/Users/dominikpapp/SimplicityStudio/SDKs/gecko_sdk//platform/emdrv/dmadrv/inc" -I"/Users/dominikpapp/SimplicityStudio/SDKs/gecko_sdk//platform/emdrv/common/inc" -I"/Users/dominikpapp/SimplicityStudio/SDKs/gecko_sdk//platform/emlib/inc" -I"/Users/dominikpapp/SimplicityStudio/SDKs/gecko_sdk//util/third_party/freertos/cmsis/Include" -I"/Users/dominikpapp/SimplicityStudio/SDKs/gecko_sdk//util/third_party/freertos/kernel/include" -I"/Users/dominikpapp/SimplicityStudio/SDKs/gecko_sdk//util/third_party/freertos/kernel/portable/GCC/ARM_CM3" -I"/Users/dominikpapp/SimplicityStudio/SDKs/gecko_sdk//platform/service/iostream/inc" -I"/Users/dominikpapp/SimplicityStudio/SDKs/gecko_sdk//platform/common/toolchain/inc" -I"/Users/dominikpapp/SimplicityStudio/SDKs/gecko_sdk//platform/service/system/inc" -I"/Users/dominikpapp/SimplicityStudio/SDKs/gecko_sdk//platform/service/udelay/inc" -O3 -Wall -Wextra -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -imacrossl_gcc_preinclude.h --specs=nano.specs -c -fmessage-length=0 -MMD -MP -MF"gecko_sdk_4.2.3/platform/service/system/src/sl_system_init.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

gecko_sdk_4.2.3/platform/service/system/src/sl_system_kernel.o: /Users/dominikpapp/SimplicityStudio/SDKs/gecko_sdk/platform/service/system/src/sl_system_kernel.c gecko_sdk_4.2.3/platform/service/system/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb -std=c99 '-DDEBUG=1' '-DDEBUG_EFM=1' '-DEFM32GG990F1024=1' '-DSL_BOARD_NAME="BRD2200A"' '-DSL_BOARD_REV="B05"' '-DconfigNUM_SDK_THREAD_LOCAL_STORAGE_POINTERS=2' '-DSL_COMPONENT_CATALOG_PRESENT=1' -I"/Users/dominikpapp/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/EFM32GG_STK3700/config" -I"/Users/dominikpapp/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/common/bsp" -I"/Users/dominikpapp/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/common/drivers" -I"/Users/dominikpapp/SimplicityStudio/v5_workspace/hf/config" -I"/Users/dominikpapp/SimplicityStudio/v5_workspace/hf/autogen" -I"/Users/dominikpapp/SimplicityStudio/v5_workspace/hf" -I"/Users/dominikpapp/SimplicityStudio/SDKs/gecko_sdk//platform/Device/SiliconLabs/EFM32GG/Include" -I"/Users/dominikpapp/SimplicityStudio/SDKs/gecko_sdk//platform/common/inc" -I"/Users/dominikpapp/SimplicityStudio/SDKs/gecko_sdk//hardware/board/inc" -I"/Users/dominikpapp/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/Core/Include" -I"/Users/dominikpapp/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/RTOS2/Include" -I"/Users/dominikpapp/SimplicityStudio/SDKs/gecko_sdk//platform/service/device_init/inc" -I"/Users/dominikpapp/SimplicityStudio/SDKs/gecko_sdk//platform/emdrv/dmadrv/inc" -I"/Users/dominikpapp/SimplicityStudio/SDKs/gecko_sdk//platform/emdrv/common/inc" -I"/Users/dominikpapp/SimplicityStudio/SDKs/gecko_sdk//platform/emlib/inc" -I"/Users/dominikpapp/SimplicityStudio/SDKs/gecko_sdk//util/third_party/freertos/cmsis/Include" -I"/Users/dominikpapp/SimplicityStudio/SDKs/gecko_sdk//util/third_party/freertos/kernel/include" -I"/Users/dominikpapp/SimplicityStudio/SDKs/gecko_sdk//util/third_party/freertos/kernel/portable/GCC/ARM_CM3" -I"/Users/dominikpapp/SimplicityStudio/SDKs/gecko_sdk//platform/service/iostream/inc" -I"/Users/dominikpapp/SimplicityStudio/SDKs/gecko_sdk//platform/common/toolchain/inc" -I"/Users/dominikpapp/SimplicityStudio/SDKs/gecko_sdk//platform/service/system/inc" -I"/Users/dominikpapp/SimplicityStudio/SDKs/gecko_sdk//platform/service/udelay/inc" -O3 -Wall -Wextra -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -imacrossl_gcc_preinclude.h --specs=nano.specs -c -fmessage-length=0 -MMD -MP -MF"gecko_sdk_4.2.3/platform/service/system/src/sl_system_kernel.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


