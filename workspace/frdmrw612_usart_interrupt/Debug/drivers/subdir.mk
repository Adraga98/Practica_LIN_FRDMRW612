################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/fsl_cache.c \
../drivers/fsl_clock.c \
../drivers/fsl_common.c \
../drivers/fsl_common_arm.c \
../drivers/fsl_flexcomm.c \
../drivers/fsl_flexspi.c \
../drivers/fsl_gpio.c \
../drivers/fsl_i2s_bridge.c \
../drivers/fsl_inputmux.c \
../drivers/fsl_iped.c \
../drivers/fsl_ocotp.c \
../drivers/fsl_power.c \
../drivers/fsl_reset.c \
../drivers/fsl_usart.c 

C_DEPS += \
./drivers/fsl_cache.d \
./drivers/fsl_clock.d \
./drivers/fsl_common.d \
./drivers/fsl_common_arm.d \
./drivers/fsl_flexcomm.d \
./drivers/fsl_flexspi.d \
./drivers/fsl_gpio.d \
./drivers/fsl_i2s_bridge.d \
./drivers/fsl_inputmux.d \
./drivers/fsl_iped.d \
./drivers/fsl_ocotp.d \
./drivers/fsl_power.d \
./drivers/fsl_reset.d \
./drivers/fsl_usart.d 

OBJS += \
./drivers/fsl_cache.o \
./drivers/fsl_clock.o \
./drivers/fsl_common.o \
./drivers/fsl_common_arm.o \
./drivers/fsl_flexcomm.o \
./drivers/fsl_flexspi.o \
./drivers/fsl_gpio.o \
./drivers/fsl_i2s_bridge.o \
./drivers/fsl_inputmux.o \
./drivers/fsl_iped.o \
./drivers/fsl_ocotp.o \
./drivers/fsl_power.o \
./drivers/fsl_reset.o \
./drivers/fsl_usart.o 


