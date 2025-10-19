#include "Actions.h"

#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#define EPSILON 1e-9

double *allocation_of_memory(int size)
{
    double *matrix = (double *)malloc(size * sizeof(double));

    return matrix;
}

int read_the_file(FILE *file, double *matrix, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (fscanf(file, "%lf", &matrix[i * size + j]) != 1)
            {
                return 0;
            }
        }
    }

    return 1;
}

void write_to_file(FILE *file, double *matrix, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            fprintf(file, "%g ", matrix[i * size + j]);
        }

        fprintf(file, "\n");
    }
}

int reverse_the_matrix(double *matrix, double *inverse, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            inverse[i * size + j] = (i == j) ? 1.0 : 0.0;
        }
    }

    for (int i = 0; i < size; i++)
    {
        int max_among_rows = i;

        for (int k = i + 1; k < size; k++)
        {
            if (fabs(matrix[k * size + i]) > fabs(matrix[max_among_rows * size + i]))
            {
                max_among_rows = k;
            }
        }

        if (fabs(matrix[max_among_rows * size + i]) < EPSILON)
        {
            return 0;
        }

        if (i != max_among_rows)
        {
            for (int k = 0; k < size; k++)
            {
                double temp = matrix[i * size + k];
                matrix[i * size + k] = matrix[max_among_rows * size + k];
                matrix[max_among_rows * size + k] = temp;

                temp = inverse[i * size + k];
                inverse[i * size + k] = inverse[max_among_rows * size + k];
                inverse[max_among_rows * size + k] = temp;
            }
        }

        double pivot = matrix[i * size + i];

        for (int j = 0; j < size; j++)
        {
            matrix[i * size + j] /= pivot;
            inverse[i * size + j] /= pivot;
        }

        for (int k = 0; k < size; k++)
        {
            if (k != i)
            {
                double factor = matrix[k * size + i];

                for (int j = 0; j < size; j++)
                {
                    matrix[k * size + j] -= factor * matrix[i * size + j];
                    inverse[k * size + j] -= factor * inverse[i * size + j];
                }
            }
        }
    }

    return 1;
}