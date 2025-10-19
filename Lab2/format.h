#ifndef FORMAT_H
#define FORMAT_H

static void init_format(Format* format)
{
    format->flag_plus = 0;
    format->flag_minus = 0;
    format->flag_space = 0;
    format->flag_zero = 0;
    format->flag_hash = 0;
    format->width = 0;
    format->specifier = '\0';
}

#endif	  // FORMAT_H