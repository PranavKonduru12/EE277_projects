################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/display_ctrl/display_ctrl.c 

OBJS += \
./src/display_ctrl/display_ctrl.o 

C_DEPS += \
./src/display_ctrl/display_ctrl.d 


# Each subdirectory must supply rules for building sources it contributes
src/display_ctrl/%.o: ../src/display_ctrl/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM v7 gcc compiler'
	arm-none-eabi-gcc -DDEBUG -Wall -O0 -g3 -I"C:\LocalWorkspace\EE277_local\EE277_Drive_Dec17_2024\EE277_FinalProject\Impl_1\Vitis\newWorkspace\Zybo-Z7-10-HDMI\src" -IC:/LocalWorkspace/EE277_local/EE277_Drive_Dec17_2024/EE277_FinalProject/Impl_1/Vitis/newWorkspace/design_1_wrapper/export/design_1_wrapper/sw/design_1_wrapper/domain_ps7_cortexa9_0/bspinclude/include -c -fmessage-length=0 -MT"$@" -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -IC:/LocalWorkspace/EE277_local/EE277_Drive_Dec17_2024/EE277_FinalProject/Impl_1/Vitis/newWorkspace/design_1_wrapper/export/design_1_wrapper/sw/design_1_wrapper/domain_ps7_cortexa9_0/bspinclude/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


