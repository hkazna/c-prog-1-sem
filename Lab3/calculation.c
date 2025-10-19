#include "calculation.h"

#include "applying_operations.h"
#include "is_unary_operation.h"
#include "parsing.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int calculate_expression(const ParsedExpression *parsed, int *result)
{
    int values[MAX_TOKENS];
    char operators[MAX_TOKENS][32];
    int value_top = -1;
    int operator_top = -1;

    for (int i = 0; i < parsed->token_count; i++)
    {
        if (isdigit(parsed->tokens[i][0]) ||
        (parsed->tokens[i][0] == '-' && isdigit(parsed->tokens[i][1])))
        {
            values[++value_top] = atoi(parsed->tokens[i]);
        } else if (is_unary_operator(parsed->tokens[i]))
        {
            if (value_top < 0)
            {
                return 3;
            }

            if (strcmp(parsed->tokens[i], "~") == 0)
            {
                values[value_top] = ~values[value_top];
            } else if (strcmp(parsed->tokens[i], "-") == 0)
            {
                values[value_top] = -values[value_top];
            }
        } else
        {
            while (operator_top >= 0 &&
            precedence(operators[operator_top]) >= precedence(parsed->tokens[i]))
            {
                if (value_top < 1)
                {
                    return 3;
                }

                int right = values[value_top--];
                int left = values[value_top--];
                const char *op = operators[operator_top--];
                int op_result = apply_operator(op, left, right);

                if (op_result == 2)
                    return 2;

                values[++value_top] = op_result;
            }

            if (operator_top >= MAX_TOKENS - 1)
            {
                return 4;
            }

            strcpy(operators[++operator_top], parsed->tokens[i]);
        }
    }

    while (operator_top >= 0)
    {
        if (value_top < 1)
        {
            return 3;
        }

        int right = values[value_top--];
        int left = values[value_top--];
        const char *op = operators[operator_top--];
        int op_result = apply_operator(op, left, right);

        if (op_result == 2)
            return 2;

        values[++value_top] = op_result;
    }

    if (value_top != 0)
    {
        return 3;
    }

    *result = values[value_top];

    return 0;
}