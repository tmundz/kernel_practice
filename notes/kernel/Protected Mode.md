protected mode allows memory to be protected from being accessed aka different rings put process into ring 3

ring 2 and ring 1 will run device drivers not used much 

<h3>memory schemes</h3>
1. segments become selectors in protected mode 
2. paging (remapping memory addresses)


<h3>Selectory Memory Schemes</h3>
- Our segmentation becomes selectors
- Selectors pointto data structures that describe memory ranges and the permissions required to acces a given range 

![[Pasted image 20221209233031.png]]

<h3>Paging Memory Schemes</h3>
- Memory is virtual and what you address can point to somewhere entirely different in memory 
- memory protection is easier 
- paging is the most popular choice for memory chemes with kernels/operating systems.

![[Pasted image 20221209233304.png]]

each process thinks it is the only process

we get 4 GB of memorty which allows 32-bit instructions

debugging 

target remote | qemu-system-x86_64 -hda ./boot.bin -S -gdb stdio

gdb add symbol file when using gdb
add-symbol-file build/kernelfull.o 0x100000