#ifndef DISK_H
#define DISK_H

typedef unsigned int PRACOS_DISK_TYPE;

//represents a real hard disk
#define PRACOS_DISK_TYPE_REAL 0

struct disk {
    PRACOS_DISK_TYPE type;
    int sector_size;
};

struct disk* disk_get(int index);
void disk_search_and_init();
int disk_read_block(struct disk* idisk, unsigned int lba, int total, void* buf);

#endif