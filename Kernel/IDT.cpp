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
	
		
	
		set_Int_Gate(0, (intptr_t) isr0);
		set_Int_Gate(1, (intptr_t) isr1);
		set_Int_Gate(2, (intptr_t) isr2);
		set_Int_Gate(3, (intptr_t) isr3);
		set_Int_Gate(4, (intptr_t) isr4);
		set_Int_Gate(5, (intptr_t) isr5);
		set_Int_Gate(6, (intptr_t) isr6);
		set_Int_Gate(7, (intptr_t) isr7);
		set_Int_Gate(8, (intptr_t) isr8);
		set_Int_Gate(9, (intptr_t) isr9);
		set_Int_Gate(10, (intptr_t) isr10);
		set_Int_Gate(11, (intptr_t) isr11);
		set_Int_Gate(12, (intptr_t) isr12);
		set_Int_Gate(13, (intptr_t) isr13);
		set_Int_Gate(14, (intptr_t) isr14);
		set_Int_Gate(15, (intptr_t) isr15);
		set_Int_Gate(16, (intptr_t) isr16);
		set_Int_Gate(17, (intptr_t) isr17);
		set_Int_Gate(18, (intptr_t) isr18);
		set_Int_Gate(19, (intptr_t) isr19);
		set_Int_Gate(20, (intptr_t) isr20);
		set_Int_Gate(21, (intptr_t) isr21);
		set_Int_Gate(22, (intptr_t) isr22);
		set_Int_Gate(23, (intptr_t) isr23);
		set_Int_Gate(24, (intptr_t) isr24);
		set_Int_Gate(25, (intptr_t) isr25);
		set_Int_Gate(26, (intptr_t) isr26);
		set_Int_Gate(27, (intptr_t) isr27);
		set_Int_Gate(28, (intptr_t) isr28);
		set_Int_Gate(29, (intptr_t) isr29);
		set_Int_Gate(30, (intptr_t) isr30);
		set_Int_Gate(31, (intptr_t) isr31);
		asm volatile("LIDT (%0)" : : "r"(&IDTR));
	//asm volatile("sti");
	//asm volatile("int $0x0");
}
					
void set_Int_Gate(int reqNum, uint32_t base)//set ISR where n is the ISR number
{
	uint64_t mask = 0xffffffff;//64 bit mask
	IDT_ENTRIES[reqNum].Selector = 0x8;//pass in the code selector
	IDT_ENTRIES[reqNum].Reserved = 0;//nothing reserved
	IDT_ENTRIES[reqNum].Flags = 0x8E;
	//set the base addresses of the interrupt
	IDT_ENTRIES[reqNum].BaseLo = base & mask;
	IDT_ENTRIES[reqNum].BaseHi =(base>> 16) & mask;
	
}

