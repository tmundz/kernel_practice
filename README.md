<h1>LEARNING KERNEL DEVELOPMENT</h1>

I am trying to learn kernel and driver development
So I am creating this repo to document my notes along with my actual code. 

need qemu-system-x86_64

<h3>run the current boot command</h3>
nasm -f bin ./boot.asm -o ./boot.bin
qemu-system-x86_64 -hda ./boot.bin
