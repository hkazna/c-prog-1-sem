#ifndef INIT_INT128_H
#define INIT_INT128_H

#include <stdint.h>

typedef struct
{
    uint64_t low;
    uint64_t high;
} int128_t;

int128_t int128_add(int128_t a, int128_t b);

int128_t int128_multy(int128_t a, int128_t b);

int128_t int128_shift_right(int128_t value);

int128_t int128_sub(int128_t a, int128_t b);

int128_t int128_division(int128_t dividend, int128_t divisor, int128_t* remainder);

int128_t int128_negative(int128_t number);

int128_t int128_parseNum(const char* str);

void int128_toString(int128_t number, char* str, int isUpper, int base);

#endif	  // INIT_INT128_H