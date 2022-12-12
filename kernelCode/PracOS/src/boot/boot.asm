ORG 0x7c00
BITS 16
; get the proper offsets
CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start 


_start:
    jmp short start
    nop

times 33 db 0
start:
    jmp 0:step2


;old way CHS reading
;to read sectors into memory Ah expects 02h AL = number of sectors to read (nonzero)
;CH = low eight bits of cylinder number CL = sector num 1-63 (bits 0-5)
;DH =head num DL is the driver number
step2:
    cli ;clear interrupts
    mov ax, 0x0 ; can not move value to ds directly so move to ax first 
    mov ds, ax ;move ax to data segment
    mov es, ax ;move ax to extra segment
    mov ss, ax;move stack segment to 0x00
    mov sp, 0x7c00 ;stack pointer points to this address
    sti ; enables interrupts

.load_protected:
    cli
    lgdt[gdt_descriptor]
    mov eax, cr0
    or eax, 0x1 
    mov cr0, eax
    ;jmp CODE_SEG:load32; switches from the code seg to code selector
    jmp $

gdt_start:
gdt_null:
    dd 0x0 
    dd 0x0 

; offset 0x8
gdt_code:       ; CS SHOULD POINT TO THIS
    dw 0xffff   ;segment limit 0-15 bits
    dw 0        ; base first 0-15 bits
    db 0        ;base 16-23 bits
    db 0x9a     ;access bits 
    db 11001111b ; high 4 bit flags and low 4 bit flags
    db 0        ; base 24-31 bits

gdt_data: ; DS,SS,ES, FS, GS 
    dw 0xffff    ;segment limit 0-15 bits
    dw 0        ; base first 0-15 bits
    db 0        ;base 16-23 bits
    db 0x92     ;access bits 
    db 11001111b ; high 4 bit flags and low 4 bit flags
    db 0        ; base 24-31 bits

gdt_end:


gdt_descriptor:
    dw gdt_end - gdt_start - 1 
    dd gdt_start


times 510-($ - $$) db 0 ;fills 510 bytes and pads the rest with 0 
dw 0xAA55 ;x86 machines are little endian 

