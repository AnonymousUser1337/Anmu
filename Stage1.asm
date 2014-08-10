[BITS   16]

[ORG  0x0]

start : jmp 0x7c0:main
;
; boot info block
;
times 8-($-$$) db 0
BootInfoPrimVolDescr   resd 1
BootInfoFileLoc           resd 1
BootInfoFileLength      resd  1
BootInfoChecksum       resd 1
BootInfoReserved        resd 40


;Colors for text
%DEFINE TEAL 0x03
%DEFINE RED 0x04
%DEFINE PURPLE 0x05
%define ISO_DIRECTORY_LEN 33      ; length of constant part of directory record
%define ISO_DIRECTORY_LBA_OFFSET 2

COL: db 0
ROW:  db 0
LOADSEG equ 0x200 ; ?
LOADOFFS equ 0 ; ?
jumptarget dw LOADOFFS, LOADSEG
;macro for print
%macro Print 2
pusha
	xor ax, ax
	xor dx, dx
	mov dh, BYTE[ROW];puts the row into the dh register
	mov dl, BYTE[COL]
	xor bx, bx
	mov bl, %2
	mov si, %1
	call cPrint
	mov BYTE[COL], dl
 ;saves the rows for the next time we need to print
popa
%endmacro

Print_ln:

pusha   
	mov dh, BYTE[ROW]          
    mov ah, 0x02            ;set cursor pos
    mov bh, 0x00            ;page 00
    inc dh            		;row 00
    mov dl, 0x00            ;col. 00    
	int 0x10
	mov BYTE[ROW], dh
	mov BYTE[COL], 0
	popa


ret

itoa:;number is passed into ax
jmp .beggining
.negate:

neg ax
push ax

mov al, '-'
mov ah, 0xe 
int 0x10
pop ax
jmp .top
.beggining:
xor bx , bx
mov cx, 10;mov into cx 10
cmp ax, 0
jl .negate


.top:
	;divide by 10 and push remainder onto stack 
	xor dx, dx;clear out remainder
	div cx ;divide ax by 10
	push dx;push the remainder onto the stack for later
	inc bx;count the number of digits
	test ax,ax;if ax = 0 then stop
jne .top

.loop:
	pop ax;restore the remainder
	add ax, '0';convert to ASCII
	mov ah, 0xe;print
	int 0x10
	dec bx;get ready for the next digit
	cmp bx, 0;if not zero then jump to .loop	
jne .loop
ret

cPrint:                   ; Routine: output string in SI to screen


 .top:
 	;Paramaters for Input 
    mov ah, 09h             ; Must be 9 to print color
    mov cx, 0x01 			;x position
    lodsb                   ; Get character from string
    test al, al
    je .done                ; If char is zero, end of string
    int 0x10                 ; Otherwise, print it

    mov ah, 0x02			;set cursor position
    mov bh, 0x00			;page
    inc dl 		;column
    int 0x10				;changes the cursor position so the next char can be written at the new location
    jmp .top

 .done:
    ret

;clears the screen and sets the cursor position to the top left 
 clear:
    mov ah, 0x0F            ;get current video mode
    mov al, 0x00            ;reset register
    int 0x10                ;get video mode
    mov ah, 0x00            ;set video mode
    int 0x10                ;reset screen
    mov ah, 0x02            ;set cursor pos
    mov bh, 0x01            ;page 00
    mov dh, 0x00            ;row 00
    mov dl, 0x00            ;col. 00
    int 0x10    	;set pos
	mov BYTE[ROW], DH
	mov BYTE[COL],0
ret


Read_Sectors:  
        ;/* Read the sector into memory. */
       
		.ForLoop:
			mov     ah,042h
			xor     al,al
			mov     si, DiskAddressPacket
			mov     dl, [CDDriveNumber]
			int     013h
        jnc    .Success 	; /* read error? */

        Print Read_Sector_Error_MSG, RED
		
		cli
		hlt

.Success:
		Print Progress_MSG , PURPLE
		inc WORD[DiskAddressPacket.SectorsToRead]
		
        loop    .ForLoop
		call Print_ln
ret
CHECK_DESC:
	Print CHECK_DESC_MSG, TEAL
	mov es, WORD[DiskAddressPacket.Segment]
	mov di, WORD[DiskAddressPacket.Offset]
	
	xor bx, bx
	.top:
		mov al, BYTE[ES:DI+BX]
		mov BYTE[VOLUME+BX], al
		
		inc bx
		cmp al, ' '
		je .Done
		jmp .top
	.Done:

	;see if the Volume descriptor contains the Signature
	xor BX, BX; clear out bx
	add BX, 0x01;move into bx the offset
	xor cx, cx;clear out cx
	.toploop:
	xor ax, ax
	mov al, BYTE[VOLUME+BX] 
	cmp al, BYTE[CD_Signature+BX-1]
	je .FOUND_IT; Compare the letters Byte by Byte to see if they are the same
	jmp .Done2
	inc CX;increments if even one letter is wrong
	.FOUND_IT:
	Print Progress_MSG, PURPLE
	inc BX;Increments the offset
	
	jmp .toploop
	
	.Done2:
	cmp CX, 0;if signatures don't match then stop the system and print an error Message
	jne .FAIL
	call Print_ln
	
	Print FOUND_CD, TEAL
	jmp .Done3
	.FAIL:
	Print FILE_NOT_FOUND, RED
	cli
	hlt
	.Done3:
	call Print_ln
