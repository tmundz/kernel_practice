ORG 0 
BITS 16

_start:
    jmp short start
    nop

times 33 db 0
start:
    jmp 0x7c0:step2


;old way CHS reading
;to read sectors into memory Ah expects 02h AL = number of sectors to read (nonzero)
;CH = low eight bits of cylinder number CL = sector num 1-63 (bits 0-5)
;DH =head num DL is the driver number
step2:
    cli ;clear interrupts
    mov ax, 0x7c0 ; can not move value to ds directly so move to ax first 
    mov ds, ax ;move ax to data segment
    mov es, ax ;move ax to extra segment
    mov ax, 0x00 ;move 0 to ax
    mov ss, ax;move stack segment to 0x00
    mov sp, 0x7c00 ;stack pointer points to this address
    sti ; enables interrupts
    
    mov ah, 2 ; READ sector command
    mov al, 1 ; 1 sector to read
    mov ch, 0 ; Cylinder low eight bits
    mov cl, 2 ; Read sector two
    mov dh, 0 ; head number

    mov bx, buffer
    int 0x13
    jc error

    mov si, buffer
    call print
    jmp $

error: 
    mov si, error_message
    call print
    jmp $ ;keeps jumping to itself 


print:
    mov bx, 0
.loop:
    lodsb ;loads char
    cmp al, 0
    je .done; jump to done if al = 0
    call print_char
    jmp .loop
.done:
    ret
   
print_char:
    mov ah,0eh 
    int 0x10 ;intterupt 10 allows video-teletype output
    ret ;returns

error_message: db 'Failed to load sector', 0

times 510-($ - $$) db 0 ;fills 510 bytes and pads the rest with 0 
dw 0xAA55 ;x86 machines are little endian 

buffer:; writes to address 0x7e00 

