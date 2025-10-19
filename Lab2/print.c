#include "print.h"

#include "formatting.h"
#include "init_int128.h"
#include "print.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int is_valid_number(const char* input_str)
{
    if (*input_str == '-')
        input_str++;

    if (*input_str == '0')
    {
        if (tolower(*(input_str + 1)) == 'x' || tolower(*(input_str + 1)) == 'b')
            input_str += 2;

        else if (isdigit(*(input_str + 1)))
            input_str++;
    }

    while (*input_str)
    {
        if (!isdigit(*input_str) && !isxdigit(*input_str))
            return 0;

        input_str++;
    }

    return 1;
}

void print(char* output_buffer, const char* format_string, const char* number_string)
{
    if (format_string == NULL || number_string == NULL ||
    strlen(format_string) == 0 || strlen(number_string) == 0)
    {
        fprintf(stderr, "Error: invalid or unsupported format.\n");
        strcpy(output_buffer, "Error: Invalid format.\n");

        exit(1);
    }

    Format format_data;
    parse_format(format_string, &format_data);

    if (format_data.specifier == '0')
    {
        fprintf(stderr, "Error: Invalid or unsupported format.\n");
        strcpy(output_buffer, "Error: Invalid format.\n");

        exit(1);
    }

    if (!is_valid_number(number_string))
    {
        fprintf(stderr, "Error: Invalid number format.\n");
        strcpy(output_buffer, "Error: Invalid number.\n");

        exit(1);
    }

    int128_t parsed_number = int128_parseNum(number_string);
    int is_negative_number = (parsed_number.high & (1ULL << 63)) != 0;

    if (is_negative_number)
    {
        parsed_number = int128_negative(parsed_number);
    }

    char converted_number[256] = { 0 };
    int base_value = 10;
    int is_uppercase = 0;

    switch (format_data.specifier)
    {
        case 'b':
            base_value = 2;
            break;
        case 'o':
            base_value = 8;
            break;
        case 'x':
            base_value = 16;
            break;
        case 'X':
            base_value = 16;
            is_uppercase = 1;
            break;
        case 'd':
            base_value = 10;
            break;
        default:
            fprintf(stderr, "Error: Unsupported format specifier.\n");
            strcpy(output_buffer, "Error: Unsupported format.\n");

            return;
    }

    int128_toString(parsed_number, converted_number,
                    is_uppercase, base_value);
    memset(output_buffer, 0, 256);
    format_output(output_buffer, converted_number,
                  &format_data, is_negative_number);
}