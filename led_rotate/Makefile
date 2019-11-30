CC = arm-none-eabi-gcc
AS = arm-none-eabi-as
LD = arm-none-eabi-ld
OBJCOPY = arm-none-eabi-objcopy

CFLAGS = -mcpu=cortex-m3 -mthumb -I CMSIS -D STM32F10X_MD

all: main.bin

startup.o: CMSIS/startup_stm32f10x_md.s
	$(AS) -o startup.o CMSIS/startup_stm32f10x_md.s

core_cm3.o system_stm32f10x.o: CMSIS/core_cm3.c CMSIS/system_stm32f10x.c
	$(CC) $(CFLAGS) -c CMSIS/core_cm3.c CMSIS/system_stm32f10x.c

main.o: main.c
	$(CC) $(CFLAGS) -c -o main.o main.c

main.elf: CMSIS/stm32_flash.ld startup.o core_cm3.o system_stm32f10x.o main.o
	$(LD) -T CMSIS/stm32_flash.ld -o main.elf startup.o core_cm3.o system_stm32f10x.o main.o

main.bin: main.elf
	$(OBJCOPY) -O binary main.elf main.bin

clean:
	rm -f *.o *.elf *.bin

flash: main.bin
	../stm32loader.py -ewv main.bin
