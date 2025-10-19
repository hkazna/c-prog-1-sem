#include "open_the_file.h"

#include <png.h>
#include <stdio.h>
#include <stdlib.h>

int read_png(
        const char *input_file,
        png_structp *png_ptr,
        png_infop *info_ptr,
        png_bytep **row_pointers,
        png_uint_32 *width,
        png_uint_32 *height,
        int *color_type,
        int *bit_depth)
{
    FILE *fp = fopen(input_file, "rb");

    if (!fp)
    {
        fprintf(stderr, "Error: Failed to open input file %s\n", input_file);

        return 1;
    }

    unsigned char header[8];

    if (fread(header, 1, 8, fp) != 8 ||
    png_sig_cmp(header, 0, 8))
    {
        fprintf(stderr, "Error: File is not a valid PNG\n");
        fclose(fp);

        return 1;
    }

    *png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (!*png_ptr)
    {
        fprintf(stderr, "Error: Failed to create PNG read structure\n");
        fclose(fp);

        return 1;
    }

    *info_ptr = png_create_info_struct(*png_ptr);

    if (!*info_ptr)
    {
        fprintf(stderr, "Error: Failed to create PNG info structure\n");
        png_destroy_read_struct(png_ptr, NULL, NULL);
        fclose(fp);

        return 1;
    }

    if (setjmp(png_jmpbuf(*png_ptr)))
    {
        fprintf(stderr, "Error: Error during PNG read\n");
        png_destroy_read_struct(png_ptr, info_ptr, NULL);
        fclose(fp);

        return 1;
    }

    png_init_io(*png_ptr, fp);
    png_set_sig_bytes(*png_ptr, 8);
    png_read_info(*png_ptr, *info_ptr);

    *width = png_get_image_width(*png_ptr, *info_ptr);
    *height = png_get_image_height(*png_ptr, *info_ptr);
    *color_type = png_get_color_type(*png_ptr, *info_ptr);
    *bit_depth = png_get_bit_depth(*png_ptr, *info_ptr);

    if (*bit_depth != 8)
    {
        fprintf(stderr, "Error: Only 8-bit images are supported\n");
        png_destroy_read_struct(png_ptr, info_ptr, NULL);
        fclose(fp);

        return 1;
    }

    if (*color_type != PNG_COLOR_TYPE_GRAY)
    {
        if (*color_type != PNG_COLOR_TYPE_RGB)
        {
            if (*color_type != PNG_COLOR_TYPE_PALETTE)
            {
                fprintf(stderr,
                        "Error: Unsupported color type (only GRAY, RGB, or PALETTE allowed)\n");
                png_destroy_read_struct(png_ptr, info_ptr, NULL);
                fclose(fp);

                return 1;
            }
        }
    }

    *row_pointers = (png_bytep *)malloc(sizeof(png_bytep) * (*height));

    for (int y = 0; y < *height; y++)
    {
        (*row_pointers)[y] = (png_byte *)malloc(png_get_rowbytes(*png_ptr, *info_ptr));
    }

    png_read_image(*png_ptr, *row_pointers);
    fclose(fp);

    return 0;
}