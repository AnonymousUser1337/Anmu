
[BITS 16] 


global _Start:
_Start: 

 jmp  main 
 extern kMain; tell nasm and the linker that this function is not located in this file 
;;;;;;;;;;;;;;;;;; 
;                                ; 
;                                ; 
;    Constants   ; 
;                                ; 
;;;;;;;;;;;;;;;;;; 
%DEFINE TEAL 0x03 
%DEFINE RED 0x04 
%DEFINE PURPLE 0x05 
%DEFINE VIDEO_MEM 0xB8000 
%DEFINE COLS    80                      ; width and height of screen 
%DEFINE LINES   25 
%DEFINE TEAL_B 0x3F203F203F203F20
%DEFINE BLUE_B 0x1F201F201F201F20
%DEFINE RED_B 0x4F204F204F204F20

X_POS:  db 0 
Y_POS:  db 0 


;;;;;;;;;;;;;;;;;; 
;    Enabling    ; 
;    The A20     ; 
;         line           ; 
;;;;;;;;;;;;;;;;;; 
EnableA20: 

    IN AL, 0x92         ; A20, using fast A20 gate 
    MOV CL, AL 
    AND CL, 2 
    JNZ .skip            ; if a20 bit seems set, don't touch it 
    OR AL, 2 
    OUT 0x92, AL 
    .skip: 

ret 


[BITS 32] 
        clear: 
         
        pusha 
        mov edi, VIDEO_MEM 
        mov BYTE[edi], ' ' 
        mov BYTE[edi+1], TEAL
        rep stosw 
        MOV BYTE[X_POS], 0x0 
        MOV BYTE [Y_POS], 0x0 
        popa 
        ret 
         
        sPrint: 
        pusha 
                jmp .start 
                .Row: 
                call NewLine 
                MOV BYTE[EDI], ' ' 
                jmp .Next 
                .start: 
                MOV EDI, VIDEO_MEM 
                xor ecx, ecx 
                xor eax, eax 
                mov     ecx, COLS*2             ; Mode 7 has 2 bytes per char, so its COLS*2 bytes per line 
                mov     al, BYTE [Y_POS]        ; get y pos 
                mul     ecx                     ; multiply y*COLS 
                push    eax                     ; save eax--the multiplication 
                  
                mov     al, byte [X_POS]        ; multiply _CurX by 2 because it is 2 bytes per char 
                mov     cl, 2 
                mul     cl 
                pop     ecx                     ; pop y*COLS result 
                add     eax, ecx 
                 
                 
                add edi, eax 
                mov al,BYTE[bx] 
                 
                cmp al, 0x0;check if end 
                je .Done 
                cmp al, 0xA;check if new line 
                je .Row 
                 
                mov BYTE[edi],al  
                .Next: 
                mov BYTE[edi+1], TEAL
                INC BX 
                inc     BYTE[X_POS]             ; go to next character 
                cmp     BYTE[X_POS], COLS               ; are we at the end of the line? 
                je      .Row                    ; yep-go to next row 
                 
                 
                jmp .start 
        .Done: 
         
         
        popa 
         
        ret 
        NewLine: 
        inc BYTE[Y_POS] 
        MOV BYTE[X_POS], -1 
         
        ret 
      


	[BITS 16]

