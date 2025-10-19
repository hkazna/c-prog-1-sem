#include "init_int128.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int128_t int128_add(int128_t a, int128_t b)
{
    int128_t result;
    uint64_t carry = 0;

    result.low = a.low + b.low;
    carry = (result.low < a.low);

    result.high = a.high + b.high + carry;

    return result;
}

int128_t int128_multy(int128_t a, int128_t b)
{
    int128_t result = { 0, 0 };

    uint64_t a_low = a.low & 0xFFFFFFFF;
    uint64_t a_high = a.low >> 32;
    uint64_t b_low = b.low & 0xFFFFFFFF;
    uint64_t b_high = b.low >> 32;

    uint64_t low_low = a_low * b_low;
    uint64_t low_high = a_low * b_high;
    uint64_t high_low = a_high * b_low;
    uint64_t high_high = a_high * b_high;

    result.low = low_low + ((low_high & 0xFFFFFFFF) << 32) + ((high_low & 0xFFFFFFFF) << 32);
    result.high = high_high + (low_high >> 32) + (high_low >> 32);

    result.high += a.high * b.low + a.low * b.high;

    return result;
}

int128_t int128_shift_right(int128_t value)
{
    int128_t result;
    result.low = (value.low >> 1) | ((value.high & 1) << 63);
    result.high = value.high >> 1;

    return result;
}

int128_t int128_sub(int128_t a, int128_t b)
{
    int128_t result;
    uint64_t borrow = 0;

    result.low = a.low - b.low;
    borrow = (a.low < b.low);

    result.high = a.high - b.high - borrow;

    return result;
}

int128_t int128_division(int128_t dividend, int128_t divisor, int128_t* remainder)
{
    int128_t result = { 0, 0 };
    int128_t current = { .low = 1, .high = 0 };
    int128_t temp = divisor;

    if (divisor.high == 0 && divisor.low == 0)
    {
        fprintf(stderr, "Division by zero error!\n");

        exit(1);
    }

    while (temp.high < dividend.high ||
    (temp.high == dividend.high && temp.low <= dividend.low))
    {
        temp = int128_add(temp, temp);
        current = int128_add(current, current);
    }

    while (current.high > 0 || current.low > 0)
    {
        if (temp.high < dividend.high ||
        (temp.high == dividend.high && temp.low <= dividend.low))
        {
            dividend = int128_sub(dividend, temp);
            result = int128_add(result, current);
        }

        temp = int128_shift_right(temp);
        current = int128_shift_right(current);
    }

    if (remainder)
    {
        *remainder = dividend;
    }

    return result;
}

int128_t int128_negative(int128_t number)
{
    int128_t result;

    result.low = ~number.low;
    result.high = ~number.high;

    result.low += 1;

    if (result.low == 0)
    {
        result.high += 1;
    }

    return result;
}

int128_t int128_parseNum(const char* str)
{
    int128_t result = { 0, 0 };
    int base = 10;
    int is_negative = 0;

    if (*str == '-')
    {
        is_negative = 1;
        str++;
    }

    if (*str == '0')
    {
        if (*(str + 1) == 'x' || *(str + 1) == 'X')
        {
            base = 16;
            str += 2;
        } else if (*(str + 1) == 'b' || *(str + 1) == 'B')
        {
            base = 2;
            str += 2;
        } else if (isdigit(*(str + 1)))
        {
            base = 8;
            str++;
        }
    }

    while (*str)
    {
        int digit = isdigit(*str) ? (*str - '0') : (tolower(*str) - 'a' + 10);

        if (digit >= base)
            break;

        result = int128_add(int128_multy(result, (int128_t)
        { .low = base, .high = 0 }), (int128_t){ .low = digit, .high = 0 });
        str++;
    }

    return is_negative ? int128_negative(result) : result;
}

void int128_toString(int128_t number, char* str, int isUpper, int base)
{
    const char* digits = isUpper ? "0123456789ABCDEF" : "0123456789abcdef";
    char buffer[128] = { 0 };
    int index = 127;

    int is_negative = (number.high & (1ULL << 63)) != 0;

    if (is_negative)
    {
        number = int128_negative(number);
    }

    if (number.low == 0 && number.high == 0)
    {
        buffer[--index] = '0';
    } else
    {
        int128_t remainder;

        while (number.low > 0 || number.high > 0)
        {
            number = int128_division(number,
                                     (int128_t){ .low = base, .high = 0 }, &remainder);
            buffer[--index] = digits[remainder.low];
        }
    }

    if (is_negative)
    {
        buffer[--index] = '-';
    }

    strcpy(str, &buffer[index]);
}