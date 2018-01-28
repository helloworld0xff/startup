AS=as --32 -I ./
LD=ld -m elf_i386 --oformat binary -N
CC=gcc -m32

all: hinux_boot hinux_kernel hinux_rc

hinux_boot: boot
	dd if=boot of=../PiliOS.vhd bs=512 count=1 seek=0 conv=notrunc
hinux_kernel: kernel
	dd if=kernel of=../PiliOS.vhd bs=512 count=127 seek=1 conv=notrunc conv=sync
hinux_rc: 
	dd if=rc of=../PiliOS.vhd bs=512 count=531 seek=128 conv=notrunc conv=sync
	
boot: boot.o
	${LD} -Ttext 0x7c00 $< -o $@
kernel: kernel.o init.o
	${LD} -Ttext 0x0000 $^ -o $@
	
boot.o: boot.s
	${AS} $< -o $@
kernel.o: kernel.s
	${AS} $< -o $@
init.o: init.c
	${CC} -c $< -o $@
	
.PHONY:clean
clean:
	rm -f boot boot.o kernel.o kernel init.o 
