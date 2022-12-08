
bios is executed directly from ROM the bios loads the boot loader into the Address 0x7C00 then the bootloader will load the kernel 

- a bootloader is a small program responsible for loading the kernel of an OS
- small program 

CPU -> executes instructions from the BIOS ROM

BIOS loads its self into RAM then continues execution from RAM

The BIos will initialize essential hardware
the bios looks for a bootloader to boot by searching all storage mediums for the boot signature 0x55AA
the BIOS loads the bootloader into RAM at absolute address0x7C00
the BIOs instructs the process to perform a jump to absolute address 0x7C00 and begin executing the operating systems bootloader