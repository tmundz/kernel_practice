

1 MB of Ram accessible 
based on the original X86 Design 
no security
16 bits accessible at one time


can only access 65kb in  real mode


<h3>Segmentation Memory Model </h3>
CS -Code Seg 
SS - Stack seg
DS - Data seg
ES - Extra seg

take a segment register * 16 + offset to calculate the absolute offset
code seg = 0x7c0
Assembly Origin "org " = 0
first instruction is at origin zero so the offset is 0

0 offset 0x7cff
seg 07co ofset 0xFF
seg 0x7cf offset 0x0F

calc for 0x7cff
-----------------------

0x7cf * 16 = 0x7cf0
0x7cf0 + 0x0f = 0x7cff

lodsb uses the DS:Si register combination 

org 0
mov ax, 07c0 ; move value to ax reg
mov ds, ax ; move ax to the data segment
mov si, 0x1f
lodsb