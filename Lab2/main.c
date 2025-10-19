#include "print.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        printf("Usage: %s <format> <number>\n", argv[0]);
        return 1;
    }

    char out_buf[256];
    const char* format = argv[1];
    const char* number = argv[2];

    print(out_buf, format, number);
    printf("%s\n", out_buf);

    return 0;
}