# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.29

# compile ASM with C:/Program Files (x86)/Arm GNU Toolchain arm-none-eabi/13.2 Rel1/bin/arm-none-eabi-gcc.exe
ASM_DEFINES = -DPICO_BOARD=\"pico\" -DPICO_BUILD=1 -DPICO_NO_HARDWARE=0 -DPICO_ON_DEVICE=1

ASM_INCLUDES = -IC:/pi_sdk/pico-sdk/src/rp2_common/boot_stage2/asminclude -IC:/pi_sdk/pico-sdk/src/rp2040/hardware_regs/include -IC:/pi_sdk/pico-sdk/src/rp2_common/hardware_base/include -IC:/pi_sdk/pico-sdk/src/common/pico_base/include -IC:/anteres/flight-computer/build/generated/pico_base -IC:/pi_sdk/pico-sdk/src/boards/include -IC:/pi_sdk/pico-sdk/src/rp2_common/pico_platform/include -IC:/pi_sdk/pico-sdk/src/rp2_common/boot_stage2/include

ASM_FLAGS = -mcpu=cortex-m0plus -mthumb -O3 -DNDEBUG

