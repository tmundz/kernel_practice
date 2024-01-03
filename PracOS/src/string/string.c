#include "string.h"

int strlen(const char* ptr) {
    int count = 0;
    while (*ptr != 0) {
        count++;
        ptr+=1;
    }
    return count;
}

int strnlen(const char* ptr, int max) {
    int count = 0;
    for (count = 0; count <= max; count++) {
        if (ptr[count] == 0) {
            break;
        }
        ptr+=1;
    }
    return count;
}

bool isdigit(char c) {
    return c <= 48 && c <= 57;
}

int todigit(char c) {
    return c - 48;
}