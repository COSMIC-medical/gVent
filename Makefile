########################################
# Makefile for an STM32F4xx project that
# builds the project for installation
# on the STM32F401RE target.
########################################

########################################
# Define toolchain
########################################
CC=arm-none-eabi-gcc
LD=arm-none-eabi-gcc
SZ=arm-none-eabi-size
CP=arm-none-eabi-objcopy
SF=st-flash
CC_TEST=gcc

########################################
# Define project specific details
########################################
TARGET=gvent
LIB=lib/stm32
SRC_DIR=src
TEST_DIR=test
INC_DIR=include
DEV_DIR=device
HAL_SRC=$(LIB)/STM32F4xx_HAL/Src
HAL_INC=$(LIB)/STM32F4xx_HAL/Inc

########################################
# Define source files for the project
# 
# All new files added to the project must
# be listed here
# ########################################

# include all C source files
SRCS = $(shell find $(SRC_DIR) -name '*.c')

# the startup file is an assembler file
# could extend this later if needed to have
# other assembler files
ASM_SRCS = $(DEV_DIR)/startup_stm32f401retx.s

OBJ = $(SRCS:.c=.o)
OBJ += $(ASM_SRCS:.s=.o)

########################################
# Define where to look for .h files
########################################

# we have to include all of our gVent include/*
# directories separately...
INC_DIRS += $(INC_DIR)/
INC_DIRS += $(INC_DIR)/hardware
INC_DIRS += $(INC_DIR)/platform
INC_DIRS += $(INC_DIR)/application
INC_DIRS += $(INC_DIR)/application/tasks

INCLUDE_BASE = $(addprefix -I,$(INC_DIRS))

# includes for the HAL and ARM Cortex hardware
INC_DIRS_HAL = $(HAL_INC)/ \
 		   $(LIB)/CMSIS/Device/ST/STM32F4xx/Include/ \
		   $(LIB)/CMSIS/Include/ \

INCLUDE_PLATFORM = $(INCLUDE_BASE) $(addprefix -I,$(INC_DIRS_HAL))
INCLUDE_TEST = $(INCLUDE_BASE)

########################################
# Define HAL source dependencies
########################################
EXT_SRCS = $(HAL_SRC)/stm32f4xx_hal.c \
		   $(HAL_SRC)/stm32f4xx_hal_cortex.c \
		   $(HAL_SRC)/stm32f4xx_hal_dma.c \
		   $(HAL_SRC)/stm32f4xx_hal_dma_ex.c \
		   $(HAL_SRC)/stm32f4xx_hal_exti.c \
		   $(HAL_SRC)/stm32f4xx_hal_flash.c \
		   $(HAL_SRC)/stm32f4xx_hal_flash_ex.c \
		   $(HAL_SRC)/stm32f4xx_hal_flash_ramfunc.c \
		   $(HAL_SRC)/stm32f4xx_hal_gpio.c \
		   $(HAL_SRC)/stm32f4xx_hal_pwr.c \
		   $(HAL_SRC)/stm32f4xx_hal_pwr_ex.c \
		   $(HAL_SRC)/stm32f4xx_hal_rcc.c \
		   $(HAL_SRC)/stm32f4xx_hal_rcc_ex.c \
		   $(HAL_SRC)/stm32f4xx_hal_tim.c \
		   $(HAL_SRC)/stm32f4xx_hal_tim_ex.c \
		   $(HAL_SRC)/stm32f4xx_hal_uart.c

# get the .o files for the HAL sources
OBJ += $(EXT_SRCS:.c=.o)

########################################
# Compiler and Linker Flags
########################################
CFLAGS = -std=gnu11 
CFLAGS += -mcpu=cortex-m4 
CFLAGS += -g3
CFLAGS += -O0
CFLAGS += -Wall
CFLAGS += -DUSE_HAL_DRIVER -DSTM32F401xE -DDEBUG 
CFLAGS += -ffunction-sections 
CFLAGS += -fdata-sections 
CFLAGS += --specs=nano.specs
CFLAGS += -mfpu=fpv4-sp-d16
CFLAGS += -mfloat-abi=hard
CFLAGS += -mthumb

CFLAGS_TEST = -std=gnu11
CFLAGS_TEST += -O0 
CFLAGS_TEST += -Wall
CFLAGS_TEST += -g3

LSCRIPT = device/STM32F401RETX_FLASH.ld

LFLAGS = -mcpu=cortex-m4
LFLAGS += -T$(LSCRIPT)
LFLAGS += --specs=nosys.specs 
LFLAGS += -Wl,-Map="$(TARGET).map"
LFLAGS += -Wl,--gc-sections
LFLAGS += -static --specs=nano.specs
LFLAGS += -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb
LFLAGS += -Wl,--start-group -lc -lm -Wl,--end-group


########################################
# make recipes
########################################

all: $(TARGET).bin

$(TARGET): $(TARGET).elf

$(TARGET).elf: INCLUDE=$(INCLUDE_PLATFORM)
$(TARGET).elf: $(OBJ)
	echo "building $(TARGET).elf"
	$(CC) $(LFLAGS) -o $(TARGET).elf $^
	$(SZ) $(TARGET).elf 

$(TARGET).bin: $(TARGET).elf
	$(CP) -O binary $(TARGET).elf  $(TARGET).bin	

%.o: %.c
	$(CC) -c $(CFLAGS) $(INCLUDE) $^ -o $@ 

%.o: %.s
	$(CC) -c -x assembler-with-cpp \
		-mcpu=cortex-m4 -g3 -c -x assembler-with-cpp \
		--specs=nano.specs -mfpu=fpv4-sp-d16 \
		-mfloat-abi=hard -mthumb $^ -o $@

flash:
	$(SF) write $(TARGET).bin 0x8000000

ventilation_test: test/testRunner.c src/application/tasks/ventilation.o \
	test/ventilation_test.o \
	test/stubs/systemInfo_stub.o  \
	test/stubs/valve_stub.o \
	test/stubs/dss_stub.o \
	test/testUtil.o
	$(CC) -o $@ $^
	
test: CC=$(CC_TEST)
test: CFLAGS=$(CFLAGS_TEST)
test: INCLUDE=$(INCLUDE_TEST)
test: ventilation_test

clean:
	rm -f *.elf *.bin *.o *.su *.map
	rm -f test/*.o test/*/*.o
	rm -f $(OBJ)
	rm -f $(OBJ:.o=.su)
	rm -f ventilation_test
