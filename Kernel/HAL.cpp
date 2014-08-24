#include "HAL.h"

void outb(unsigned short port, unsigned char value)
{
    asm volatile ( "outb %0, %1" : : "a"(value), "Nd"(port) );
    
}

unsigned char inb(unsigned short port)
{
    unsigned char ret;
    asm volatile ( "inb %1, %0" : "=a"(ret) : "Nd"(port) );
    return ret;
}
void pushall()
{
	asm volatile("pushq %rax");
	asm volatile("pushq %rbx");
	asm volatile("pushq %rcx");
	asm volatile("pushq %rdx");
	asm volatile("pushq %rsi");
	asm volatile("pushq %rdi");
	asm volatile("pushq %rbp");	

}
void popall()
{
	asm volatile("popq %rbp");
	asm volatile("popq %rdi");
	asm volatile("popq %rsi");
	asm volatile("popq %rdx");
	asm volatile("popq %rcx");
	asm volatile("popq %rbx");
	asm volatile("popq %rax");
}
void enable_Ints()
{
	asm volatile("sti");
}

void disable_Ints()
{
	asm volatile("cli");
}