main:            
;first stage of bootloader is loaded at the address 0x07c0:0 
        ;second stage of bootloader is loaded at address 0x200:0x0 


        cli 
   xor ax, ax         ; All segments set to 0, flat memory model 
   mov ds, ax 
   mov es, ax 
   mov gs, ax 
   mov fs, ax 
   mov ss, ax 
   ; 
   ; Set stack top SS:0xffff 
   ; 
   mov sp, 0x0FFFF 
   ; 


        mov [CDDriveNumber], dl 

        SwitchToProtectedMode: 

        lgdt [GDT_32];load the gdt 
        call EnableA20 


        mov eax, cr0 
        or eax, 1 
        mov cr0, eax 


         ; Flush CS and set code selector 
   ; 
        jmp 0x8:Protected_Mode 

        [BITS 32];Declare 32 bits 

        Protected_Mode: 

		

        mov eax,0x10    ; load 4 GB data descriptor
        mov ds,ax           ; to all data segment registers
        mov es,ax
        mov fs,ax
        mov gs,ax
        mov ss,ax
		
		call clear
		xor bx, bx
		mov bx, Entered_PMODE
		call sPrint
		
        mov eax,cr4
        or  eax,1 << 5
        mov cr4,eax         ; enable physical-address extensions

        mov edi,70000h
        mov ecx,4000h >> 2
        xor eax,eax
        rep stosd           ; clear the page tables

        mov dword [70000h],71000h + 111b ; first PDP table
        mov dword [71000h],72000h + 111b ; first page directory
        mov dword [72000h],73000h + 111b ; first page table

        mov edi,73000h      ; address of first page table
        mov eax,0 + 111b
        mov ecx,256         ; number of pages to map (1 MB)
    make_page_entries:
        stosd
        add edi,4
        add eax,1000h
        loop    make_page_entries

        mov eax,70000h
        mov cr3,eax         ; load page-map level-4 base

        mov ecx,0C0000080h      ; EFER MSR
        rdmsr
        or  eax,1 << 8      ; enable long mode
        wrmsr


        lgdt[GDT_64.Pointer]

        mov eax,cr0       
        or  eax,1 << 31
        mov cr0,eax         ; enable paging



        jmp 0x08:Long_Mode 
        [BITS 64] 


        Long_Mode:
			
			call clear_64
			
			; Display "Hello World!" in red and white
			MOV EDI, VIDEO_MEM
			mov rax, 0x4F6C4F6C4F654F48    
			mov [edi],rax
 
			mov rax, 0x4F6F4F574F204F6F
			mov [edi + 8], rax
 
			mov rax, 0x4F214F644F6C4F72
			mov [edi + 16], rax
			MOV EDI, VIDEO_MEM
			mov rax, 0x4F6C4F6C4F654F48    
			mov [edi],rax
 
			mov rax, 0x4F6F4F574F204F6F
			mov [edi + 8], rax
 
			mov rax, 0x4F214F644F6C4F72
			mov [edi + 16], rax
			
			
			call kMain; Execute the kernel
			
		cli
		hlt
		
		clear_64:
		 ; Blank out the screen to a blue color.
			mov edi, VIDEO_MEM
			mov rcx, 500                      ; Since we are clearing QWORDs over here, we put the count as Count/4.
			mov rax, RED_B       ; Set the value to set the screen to: Red background, white foreground, blank spaces.
			rep stosq                         ; Clear the entire screen. 
		ret
        
Entered_PMODE:  db "You have succcessfully entered Protected Mode :D",0xA, 0 
LOAD_SUCCESS:   db "Stage 2 Loaded Successfully",0xA, 0 
CDDriveNumber:  db 0 

GDT_START: 
;null descriptor 
dd 0 
dd 0 
;data descriptor 
dw 0xFFFF 
dw 0 
db 0 
db 10011010b 
db 11001111b 
db 0 
;code descriptor 
dw 0xFFFF 
dw 0 
db 0 
db 10010010b 
db 11001111b 
db 0 
GDT_END: 
align 4 
GDT_32: 
dw GDT_END - GDT_START - 1 
dd GDT_START 



GDT_64: 
.Null: 
    dq 0x0000000000000000             ; Null Descriptor - should be present. 
  
.Code_64: 
    dq 0x0020980000000000             ; 64-bit code descriptor.  
    dq 0x0000900000000000             ; 64-bit data descriptor.  
.Pointer: 
    dw $ - GDT_64 - 1                    ; 16-bit Size (Limit) of GDT. 
    dd GDT_64                            ; 32-bit Base Address of GDT. (CPU will zero extend to 64-bit) 

         
         
         




