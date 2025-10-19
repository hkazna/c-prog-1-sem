#include "color_to_color.h"

#include <png.h>
#include <stdlib.h>

void convert_palette_to_rgb(
        png_bytep *row_pointers,
        png_uint_32 width,
        png_uint_32 height,
        png_structp png_ptr,
        png_infop info_ptr)
{
    int palette_size;
    png_colorp palette_data;
    png_get_PLTE(png_ptr, info_ptr, &palette_data, &palette_size);

    for (int y = 0; y < height; y++)
    {
        png_bytep old_row = row_pointers[y];
        png_bytep rgb_row = malloc(3 * width);

        for (int x = 0; x < width; x++)
        {
            png_byte color_index = old_row[x];
            rgb_row[3 * x] = palette_data[color_index].red;
            rgb_row[3 * x + 1] = palette_data[color_index].green;
            rgb_row[3 * x + 2] = palette_data[color_index].blue;
        }

        free(old_row);
        row_pointers[y] = rgb_row;
    }
}

void convert_gray_to_rgb(
        png_bytep *row_pointers,
        png_uint_32 width,
        png_uint_32 height)
{
    for (int y = 0; y < height; y++)
    {
        png_bytep original_row = row_pointers[y];
        png_bytep rgb_row = malloc(3 * width);

        for (int x = 0; x < width; x++)
        {
            png_byte gray_value = original_row[x];
            rgb_row[3 * x] = gray_value;
            rgb_row[3 * x + 1] = gray_value;
            rgb_row[3 * x + 2] = gray_value;
        }

        free(original_row);
        row_pointers[y] = rgb_row;
    }
}

void convert_rgb_to_gray(
        png_bytep *row_pointers,
        png_uint_32 width,
        png_uint_32 height)
{
    for (int y = 0; y < height; y++)
    {
        png_bytep original_row = row_pointers[y];
        png_bytep gray_row = malloc(width);

        for (int x = 0; x < width; x++)
        {
            png_byte red = original_row[3 * x];
            png_byte green = original_row[3 * x + 1];
            png_byte blue = original_row[3 * x + 2];

            gray_row[x] = (red + green + blue) / 3;
        }

        free(original_row);
        row_pointers[y] = gray_row;
    }
}