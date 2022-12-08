ORG 0x7c00
BITS 16

start:
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

message: db 'Welcome to my OS', 0

times 510-($ - $$) db 0 ;fills 510 bytes and pads the rest with 0 
dw 0xAA55 ;x86 machines are little endian 



