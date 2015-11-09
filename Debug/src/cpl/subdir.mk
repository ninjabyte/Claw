################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/cpl/cpl.c 

OBJS += \
./src/cpl/cpl.o 

C_DEPS += \
./src/cpl/cpl.d 


# Each subdirectory must supply rules for building sources it contributes
src/cpl/%.o: ../src/cpl/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -std=c99 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


