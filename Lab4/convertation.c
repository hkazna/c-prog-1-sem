#include "convertation.h"

#include "color_to_color.h"
#include "open_the_file.h"
#include "write_to_the_file.h"

#include <png.h>
#include <stdlib.h>

void convert_color(
        png_bytep *row_pointers,
        png_uint_32 width,
        png_uint_32 height,
        int *color_type,
        png_structp png_ptr,
        png_infop info_ptr)
{
    if (*color_type == PNG_COLOR_TYPE_GRAY)
    {
        convert_gray_to_rgb(row_pointers, width, height);
        *color_type = PNG_COLOR_TYPE_RGB;

    } else if (*color_type == PNG_COLOR_TYPE_RGB)
    {
        convert_rgb_to_gray(row_pointers, width, height);
        *color_type = PNG_COLOR_TYPE_GRAY;

    } else if (*color_type == PNG_COLOR_TYPE_PALETTE)
    {
        convert_palette_to_rgb(row_pointers, width, height, png_ptr, info_ptr);
        *color_type = PNG_COLOR_TYPE_RGB;
    }
}

int convert_png(const char *input_file, const char *output_file)
{
    png_structp png_ptr = NULL;
    png_infop info_ptr = NULL;
    png_bytep *row_pointers = NULL;
    png_uint_32 width, height;
    int color_type, bit_depth;

    if (read_png(input_file, &png_ptr, &info_ptr,
                 &row_pointers, &width, &height, &color_type, &bit_depth))
    {
        return 1;
    }

    convert_color(row_pointers, width, height, &color_type, png_ptr, info_ptr);

    if (write_png(output_file, row_pointers, width, height, bit_depth, color_type))
    {
        return 1;
    }

    for (int y = 0; y < height; y++)
    {
        free(row_pointers[y]);
    }

    free(row_pointers);
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);

    return 0;
}