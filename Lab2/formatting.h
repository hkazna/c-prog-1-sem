#ifndef FORMATTING_H
#define FORMATTING_H

#include <stdint.h>

typedef struct
{
    int flag_plus;
    int flag_minus;
    int flag_space;
    int flag_zero;
    int flag_hash;
    int width;
    char specifier;
} Format;

void parse_format(const char* format_string, Format* format);

void format_output(char* out_buf, const char* num_str, Format* format, int is_negative);

#endif	  // FORMATTING_H