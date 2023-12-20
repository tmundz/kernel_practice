[BITS 32]

section .asm

global paging_load_directory
global enable_paging

paging_load_directory:
    push ebp
    mov ebp, esp
    mov eax, [ebp+8]
    mov cr3, eax
    pop ebp
    ret


enable_paging:
    push ebp
    mov ebp, esp #move stack pointer
    mov eax, cr0 #move cr0 to eax as cr0 cannot be changed directly
    or eax, 0x80000000
    move cr0, eax #move eax back to cr0
    pop ebp
    ret

