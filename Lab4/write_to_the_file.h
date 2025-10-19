#ifndef WRITE_TO_THE_FILE_H
#define WRITE_TO_THE_FILE_H
#include <png.h>

int write_png(
        const char *output_file,
        png_bytep *row_pointers,
        png_uint_32 width,
        png_uint_32 height,
        int bit_depth,
        int color_type);

#endif	  // WRITE_TO_THE_FILE_H