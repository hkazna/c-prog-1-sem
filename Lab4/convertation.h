#ifndef CONVERTATION_H
#define CONVERTATION_H

#include <png.h>

void convert_color(
        png_bytep *row_pointers,
        png_uint_32 width,
        png_uint_32 height,
        int *color_type,
        png_structp png_ptr,
        png_infop info_ptr);

int convert_png(const char *input_file, const char *output_file);

#endif	  // CONVERTATION_H