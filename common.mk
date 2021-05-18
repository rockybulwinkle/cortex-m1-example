#REPO_ROOT := $(shell git rev-parse --show-toplevel)
REPO_ROOT := $(shell pwd)

ifdef DEBUG
	NO_ECHO :=
else
	NO_ECHO := @
endif

tool_root=/software/gcc/arm/gcc-arm-none-eabi-9-2020-q2-update/bin
CC=$(tool_root)/arm-none-eabi-gcc
LD=$(tool_root)/arm-none-eabi-ld
OCPY=$(tool_root)/arm-none-eabi-objcopy
ODUMP=$(tool_root)/arm-none-eabi-objdump
SZ=$(tool_root)/arm-none-eabi-size
MKDIR=mkdir

CFLAGS += \
	-mthumb \
	-march=armv6-m \
	-mcpu=cortex-m0 \
	-Wall \
	-std=c11 \
	-specs=nano.specs \
	-O0 \
	-fdebug-prefix-map=$(REPO_ROOT)= \
	-g \
	-ffreestanding \
	-ffunction-sections \
	-fdata-sections

LDFLAGS += \
	-mthumb \
	-march=armv6-m \
	-mcpu=cortex-m0 \
	-Wl,--print-memory-usage \
	-Wl,-Map=$(BUILD_DIR)/$(PROJECT).map \
	-T m1.ld \
	-Wl,--gc-sections \


CFLAGS += $(foreach i,$(INCLUDES),-I$(i))
CFLAGS += $(foreach d,$(DEFINES),-D$(d))

OBJ_DIR = $(BUILD_DIR)/objs
OBJS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRCS))

.PHONY: all
all: $(BUILD_DIR)/$(PROJECT).bin

$(BUILD_DIR):
	$(NO_ECHO)$(MKDIR) -p $(BUILD_DIR)

$(OBJ_DIR):
	$(NO_ECHO)$(MKDIR) -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.c $(OBJ_DIR)
	@echo "Compiling $<"
	$(NO_ECHO)$(MKDIR) -p $(dir $@)
	$(NO_ECHO)$(CC) -c -o $@ $< $(CFLAGS)

$(BUILD_DIR)/$(PROJECT).bin: $(BUILD_DIR)/$(PROJECT).elf $(BUILD_DIR)/$(PROJECT).lst
	$(OCPY) $< $@ -O binary
	$(SZ) $<

$(BUILD_DIR)/$(PROJECT).lst: $(BUILD_DIR)/$(PROJECT).elf $(BUILD_DIR)
	$(ODUMP) -D $< > $@

$(BUILD_DIR)/$(PROJECT).elf: $(OBJS)
	@echo "Linking $@"
	$(NO_ECHO)$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@


.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)

