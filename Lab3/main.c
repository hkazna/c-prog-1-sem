#include "calculation.h"
#include "parsing.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s \"expression\".\n", argv[0]);

        return 4;
    }

    const char *expression = argv[1];
    ParsedExpression parsed;
    int parse_status = parse_expression(expression, &parsed);

    if (parse_status != 0)
    {
        switch (parse_status)
        {
            case 1:
                fprintf(stderr, "Error: Unsupported operation.\n");
                break;
            case 2:
                fprintf(stderr, "Error: Division by zero or other calculation error.\n");
                break;
            case 3:
                fprintf(stderr, "Error: Unable to parse expression.\n");
                break;
            default:
                fprintf(stderr, "Error: Unknown error during parsing.\n");
        }

        return parse_status;
    }

    int result;
    int calc_status = calculate_expression(&parsed, &result);

    if (calc_status != 0)
    {
        switch (calc_status)
        {
            case 1:
                fprintf(stderr, "Error: Unsupported operation during calculation.\n");
                break;
            case 2:
                fprintf(stderr, "Error: Division by zero or other calculation error.\n");
                break;
            case 3:
                fprintf(stderr, "Error: Unable to parse expression during calculation.\n");
                break;
            default:
                fprintf(stderr, "Error: Unknown error during calculation.\n");
        }

        return calc_status;
    }

    printf("%d\n", result);

    return 0;
}