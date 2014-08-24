@echo off
cd Boot
nasm Stage1.asm -o Stage1.bin
nasm -f elf64 Stage2.asm -o Stage2.o
copy Stage1.bin "C:\cygwin64\home\Anonymous\Zeroth-OS"
copy Stage2.o "C:\cygwin64\home\Anonymous\Zeroth-OS"
del Stage1.bin
del Stage2.o
cd C:\cygwin64\home\Anonymous\Zeroth-OS
cd kernel
x86_64-elf-g++ -fno-exceptions -fno-rtti -ffreestanding -mcmodel=large -mno-red-zone -mno-mmx -mno-sse -mno-sse2 -mno-sse3 -mno-3dnow -c -o kernel.o kernel.cpp
x86_64-elf-g++ -fno-exceptions -fno-rtti -ffreestanding -mcmodel=large -mno-red-zone -mno-mmx -mno-sse -mno-sse2 -mno-sse3 -mno-3dnow -c -o TextTerminal.o TextTerminal.cpp
x86_64-elf-g++ -fno-exceptions -fno-rtti -ffreestanding -mcmodel=large -mno-red-zone -mno-mmx -mno-sse -mno-sse2 -mno-sse3 -mno-3dnow -c -o HAL.o HAL.cpp
x86_64-elf-g++ -fno-exceptions -fno-rtti -ffreestanding -mcmodel=large -mno-red-zone -mno-mmx -mno-sse -mno-sse2 -mno-sse3 -mno-3dnow -c -o IDT.o IDT.cpp
nasm -f elf64 ISR_handlers.asm -o ISR_handlers.o
copy ISR_handlers.o C:\cygwin64\home\Anonymous\Zeroth-OS
copy kernel.o C:\cygwin64\home\Anonymous\Zeroth-OS
copy TextTerminal.o C:\cygwin64\home\Anonymous\Zeroth-OS
copy HAL.o C:\cygwin64\home\Anonymous\Zeroth-OS
copy IDT.o C:\cygwin64\home\Anonymous\Zeroth-OS
del kernel.o
del TextTerminal.o
del HAL.o
del IDT.o
del ISR_handlers.o
cd C:\cygwin64\home\Anonymous\Zeroth-OS
x86_64-elf-ld -T linkerscript.ld -o MyOS.bin Stage2.o kernel.o TextTerminal.o HAL.o IDT.o ISR_handlers.o -nostdlib
x86_64-elf-objcopy -S -O binary MyOS.bin Anmu.bin
del MyOS.bin
copy Stage1.bin Root
copy Anmu.bin Root
mkisofs -b Stage1.bin -no-emul-boot -boot-info-table -o BootLoader.iso ./Root
del Stage1.bin
del Stage2.o
del Anmu.bin
del kernel.o
del TextTerminal.o
del HAL.o
del IDT.o
del ISR_handlers.o
