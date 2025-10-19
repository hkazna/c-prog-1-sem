#include "formatting.h"

#include "format.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>

void parse_format(
        const char* format_string,
        Format* format)
{
    init_format(format);
    const char* p = format_string;

    if (*p++ != '%')
    {
        return;
    }

    while (*p == '+' || *p == '-' || *p == ' ' || *p == '#' || *p == '0')
    {
        switch (*p++)
        {
            case '+':
                format->flag_plus = 1;
                break;
            case '-':
                format->flag_minus = 1;
                break;
            case ' ':
                format->flag_space = 1;
                break;
            case '#':
                format->flag_hash = 1;
                break;
            case '0':
                format->flag_zero = 1;
                break;
        }
    }

    while (isdigit(*p))
    {
        format->width = format->width * 10 + (*p++ - '0');
    }

    if (*p == 'd' || *p == 'x' || *p == 'X' || *p == 'o' || *p == 'b')
    {
        format->specifier = *p++;
    }
}

void format_output(
        char* out_buf,
        const char* num_str,
        Format* format, int is_negative)
{
    char temp[256] = { 0 };
    int pos = 0;

    if (is_negative && num_str[0] != '-')
    {
        temp[pos++] = '-';
    } else if (format->flag_plus)
    {
        temp[pos++] = '+';
    } else if (format->flag_space)
    {
        temp[pos++] = ' ';
    }

    if (format->flag_hash && format->specifier != 'd')
    {
        if (format->specifier == 'x')
        {
            strcpy(temp + pos, "0x");
            pos += 2;
        } else if (format->specifier == 'X')
        {
            strcpy(temp + pos, "0X");
            pos += 2;
        } else if (format->specifier == 'o')
        {
            temp[pos++] = '0';
        } else if (format->specifier == 'b')
        {
            strcpy(temp + pos, "0b");
            pos += 2;
        }
    }

    strcpy(temp + pos, num_str);
    pos += strlen(num_str);
    int total_len = pos;

    if (format->width > total_len)
    {
        int padding = format->width - total_len;

        if (format->flag_minus)
        {
            strcpy(out_buf, temp);
            memset(out_buf + total_len, ' ', padding);
        } else
        {
            if (format->flag_zero)
            {
                if (temp[0] == '+' || temp[0] == '-' || temp[0] == ' ')
                {
                    out_buf[0] = temp[0];
                    memset(out_buf + 1, '0', padding);
                    strcpy(out_buf + 1 + padding, temp + 1);
                } else
                {
                    memset(out_buf, '0', padding);
                    strcpy(out_buf + padding, temp);
                }
            } else
            {
                memset(out_buf, ' ', padding);
                strcpy(out_buf + padding, temp);
            }
        }
    } else
    {
        strcpy(out_buf, temp);
    }
}