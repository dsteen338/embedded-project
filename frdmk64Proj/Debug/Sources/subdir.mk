################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/accelerometer.c \
../Sources/adc.c \
../Sources/alarm.c \
../Sources/dac.c \
../Sources/gpio.c \
../Sources/main.c \
../Sources/timer.c \
../Sources/uart.c 

OBJS += \
./Sources/accelerometer.o \
./Sources/adc.o \
./Sources/alarm.o \
./Sources/dac.o \
./Sources/gpio.o \
./Sources/main.o \
./Sources/timer.o \
./Sources/uart.o 

C_DEPS += \
./Sources/accelerometer.d \
./Sources/adc.d \
./Sources/alarm.d \
./Sources/dac.d \
./Sources/gpio.d \
./Sources/main.d \
./Sources/timer.d \
./Sources/uart.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/%.o: ../Sources/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -D"CPU_MK64FN1M0VMD12" -I"../Sources" -I"../Project_Settings/Startup_Code" -I"../SDK/platform/CMSIS/Include" -I"../SDK/platform/devices" -I"../SDK/platform/devices/MK64F12/include" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


