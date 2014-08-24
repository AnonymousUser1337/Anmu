;for now just call a common handler for all isr's
[GLOBAL isr0]

isr0:

	call common_handler

ret
[GLOBAL isr1]

isr1:

call common_handler

ret
[GLOBAL isr2]

isr2:

call common_handler

ret
[GLOBAL isr3]

isr3:

call common_handler

ret
[GLOBAL isr4]

isr4:

call common_handler

ret
[GLOBAL isr5]

isr5:

call common_handler

ret
[GLOBAL isr6]

isr6:

call common_handler

ret
[GLOBAL isr7]

isr7:

call common_handler

ret
[GLOBAL isr8]

isr8:

call common_handler

ret
[GLOBAL isr9]

isr9:

call common_handler

ret
[GLOBAL isr10]

isr10:

call common_handler

ret
[GLOBAL isr11]

isr11:

call common_handler

ret
[GLOBAL isr12]

isr12:

call common_handler

ret
[GLOBAL isr13]

isr13:

call common_handler

ret
[GLOBAL isr14]

isr14:

call common_handler

ret
[GLOBAL isr15]

isr15:

call common_handler

ret
[GLOBAL isr16]

isr16:

call common_handler

ret
[GLOBAL isr17]

isr17:

call common_handler

ret
[GLOBAL isr18]

isr18:

call common_handler

ret
[GLOBAL isr19]

isr19:

call common_handler

ret
[GLOBAL isr20]

isr20:

call common_handler

ret
[GLOBAL isr21]

isr21:

call common_handler

ret
[GLOBAL isr22]

isr22:

call common_handler

ret
[GLOBAL isr23]

isr23:

call common_handler

ret
[GLOBAL isr24]

isr24:

call common_handler

ret
[GLOBAL isr25]

isr25:

call common_handler

ret
[GLOBAL isr26]

isr26:

call common_handler

ret
[GLOBAL isr27]

isr27:

call common_handler

ret
[GLOBAL isr28]

isr28:

call common_handler

ret
[GLOBAL isr29]

isr29:

call common_handler

ret
[GLOBAL isr30]

isr30:

call common_handler

ret
[GLOBAL isr31]

isr31:

call common_handler

ret
[EXTERN ISR_HANDLER]
common_handler:
	;preserve registers
	push rax
	push rbx
	push rcx
	push rdx
	push rsi
	push rdi
	push rbp
	
	

	call ISR_HANDLER
	
	;restore registers
	pop rbp
	pop rdi
	pop rsi
	pop rdx
	pop rcx
	pop rbx
	pop rax
	
	iretq;return to what the cpu was doing
	
	
ret
[GLOBAL LOAD_IDT]
LOAD_IDT:

	cli;disable interrupts again just incase
	
	LIDT[rsp+4];Load the gdt from the stack
	
	sti;enable interrupts

ret