ret
READ_STAGE2:
	Print LOADING_STAGE2_MSG, TEAL
	call Print_ln
		
	mov di, [DiskAddressPacket.Offset]
	mov es, [DiskAddressPacket.Segment]

	
    xor BX, BX;clears out bx
	xor si, si ;clears out si
	xor cx, cx
	MOV CX, [ES:DI+32]
    .top:
		
		
		MOV AL,BYTE[ES:DI+BX] ;moves a byte of a possible start of a file entry
		cmp AL,BYTE[STAGE2];compares it with file I want
		je .Done;if it is then jump out of loop
		INC BX;get ready for next file entry
	jmp .top
	
	.Done:
	Print Found_Possible_FILE, TEAL;prints it found a possible file
	XOR SI, SI;Clear out for use
	;=INC BX
	;INC SI
	xor cx, cx;clear out for use as counter
	.top2:;compares strings to see if they are the same
		;xor ax, ax;clears out acx
		
		;prints out a letter to the screen
		MOV AL, BYTE[ES:DI+BX]
		MOV AH, 0xE
		INT 0x010
		;;;;;;;;;;;;;;;;;;
		
		xor ax, ax
		MOV AL, BYTE [ES:DI+BX]
		cmp AL, BYTE[STAGE2+SI]
		
		je .Success
		call Print_ln
		jmp .top
		.Success:
			
			;Print Progress_MSG, PURPLE;progress message
						
			
			INC BX;get ready for next character
			INC SI;get ready for next character	
			INC CX; increment counter 
	cmp CX, WORD[STAGE_2_LEN] 
	jne .top2
	;call clear
	call Print_ln
	Print File_Found, TEAL;prints found file if found
	call Print_ln
	
	Print Reading_Sectors, TEAL;prints reading sector message
	;call clear
	
	
	%define STAGE2_LEN 12            ; STAGE2.BIN;1
	%define ISO_DIRECTORY_LEN 33      ; length of constant part of directory record
	%define ISO_DIRECTORY_LBA_OFFSET 2  ; offset of LBA member of structure

   ;
   ; Set SEG:OFFSET to 0x2000 load address
   ;
   mov word [DiskAddressPacket.Offset], 0
   mov word [DiskAddressPacket.Segment], 0x200
   ;
   ; Adjust BX
   ;
   mov di, bx   ; save bx and get rid of it. Only want to use ES:DI
   xor bx, bx
   ;
   ; Adjust ES:DI to point to LBA / Extent member of directory structure
   ;
   sub di, STAGE2_LEN
   sub di, ISO_DIRECTORY_LEN
   add di, ISO_DIRECTORY_LBA_OFFSET
   ;
   ; Now [ES:DI] -> LBA / Extent of directory record in both endian formats; grab little endian format into EAX
   ;
   mov eax, [ES:DI]
   ;
   ; Now EAX = LBA to start loading from. Store it
   ;
   mov dword [DiskAddressPacket.End], EAX
   ;
   ; Should calculate this from extentSize field: sector count = (extentSize / sectorSize) + 1
   ;
   mov word [DiskAddressPacket.SectorsToRead], 4;which sector to start reading from
	
	xor cx, cx;clears out cx
	mov cx, 0x01;puts in cx 0x01 for how many sectors to read
	call Read_Sectors;calls the read sectors
	Print READ_SUCCESS, TEAL;if it gets here that means it was successful
	;jump to where the file is located and run it
	
	call Print_ln
	MOV AX, ES
	call itoa
	
	
	mov AL, ':'
	MOV AH, 0xE
	INT 0x010
	
	

	MOV AX, DI
	call itoa
	
	call Print_ln
	;call clear
	mov dl, [CDDriveNumber]

	push	0x200
	push	0x000
	retf
	 
	
	
	.FAIL:;it failed so print that the file wasn't found and halt the system
	;call Print_ln
	Print FILE_NOT_FOUND, RED
	cli
	hlt
	         