//isr handlers
//push all registers 
//some code
//pop registers
//return to what cpu was doing
void isr0()
{
	pushall();
	
	kPrintf("Unhandled exception: 0\n", LIGHT_BLUE);
	
	popall();
	asm volatile("iretq");
}
void isr1()
{
	pushall();
	kPrintf("Unhandled exception: 1\n", LIGHT_BLUE);
	popall();
	asm volatile("iretq");
}
void isr2()
{
	pushall();
	kPrintf("Unhandled exception: 2\n", LIGHT_BLUE);
	popall();
	asm volatile("iretq");

}
void isr3()
{
	pushall();
	kPrintf("Unhandled exception: 3\n", LIGHT_BLUE);
	popall();
	asm volatile("iretq");
}
void isr4()
{
	pushall();
	kPrintf("Unhandled exception: 4\n", LIGHT_BLUE);
	popall();
	asm volatile("iretq");
}
 void isr5()
{
	pushall();
	kPrintf("Unhandled exception: 5\n", LIGHT_BLUE);
	popall();
	asm volatile("iretq");

}
 void isr6()
{
	pushall();
	kPrintf("Unhandled exception: 6\n", LIGHT_BLUE);
	popall();
	asm volatile("iretq");
}
 void isr7()
{
	pushall();
	kPrintf("Unhandled exception: 7\n", LIGHT_BLUE);
	popall();
	asm volatile("iretq");
}
 void isr8()
{
	pushall();
	kPrintf("Unhandled exception: 8\n", LIGHT_BLUE);
	popall();
	asm volatile("iretq");
}
 void isr9()
{
	pushall();
	kPrintf("Unhandled exception: 9\n", LIGHT_BLUE);
	popall();
	asm volatile("iretq");
}
 void isr10()
{
	pushall();
	kPrintf("Unhandled exception: 10\n", LIGHT_BLUE);
	popall();
	asm volatile("iretq");
}
 void isr11()
{
	pushall();
	kPrintf("Unhandled exception: 11\n", LIGHT_BLUE);
	popall();
	asm volatile("iretq");
}
 void isr12()
{
	pushall();
	kPrintf("Unhandled exception: 12\n", LIGHT_BLUE);
	popall();
	asm volatile("iretq");
}
 void isr13()
{
	pushall();
	kPrintf("Unhandled exception: 13\n", LIGHT_BLUE);
	popall();
	asm volatile("iretq");
}
 void isr14()
{
	pushall();
	kPrintf("Unhandled exception: 14\n", LIGHT_BLUE);
	popall();
	asm volatile("iretq");
}
 void isr15()
{
	pushall();
	kPrintf("Unhandled exception: 15\n", LIGHT_BLUE);
	popall();
	asm volatile("iretq");
}
 void isr16()
{
	pushall();
	kPrintf("Unhandled exception: 16\n", LIGHT_BLUE);
	popall();
	asm volatile("iretq");
}
 void isr17()
{
	pushall();
	kPrintf("Unhandled exception: 17\n", LIGHT_BLUE);
	popall();
	asm volatile("iretq");
}
 void isr18()
{
	pushall();
	kPrintf("Unhandled exception: 18\n", LIGHT_BLUE);
	popall();
	asm volatile("iretq");
}
 void isr19()
{
	pushall();
	kPrintf("Unhandled exception: 19\n", LIGHT_BLUE);
	popall();
	asm volatile("iretq");
}
 void isr20()
{
	pushall();
	kPrintf("Unhandled exception: 20\n", LIGHT_BLUE);
	popall();
	asm volatile("iretq");
}
 void isr21()
{
	pushall();
	kPrintf("Unhandled exception: 21\n", LIGHT_BLUE);
	popall();
	asm volatile("iretq");
}
 void isr22()
{
	pushall();
	kPrintf("Unhandled exception: 22\n", LIGHT_BLUE);
	popall();
	asm volatile("iretq");
}
 void isr23()
{
	pushall();
	kPrintf("Unhandled exception: 23\n", LIGHT_BLUE);
	popall();
	asm volatile("iretq");
}
 void isr24()
{
	pushall();
	kPrintf("Unhandled exception: 24\n", LIGHT_BLUE);
	popall();
	asm volatile("iretq");
}
 void isr25()
{
	pushall();
	kPrintf("Unhandled exception: 25\n", LIGHT_BLUE);
	popall();
	asm volatile("iretq");
}
 void isr26()
{
	pushall();
	kPrintf("Unhandled exception: 26\n", LIGHT_BLUE);
	popall();
	asm volatile("iretq");
}
 void isr27()
{
	pushall();
	kPrintf("Unhandled exception: 27\n", LIGHT_BLUE);
	popall();
	asm volatile("iretq");
}
 void isr28()
{
	pushall();
	kPrintf("Unhandled exception: 28\n", LIGHT_BLUE);
	popall();
	asm volatile("iretq");
}
 void isr29()
{
	pushall();
	kPrintf("Unhandled exception: 29\n", LIGHT_BLUE);
	popall();
	asm volatile("iretq");
}
 void isr30()
{
	pushall();
	kPrintf("Unhandled exception: 30\n", LIGHT_BLUE);
	popall();
	asm volatile("iretq");
}
 void isr31()
{
	pushall();
	kPrintf("Unhandled exception: 31\n", LIGHT_BLUE);
	popall();
	asm volatile("iretq");
}
