#include "write_to_the_file.h"

#include <png.h>
#include <stdio.h>

int write_png(
        const char *output_file,
        png_bytep *row_pointers,
        png_uint_32 width,
        png_uint_32 height,
        int bit_depth,
        int color_type)
{
    FILE *fp = fopen(output_file, "wb");

    if (!fp)
    {
        fprintf(stderr, "Error: Failed to open output file %s\n", output_file);

        return 1;
    }

    png_structp out_png_ptr =
            png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (!out_png_ptr)
    {
        fprintf(stderr, "Error: Failed to create PNG write structure\n");
        fclose(fp);

        return 1;
    }

    png_infop out_info_ptr = png_create_info_struct(out_png_ptr);

    if (!out_info_ptr)
    {
        fprintf(stderr, "Error: Failed to create PNG info structure\n");
        png_destroy_write_struct(&out_png_ptr, NULL);
        fclose(fp);

        return 1;
    }

    if (setjmp(png_jmpbuf(out_png_ptr)))
    {
        fprintf(stderr, "Error: Error during PNG write\n");
        png_destroy_write_struct(&out_png_ptr, &out_info_ptr);
        fclose(fp);

        return 1;
    }

    png_init_io(out_png_ptr, fp);
    png_set_IHDR(
            out_png_ptr,
            out_info_ptr,
            width, height,
            bit_depth,
            color_type,
            PNG_INTERLACE_NONE,
            PNG_COMPRESSION_TYPE_DEFAULT,
            PNG_FILTER_TYPE_DEFAULT);

    png_write_info(out_png_ptr, out_info_ptr);
    png_write_image(out_png_ptr, row_pointers);
    png_write_end(out_png_ptr, NULL);

    fclose(fp);
    png_destroy_write_struct(&out_png_ptr, &out_info_ptr);

    return 0;
}