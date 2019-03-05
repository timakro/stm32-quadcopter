CC = arm-none-eabi-gcc
AS = arm-none-eabi-as
LD = arm-none-eabi-ld
OBJCOPY = arm-none-eabi-objcopy

CFLAGS = -mcpu=cortex-m3 -mthumb

all: main.bin

startup.o: startup.s
	$(AS) -o startup.o startup.s

main.o: main.c
	$(CC) $(CFLAGS) -c -o main.o main.c

main.elf: linker.ld startup.o main.o
	$(LD) -T linker.ld -o main.elf startup.o main.o

main.bin: main.elf
	$(OBJCOPY) -O binary main.elf main.bin

clean:
	rm -f *.o *.elf *.bin

flash: main.bin
	../stm32loader.py -ewv main.bin
