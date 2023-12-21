#ifndef CONFIG_H
#define CONFIG_H

#define KERNEL_CODE_SELECTOR 0x08
#define KERNEL_DATA_SELECTOR 0x10
#define PRACOS_TOTAL_INTERRUPTS 512

// 100MB heap size
#define PRACOS_HEAP_SIZE_BYTES 104857600
#define PRACOS_HEAP_BLOCK_SIZE 4096
#define PRACOS_HEAP_ADDRESS 0x01000000
#define PRACOS_TABLE_ADDRESS 0x00007E00 //address of the heap table


#define PRACOS_SECTOR_SIZE 512 //normal hard disk size
#endif

