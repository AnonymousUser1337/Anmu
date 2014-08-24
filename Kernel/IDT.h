#define ASM_LINK extern "C"
#define MAX_INTS 256
#include <stdint.h>
#include "TextTerminal.h"
#include "HAL.h"
 			
struct IDT_PTR
{
	uint16_t Limit;
	intptr_t Base;
}__attribute__((packed));
typedef struct IDT_PTR IDTR_T;

struct IDT
{
	
	uint16_t BaseLo;
	uint16_t Selector;
	uint8_t Reserved;
	uint8_t Flags;
	uint16_t BaseHi;
	
}__attribute__((packed));
typedef struct IDT IDT_T;

ASM_LINK void initIDT();

ASM_LINK void set_Int_Gate(int reqNum, uint32_t base);
ASM_LINK void isr0();
ASM_LINK void isr1();
ASM_LINK void isr2();
ASM_LINK void isr3();
ASM_LINK void isr4();
ASM_LINK void isr5();
ASM_LINK void isr6();
ASM_LINK void isr7();
ASM_LINK void isr8();
ASM_LINK void isr9();
ASM_LINK void isr10();
ASM_LINK void isr11();
ASM_LINK void isr12();
ASM_LINK void isr13();
ASM_LINK void isr14();
ASM_LINK void isr15();
ASM_LINK void isr16();
ASM_LINK void isr17();
ASM_LINK void isr18();
ASM_LINK void isr19();
ASM_LINK void isr20();
ASM_LINK void isr21();
ASM_LINK void isr22();
ASM_LINK void isr23();
ASM_LINK void isr24();
ASM_LINK void isr25();
ASM_LINK void isr26();
ASM_LINK void isr27();
ASM_LINK void isr28();
ASM_LINK void isr29();
ASM_LINK void isr30();
ASM_LINK void isr31();
