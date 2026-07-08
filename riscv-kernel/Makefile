CC = riscv64-unknown-elf-gcc
AS = riscv64-unknown-elf-as
LD = riscv64-unknown-elf-ld
OBJCOPY = riscv64-unknown-elf-objcopy
OBJDUMP = riscv64-unknown-elf-objdump

CFLAGS = -march=rv64gc -mabi=lp64d -mcmodel=medany -nostdlib -ffreestanding -Wall -Wextra -Iinclude
AFLAGS =
LDFLAGS = -T link.ld

ROOT_DIR = .
BOOT_DIR = boot
KERNEL_DIR = kernel
DRIVERS_DIR = drivers
BUILD_DIR = build
INCLUDE_DIR = include

BOOT_SRC = $(BOOT_DIR)/boot.s
KERNEL_SRC = $(KERNEL_DIR)/kernel.c
DRIVERS_SRC = $(DRIVERS_DIR)/uart.c

BOOT_OBJ = $(BUILD_DIR)/boot.o
KERNEL_OBJ = $(BUILD_DIR)/kernel.o
DRIVERS_OBJ = $(BUILD_DIR)/uart.o


OBJS = $(BOOT_OBJ) $(KERNEL_OBJ) $(DRIVERS_OBJ)

ELF = $(BUILD_DIR)/kernel.elf
BIN = $(BUILD_DIR)/kernel.bin

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

all: $(BIN)

$(BUILD_DIR)/%.o: $(DRIVERS_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(ELF): $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $(OBJS)

$(BIN): $(ELF)
	$(OBJCOPY) -O binary $< $@

$(BOOT_OBJ): $(BOOT_SRC) | $(BUILD_DIR)
	$(AS) $(AFLAGS) -o $@ $<

$(KERNEL_OBJ): $(KERNEL_SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(BUILD_DIR)/*.o $(BUILD_DIR)/*.elf $(BUILD_DIR)/*.bin

run: $(BIN)
	qemu-system-riscv64 -M virt -m 2G -kernel $(BIN) -nographic

debug: $(BIN)
	qemu-system-riscv64 -M virt -m 2G -kernel $(BIN) -nographic -s -S

dump: $(ELF)
	$(OBJDUMP) -d $(ELF) | less

help:
	@echo "Objetivos disponibles:"
	@echo "  all     - Compila el kernel (por defecto)"
	@echo "  clean   - Elimina los archivos compilados"
	@echo "  run     - Ejecuta el kernel en QEMU (modo texto)"
	@echo "  debug   - Ejecuta QEMU en modo depuración (con GDB)"
	@echo "  dump    - Muestra el desensamblado del kernel"
	@echo "  help    - Muestra esta ayuda"

.PHONY: all clean run debug dump help