#include "IDT.h"
#define IDX 0
#define isr(a) isr##a

IDT_T IDT_ENTRIES[MAX_INTS];
IDTR_T IDTR;

								
void initIDT()
{
	
	
	IDTR.Limit = sizeof(IDT_PTR) * MAX_INTS - 1;//set the maximum size of the IDT
	IDTR.Base = (intptr_t)(&IDT_ENTRIES);//Get the linear address of the IDT
	kPrintf("Initializing the IDT at the linear address: %d ......\n",LIGHT_BLUE, IDTR.Base);//Tell the user that the IDT is getting ready
	
		
		//set interrupt gates
		set_Int_Gate(0, (intptr_t) &isr0);
		set_Int_Gate(1, (intptr_t) &isr1);
		set_Int_Gate(2, (intptr_t) &isr2);
		set_Int_Gate(3, (intptr_t) &isr3);
		set_Int_Gate(4, (intptr_t) &isr4);
		set_Int_Gate(5, (intptr_t) &isr5);
		set_Int_Gate(6, (intptr_t) &isr6);
		set_Int_Gate(7, (intptr_t) &isr7);
		set_Int_Gate(8, (intptr_t) &isr8);
		set_Int_Gate(9, (intptr_t) &isr9);
		set_Int_Gate(10, (intptr_t) &isr10);
		set_Int_Gate(11, (intptr_t) &isr11);
		set_Int_Gate(12, (intptr_t) &isr12);
		set_Int_Gate(13, (intptr_t) &isr13);
		set_Int_Gate(14, (intptr_t) &isr14);
		set_Int_Gate(15, (intptr_t) &isr15);
		set_Int_Gate(16, (intptr_t) &isr16);
		set_Int_Gate(17, (intptr_t) &isr17);
		set_Int_Gate(18, (intptr_t) &isr18);
		set_Int_Gate(19, (intptr_t) &isr19);
		set_Int_Gate(20, (intptr_t) &isr20);
		set_Int_Gate(21, (intptr_t) &isr21);
		set_Int_Gate(22, (intptr_t) &isr22);
		set_Int_Gate(23, (intptr_t) &isr23);
		set_Int_Gate(24, (intptr_t) &isr24);
		set_Int_Gate(25, (intptr_t) &isr25);
		set_Int_Gate(26, (intptr_t) &isr26);
		set_Int_Gate(27, (intptr_t) &isr27);
		set_Int_Gate(28, (intptr_t) &isr28);
		set_Int_Gate(29, (intptr_t) &isr29);
		set_Int_Gate(30, (intptr_t) &isr30);
		set_Int_Gate(31, (intptr_t) &isr31);
		LOAD_IDT(&IDTR);
		
}
					
void set_Int_Gate(int reqNum, uint64_t base)//set ISR where n is the ISR number
{
	uint64_t mask = 0xffffffff;//64 bit mask
	IDT_ENTRIES[reqNum].Selector = 0x8;//pass in the code selector
	IDT_ENTRIES[reqNum].Reserved = 0;//nothing reserved
	IDT_ENTRIES[reqNum].Flags = 0x8E;
	//set the base addresses of the interrupt
	IDT_ENTRIES[reqNum].BaseLo = base & mask;
	IDT_ENTRIES[reqNum].BaseHi =(base>> 16) & mask;
	
}
void ISR_HANDLER()
{
	kPrintf("Unhandled exception", LIGHT_BLUE);
}