# Each subdirectory must supply rules for building sources it contributes
drivers/%.o: ../drivers/%.c drivers/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_RW612ETA2I -DCPU_RW612ETA2I_cm33_nodsp -DMCUXPRESSO_SDK -DFSL_SDK_DRIVER_QUICK_ACCESS_ENABLE=1 -DSDK_DEBUGCONSOLE=1 -DMCUX_META_BUILD -DBOOT_HEADER_ENABLE=1 -DWIFI_BOARD_RW610 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\repos\practica_LIN\workspace\frdmrw612_usart_interrupt\source" -I"C:\repos\practica_LIN\workspace\frdmrw612_usart_interrupt\flash_config" -I"C:\repos\practica_LIN\workspace\frdmrw612_usart_interrupt\drivers" -I"C:\repos\practica_LIN\workspace\frdmrw612_usart_interrupt\CMSIS" -I"C:\repos\practica_LIN\workspace\frdmrw612_usart_interrupt\CMSIS\m-profile" -I"C:\repos\practica_LIN\workspace\frdmrw612_usart_interrupt\device" -I"C:\repos\practica_LIN\workspace\frdmrw612_usart_interrupt\device\periph" -I"C:\repos\practica_LIN\workspace\frdmrw612_usart_interrupt\utilities" -I"C:\repos\practica_LIN\workspace\frdmrw612_usart_interrupt\utilities\str" -I"C:\repos\practica_LIN\workspace\frdmrw612_usart_interrupt\utilities\debug_console_lite" -I"C:\repos\practica_LIN\workspace\frdmrw612_usart_interrupt\component\uart" -I"C:\repos\practica_LIN\workspace\frdmrw612_usart_interrupt\component\els_pkc" -I"C:\repos\practica_LIN\workspace\frdmrw612_usart_interrupt\component\els_pkc\src\comps\mcuxClBuffer\inc" -I"C:\repos\practica_LIN\workspace\frdmrw612_usart_interrupt\component\els_pkc\src\comps\mcuxClBuffer\inc\internal" -I"C:\repos\practica_LIN\workspace\frdmrw612_usart_interrupt\component\els_pkc\src\comps\mcuxClCore\inc" -I"C:\repos\practica_LIN\workspace\frdmrw612_usart_interrupt\component\els_pkc\src\comps\mcuxClEls\inc" -I"C:\repos\practica_LIN\workspace\frdmrw612_usart_interrupt\component\els_pkc\src\comps\mcuxClEls\inc\internal" -I"C:\repos\practica_LIN\workspace\frdmrw612_usart_interrupt\component\els_pkc\src\comps\mcuxClMemory\inc" -I"C:\repos\practica_LIN\workspace\frdmrw612_usart_interrupt\component\els_pkc\src\comps\mcuxClMemory\inc\internal" -I"C:\repos\practica_LIN\workspace\frdmrw612_usart_interrupt\component\els_pkc\src\comps\mcuxCsslMemory\inc" -I"C:\repos\practica_LIN\workspace\frdmrw612_usart_interrupt\component\els_pkc\src\comps\mcuxCsslMemory\inc\internal" -I"C:\repos\practica_LIN\workspace\frdmrw612_usart_interrupt\component\els_pkc\src\comps\mcuxCsslCPreProcessor\inc" -I"C:\repos\practica_LIN\workspace\frdmrw612_usart_interrupt\component\els_pkc\src\comps\mcuxCsslDataIntegrity\inc" -I"C:\repos\practica_LIN\workspace\frdmrw612_usart_interrupt\component\els_pkc\src\comps\mcuxCsslFlowProtection\inc" -I"C:\repos\practica_LIN\workspace\frdmrw612_usart_interrupt\component\els_pkc\src\comps\mcuxCsslParamIntegrity\inc" -I"C:\repos\practica_LIN\workspace\frdmrw612_usart_interrupt\component\els_pkc\src\comps\mcuxCsslSecureCounter\inc" -I"C:\repos\practica_LIN\workspace\frdmrw612_usart_interrupt\component\els_pkc\src\compiler" -I"C:\repos\practica_LIN\workspace\frdmrw612_usart_interrupt\component\els_pkc\src\platforms\rw61x" -I"C:\repos\practica_LIN\workspace\frdmrw612_usart_interrupt\component\els_pkc\src\platforms\rw61x\inc" -I"C:\repos\practica_LIN\workspace\frdmrw612_usart_interrupt\component\els_pkc\includes\platform\rw61x" -I"C:\repos\practica_LIN\workspace\frdmrw612_usart_interrupt\board" -O0 -fno-common -g3 -gdwarf-4 -c -ffunction-sections -fdata-sections -fno-builtin -mcpu=cortex-m33+nodsp -imacros "C:\repos\practica_LIN\workspace\frdmrw612_usart_interrupt\source\mcux_config.h" -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m33+nodsp -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-drivers

clean-drivers:
	-$(RM) ./drivers/fsl_cache.d ./drivers/fsl_cache.o ./drivers/fsl_clock.d ./drivers/fsl_clock.o ./drivers/fsl_common.d ./drivers/fsl_common.o ./drivers/fsl_common_arm.d ./drivers/fsl_common_arm.o ./drivers/fsl_flexcomm.d ./drivers/fsl_flexcomm.o ./drivers/fsl_flexspi.d ./drivers/fsl_flexspi.o ./drivers/fsl_gpio.d ./drivers/fsl_gpio.o ./drivers/fsl_i2s_bridge.d ./drivers/fsl_i2s_bridge.o ./drivers/fsl_inputmux.d ./drivers/fsl_inputmux.o ./drivers/fsl_iped.d ./drivers/fsl_iped.o ./drivers/fsl_ocotp.d ./drivers/fsl_ocotp.o ./drivers/fsl_power.d ./drivers/fsl_power.o ./drivers/fsl_reset.d ./drivers/fsl_reset.o ./drivers/fsl_usart.d ./drivers/fsl_usart.o

.PHONY: clean-drivers

