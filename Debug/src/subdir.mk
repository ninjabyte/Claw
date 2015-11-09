################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/io.c \
../src/main.c \
../src/parser.c \
../src/rpn.c 

OBJS += \
./src/io.o \
./src/main.o \
./src/parser.o \
./src/rpn.o 

C_DEPS += \
./src/io.d \
./src/main.d \
./src/parser.d \
./src/rpn.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -std=c99 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


