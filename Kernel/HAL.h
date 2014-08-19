#ifndef ASM_LINK
#define ASM_LINK extern "C"
#endif
ASM_LINK void outb(unsigned short port, unsigned char value);
ASM_LINK unsigned char inb(unsigned short port);
