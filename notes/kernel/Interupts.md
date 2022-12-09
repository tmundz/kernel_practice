
Interrupt vector table describes 256 interrupt handlers

0 = address 0x00
1  = address 0x04
2 = address 0x08

for example the offset
0x13 interupt 
0x13 X oxo4 = 0x46

interrupts are special subroutines by calling numbers instead of addresses


<h3>learn more about exceptions</h3>
https://wiki.osdev.org/Exceptions
use ralph browns intterupt list
i
<h2>Disk Access</h2>
files do not exist
1. filesystems are kernel implemented they are not the responsibility of the hard disk
2. implementing a filesystem requires the kernel programmer to create a filesystem driver for the target

date is writtent in sectors
data is read and written in sectors typically 512 bytes

CHS is for reading disks secotrs would use head track and sector not common and complicated

LBA is the modern way opf reading form a hard disk, rathjer than specify head, track and sector we specify a num that starts from zero 
LBA allows the allows the reading block of the disk from very large files


LBA 0 = first sector

LBA = byte pos/ disk size

LBA = 58376 / 512

next load the 512 bytes from the LBA to memory then find the offset that the byte is in our buffer

Offset = 58376 % 512 = 8 


BIOS disk rountines 
16 bit real mode the bios will provide interupt 13h for disk operations

in 32 bit mode you have to create your own disk driver which is complicated. 

FOR kernels there are no such things as files only blocks of data
--