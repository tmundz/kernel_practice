ORG 0 
BITS 16

_start:
    jmp short start
    nop

times 33 db 0
start:
    jmp 0x7c0:step2

step2:
    cli ;clear interrupts
    mov ax, 0x7c0 ; can not move value to ds directly so move to ax first 
    mov ds, ax ;move ax to data segment
    mov es, ax ;move ax to extra segment
    mov ax, 0x00 ;move 0 to ax
    mov ss, ax;move stack segment to 0x00
    mov sp, 0x7c00 ;stack pointer points to this address
    sti ; enables interrupts

    mov si, message ;move the address of the label message to SI register
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

message: db 'Welcome to my os', 0

times 510-($ - $$) db 0 ;fills 510 bytes and pads the rest with 0 
dw 0xAA55 ;x86 machines are little endian 



