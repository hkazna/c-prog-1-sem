#ifndef ACTIONS_H
#define ACTIONS_H

#include <stddef.h>
#include <stdio.h>

double *allocation_of_memory(int size);

int read_the_file(FILE *file, double *matrix, int size);

void write_to_file(FILE *file, double *matrix, int size);

int reverse_the_matrix(double *matrix, double *inverse, int size);

#endif	  // ACTIONS_H
