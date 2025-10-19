#ifndef OPEN_THE_FILE_H
#define OPEN_THE_FILE_H

#include <png.h>

int read_png(
        const char *input_file,
        png_structp *png_ptr,
        png_infop *info_ptr,
        png_bytep **row_pointers,
        png_uint_32 *width,
        png_uint_32 *height,
        int *color_type,
        int *bit_depth);

#endif	  // OPEN_THE_FILE_H