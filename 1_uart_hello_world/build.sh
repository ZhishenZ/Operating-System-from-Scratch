aarch64-linux-gnu-gcc -c  boot.s -o boot.o
aarch64-linux-gnu-gcc -c  lib.s -o lib.o 
aarch64-linux-gnu-gcc -std=c99  -ffreestanding -mgeneral-regs-only -c main.c
aarch64-linux-gnu-gcc -std=c99 -ffreestanding -mgeneral-regs-only  -c uart.c 
aarch64-linux-gnu-ld -nostdlib -T link.lds -o kernel boot.o main.o lib.o uart.o
aarch64-linux-gnu-objcopy -O binary kernel kernel8.img
# -ffreestanding: tells gcc that we do not need c standard library and other runtime features. 
# -mgeneral-regs-only: general purpose registers only, no other registers such as neon registers
# -nostdlib: we do not use start up files or library files. 
# -T link.lds: we use our owm linkerscript. 
# -o kernel: the output file is called kernel
# boot.o and main.o are the files that we want to link.
# aarch64-linux-gnu-objcopy -O binary kernel kernel8.img:
# convert the outputfile "kernel" to a binary file called "kernel8.img"  



# how to run in terminal:
# chmod +x build.sh
# ./build.sh