ret
main:
	;first stage of bootloader is loaded at the address 0x07c0:0x0
	;second stage of bootloader is loaded at address 0x5000:0x0
	cli  
	mov ax, 0x07c0
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    ;Set up Stack
	xor ax, ax
    mov ss, ax
    mov sp, 0xFFFE
	sti
	
	mov     [CDDriveNumber],dl
	call clear


	Print W_MSG, TEAL;prints the loading message in colour
	Print DOTS, PURPLE
	call Print_ln
	call Print_ln
	
	Print BOOT_MSG, TEAL
	call Print_ln
	
	
	Print BootInfoPrimVolDescr_MSG, TEAL
	MOV AX, WORD[BootInfoPrimVolDescr]
	call itoa
	call Print_ln
	
	Print BootInfoFileLoc_MSG, TEAL
	MOV AX,  WORD[BootInfoFileLoc]
	call itoa
	call Print_ln
	
	Print BootInfoFileLength_MSG, TEAL
	MOV AX, WORD[BootInfoFileLength]
	call itoa
	call Print_ln
	
	Print BootInfoChecksum_MSG, TEAL
	MOV AX, WORD[BootInfoChecksum]
	call itoa
	call Print_ln
	
	Print BootInfoReserved_MSG, TEAL
	MOV AX, WORD[BootInfoReserved]
	call itoa
	call Print_ln
	
	call Print_ln


	
	

	;First find the Signature of the CD 
	Print Reading_Sectors, TEAL
	LOAD_SIGNATURE:
	mov cx, 0x04
	call Read_Sectors
	
	Print READ_SUCCESS, TEAL
	call Print_ln
	;load the Volume descriptor to the Volume variable
	call CHECK_DESC
	;Now Load the Root Directory from the Volume Descriptor
	LOAD_ROOT:
		;Print Reading_Sectors, TEAL
		mov es, WORD[DiskAddressPacket.Segment]
		mov di, WORD[DiskAddressPacket.Offset]
		
		XOR BX, BX
		MOV BX, 40 ;move in the offset
		VolumeLabelLoop: 

			MOV CL,[ES:DI+BX]                   ; Grab a letter 
			CMP CL,' '                          ; Is it a space? (Assumes end of string is space, may run out) 
			JE .VolumeLabelDone                 ; Yes, we are done 

			MOV [VOLUME+BX-40],CL 
			INC BX 
			JMP VolumeLabelLoop                 ; Need to compare BX to length of Volume Label on CD (32?) 

			.VolumeLabelDone: 
				Print Reading_Sectors, TEAL
				MOV byte [VOLUME+BX-40],0      ; End the string 

				MOV EAX,[ES:DI+158]                 ; LBA of root directory, where all things start. 
				;MOV [DiskAddressPacket.End],EAX     ; Load packet with new address on CD of the root directory 
				MOV [DiskAddressPacket.End],EAX     ; Load packet with new address on CD of the root directory 
				xor cx, cx
				mov cx, 0x04
				call Read_Sectors
			                             
				
				Print READ_SUCCESS, TEAL;if the program gets here it means it was a success
				call Print_ln
				
LOAD_STAGE2:
		
	call READ_STAGE2
		
		
		.FAILURE:
		Print FILE_NOT_FOUND, RED
		cli
		hlt
		
		
					
CDDriveNumber: 				db 	  	0x080
CD_Signature: 			   	db    	"CD001"
CD_FILE_VER:			   	db    	0x01
CD_FileNameLength:			db	  	0x0
CD_dir_curr_size:			db 		0x0
Reading_Sectors: 			db 		"Reading sectors", 0
CHECK_DESC_MSG:				db		"Checking for CD Signature",0
LOADING_STAGE2_MSG:			db		"Loading Stage 2 of boot loader",0
STAGE_2_LEN:				DW 		0xC
File_Found:					db		"File for Stage 2 of the bootloader was found!!",0
LOADING_STAGE2_FAILED:		db  	"Failed to load Stage 2 of the boot loader !!!!!",0
Found_Possible_FILE:		db		"Found Possible File: ",0
Colon: 						db		":",0
FILE_ENTRY:					db 		0
JolietSig       			DB  	25h, 2fh, 45h                               ; this is the value of the escape sequence for a Joliet CD 
BOOT_MSG:					DB 		"Boot Info Table:", 0				
DOTS:						db 		".....",0	
					;Disk Address Packet				
DiskAddressPacket:          db 0x010,0 						  
.SectorsToRead:             dw 1                              ; Number of sectors to read (read size of OS) 
.Offset:                    dw 0                              ; Offset :0000h
.Segment:                   dw 0x0200                         ; Segment 01000h
.End:                       dq 0x010                             ; Sector 16 or 10h on CD-ROM 

VOLUME: 					DW 0
BootInfoPrimVolDescr_MSG:	db "Volume Descriptor: ", 0
BootInfoFileLoc_MSG         db "File Location:     ", 0  
BootInfoFileLength_MSG		db "File Length:       ", 0
BootInfoChecksum_MSG       	db "Checksum:          ", 0
BootInfoReserved_MSG        db "Reserved:          ", 0					
W_MSG: 						db "Loading Z-Boot", 0
STAGE2: 					db "STAGE2.BIN;1"
Read_Sector_Error_MSG: 		db "Error, failed to read sector",0
READ_SUCCESS: 				db "Sectors read correctly!",0
Progress_MSG: 				db ".",0
FILE_NOT_FOUND: 			db "Error, file not found!",0
FOUND_CD: 					db "Found the CD Signature!", 0
times 2046 - ($ - $$) 		db 0; padd out the rest of the file to 0









							
							
							
							
							
							
							
