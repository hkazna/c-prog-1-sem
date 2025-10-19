#ifndef COLOR_TO_COLOR_H
#define COLOR_TO_COLOR_H
#include <png.h>

void convert_palette_to_rgb(
        png_bytep *row_pointers,
        png_uint_32 width,
        png_uint_32 height,
        png_structp png_ptr,
        png_infop info_ptr);

void convert_gray_to_rgb(
        png_bytep *row_pointers,
        png_uint_32 width,
        png_uint_32 height);

void convert_rgb_to_gray(
        png_bytep *row_pointers,
        png_uint_32 width,
        png_uint_32 height);

#endif	  // COLOR_TO_COLOR_H