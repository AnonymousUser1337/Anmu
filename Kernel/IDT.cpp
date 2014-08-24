#include "IDT.h"


IDT_T IDT_ENTRIES[MAX_INTS];
IDTR_T IDTR;

								
void initIDT()
{
	
	
	IDTR.Limit = sizeof(IDT_PTR) * MAX_INTS - 1;//set the maximum size of the IDT
	IDTR.Base = (intptr_t)(&IDT_ENTRIES);//Get the linear address of the IDT
	kPrintf("Initializing the IDT at the linear address: %d ......\n",LIGHT_BLUE, IDTR.Base);//Tell the user that the IDT is getting ready
	
		
		//set interrupt gates
		set_Int_Gate(0, (uint64_t) isr0);
		set_Int_Gate(1, (uint64_t) isr1);
		set_Int_Gate(2, (uint64_t) isr2);
		set_Int_Gate(3, (uint64_t) isr3);
		set_Int_Gate(4, (uint64_t) isr4);
		set_Int_Gate(5, (uint64_t) isr5);
		set_Int_Gate(6, (uint64_t) isr6);
		set_Int_Gate(7, (uint64_t) isr7);
		set_Int_Gate(8, (uint64_t) isr8);
		set_Int_Gate(9, (uint64_t) isr9);
		set_Int_Gate(10, (uint64_t) isr10);
		set_Int_Gate(11, (uint64_t) isr11);
		set_Int_Gate(12, (uint64_t) isr12);
		set_Int_Gate(13, (uint64_t) isr13);
		set_Int_Gate(14, (uint64_t) isr14);
		set_Int_Gate(15, (uint64_t) isr15);
		set_Int_Gate(16, (uint64_t) isr16);
		set_Int_Gate(17, (uint64_t) isr17);
		set_Int_Gate(18, (uint64_t) isr18);
		set_Int_Gate(19, (uint64_t) isr19);
		set_Int_Gate(20, (uint64_t) isr20);
		set_Int_Gate(21, (uint64_t) isr21);
		set_Int_Gate(22, (uint64_t) isr22);
		set_Int_Gate(23, (uint64_t) isr23);
		set_Int_Gate(24, (uint64_t) isr24);
		set_Int_Gate(25, (uint64_t) isr25);
		set_Int_Gate(26, (uint64_t) isr26);
		set_Int_Gate(27, (uint64_t) isr27);
		set_Int_Gate(28, (uint64_t) isr28);
		set_Int_Gate(29, (uint64_t) isr29);
		set_Int_Gate(30, (uint64_t) isr30);
		set_Int_Gate(31, (uint64_t) isr31);
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
	IDT_ENTRIES[reqNum].BaseHi =(base >> 16) & mask;
	
}
void ISR_HANDLER()
{
	kPrintf("Unhandled exception", LIGHT_BLUE);
}
