#include "Actions.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);

        return 1;
    }

    FILE *input_file = fopen(argv[1], "r");

    if (input_file == NULL)
    {
        fprintf(stderr, "Error: Can't open the input file.\n");

        return 1;
    }

    FILE *output_file = fopen(argv[2], "w");

    if (output_file == NULL)
    {
        fprintf(stderr, "Error: Can't open the output file.\n");
        fclose(input_file);

        return 1;
    }

    int row, column;

    if (fscanf(input_file, "%d %d", &row, &column) != 2)
    {
        fprintf(stderr, "Error: Invalid input format.\n");
        fclose(input_file);
        fclose(output_file);

        return 1;
    }

    if (row != column)
    {
        fprintf(output_file, "no_solution\n");
        fclose(input_file);
        fclose(output_file);

        return 0;
    }

    int size = row;
    double *matrix = allocation_of_memory(size * size);
    double *inversed_matrix = allocation_of_memory(size * size);

    if (!matrix || !inversed_matrix)
    {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        fclose(input_file);
        fclose(output_file);
        free(matrix);
        free(inversed_matrix);

        return 1;
    }

    if (!read_the_file(input_file, matrix, size))
    {
        fprintf(stderr, "Error: Invalid input format.\n");
        fclose(input_file);
        fclose(output_file);
        free(matrix);
        free(inversed_matrix);

        return 1;
    }

    fclose(input_file);

    // Inversed matrix
    int result = reverse_the_matrix(matrix, inversed_matrix, size);

    if (result == 1)
    {
        fprintf(output_file, "%d %d\n", row, column);
        write_to_file(output_file, inversed_matrix, size);
    }
    else
    {
        fprintf(output_file, "no_solution\n");
    }

    fclose(output_file);
    free(inversed_matrix);
    free(matrix);

    return 0;
}