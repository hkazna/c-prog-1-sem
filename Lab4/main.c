#include "convertation.h"
#include "open_the_file.h"
#include "write_to_the_file.h"

#include <png.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <input_png_file> <output_png_file>\n", argv[0]);

        return 1;
    }

    const char *input_file = argv[1];
    const char *output_file = argv[2];

    png_structp png_ptr = NULL;
    png_infop info_ptr = NULL;
    png_bytep *row_pointers = NULL;
    png_uint_32 width, height;
    int color_type, bit_depth;

    if (read_png(input_file, &png_ptr, &info_ptr,
                 &row_pointers, &width, &height, &color_type, &bit_depth))
    {
        fprintf(stderr, "Error: Failed to read input PNG file.\n");

        return 1;
    }

    convert_color(row_pointers, width, height, &color_type, png_ptr, info_ptr);

    if (write_png(output_file, row_pointers, width, height, bit_depth, color_type))
    {
        fprintf(stderr, "Error: Failed to write output PNG file.\n");

        return 1;
    }

    for (int y = 0; y < height; y++)
    {
        free(row_pointers[y]);
    }

    free(row_pointers);
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
    printf("Conversion successful: %s -> %s\n", input_file, output_file);

    return 0;
}