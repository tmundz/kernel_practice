#include "pparser.h"
#include "kernel.h"
#include "string/string.h"
#include "memory/heap/kheap.h"
#include "memory/memory.h"

static int path_valid_format(const char* fname) {
    int len = strnlen(fname, PRACOS_MAX_PATH); // digits for the drive number
    return (len >= 3 && isdigit(fname[0]) && memcmp((void*)&fname[1], ":/", 2) == 0);
}