################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/Algorithms.c" \
"../Sources/Camera.c" \
"../Sources/Common.c" \
"../Sources/ConsoleIO.c" \
"../Sources/Control.c" \
"../Sources/InitCar.c" \
"../Sources/SerialComms.c" \
"../Sources/main.c" \
"../Sources/sa_mtb.c" \

C_SRCS += \
../Sources/Algorithms.c \
../Sources/Camera.c \
../Sources/Common.c \
../Sources/ConsoleIO.c \
../Sources/Control.c \
../Sources/InitCar.c \
../Sources/SerialComms.c \
../Sources/main.c \
../Sources/sa_mtb.c \

OBJS += \
./Sources/Algorithms.o \
./Sources/Camera.o \
./Sources/Common.o \
./Sources/ConsoleIO.o \
./Sources/Control.o \
./Sources/InitCar.o \
./Sources/SerialComms.o \
./Sources/main.o \
./Sources/sa_mtb.o \

C_DEPS += \
./Sources/Algorithms.d \
./Sources/Camera.d \
./Sources/Common.d \
./Sources/ConsoleIO.d \
./Sources/Control.d \
./Sources/InitCar.d \
./Sources/SerialComms.d \
./Sources/main.d \
./Sources/sa_mtb.d \

OBJS_QUOTED += \
"./Sources/Algorithms.o" \
"./Sources/Camera.o" \
"./Sources/Common.o" \
"./Sources/ConsoleIO.o" \
"./Sources/Control.o" \
"./Sources/InitCar.o" \
"./Sources/SerialComms.o" \
"./Sources/main.o" \
"./Sources/sa_mtb.o" \

C_DEPS_QUOTED += \
"./Sources/Algorithms.d" \
"./Sources/Camera.d" \
"./Sources/Common.d" \
"./Sources/ConsoleIO.d" \
"./Sources/Control.d" \
"./Sources/InitCar.d" \
"./Sources/SerialComms.d" \
"./Sources/main.d" \
"./Sources/sa_mtb.d" \

OBJS_OS_FORMAT += \
./Sources/Algorithms.o \
./Sources/Camera.o \
./Sources/Common.o \
./Sources/ConsoleIO.o \
./Sources/Control.o \
./Sources/InitCar.o \
./Sources/SerialComms.o \
./Sources/main.o \
./Sources/sa_mtb.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/Algorithms.o: ../Sources/Algorithms.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Algorithms.args" -Wa,-adhlns="$@.lst" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Algorithms.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/Camera.o: ../Sources/Camera.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Camera.args" -Wa,-adhlns="$@.lst" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Camera.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/Common.o: ../Sources/Common.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Common.args" -Wa,-adhlns="$@.lst" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Common.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/ConsoleIO.o: ../Sources/ConsoleIO.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/ConsoleIO.args" -Wa,-adhlns="$@.lst" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/ConsoleIO.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/Control.o: ../Sources/Control.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Control.args" -Wa,-adhlns="$@.lst" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Control.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/InitCar.o: ../Sources/InitCar.c
	@echo 'Building file: $<'
	@echo 'Executing target #6 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/InitCar.args" -Wa,-adhlns="$@.lst" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/InitCar.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/SerialComms.o: ../Sources/SerialComms.c
	@echo 'Building file: $<'
	@echo 'Executing target #7 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/SerialComms.args" -Wa,-adhlns="$@.lst" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/SerialComms.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/main.o: ../Sources/main.c
	@echo 'Building file: $<'
	@echo 'Executing target #8 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/main.args" -Wa,-adhlns="$@.lst" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/main.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/sa_mtb.o: ../Sources/sa_mtb.c
	@echo 'Building file: $<'
	@echo 'Executing target #9 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/sa_mtb.args" -Wa,-adhlns="$@.lst" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/sa_mtb.o"
	@echo 'Finished building: $<'
	@echo ' '


