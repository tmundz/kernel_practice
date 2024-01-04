#ifndef STRING_H
#define STRING_H
#include <stdbool.h>
/* 
gets the length of the string returns an int
runs in O(n)
*/
int strlen(const char* ptr);

/* 
gets the length of the string returns an int
runs in O(n) but will only go up to the max which then prevents a buffer overflow
*/
int strnlen(const char* ptr, int max);

/*
Confirms if the char is a digit based on the ascii table
*/
bool isdigit(char c);


/*
gets the ascii number of the char returns the number of a digit
*/
int todigit(char c);


#endif