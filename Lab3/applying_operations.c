
#include "applying_operations.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int precedence(const char *op)
{
    if (strcmp(op, "**") == 0)
        return 4;

    if (strcmp(op, "~") == 0)
        return 3;

    if (strcmp(op, "*") == 0 || strcmp(op, "/") == 0 || strcmp(op, "%") == 0)
        return 2;

    if (strcmp(op, "+") == 0 || strcmp(op, "-") == 0)
        return 1;

    if (strcmp(op, "<<") == 0 || strcmp(op, ">>") == 0)
        return 0;

    if (strcmp(op, "&") == 0 || strcmp(op, "^") == 0 || strcmp(op, "|") == 0)
        return -1;

    return -2;
}

int apply_operator(const char *op, int left, int right)
{
    if (strcmp(op, "~") == 0)
        return ~right;

    if (strcmp(op, "-") == 0 && left == 0)
        return -right;

    if (strcmp(op, "<<") == 0)
    {
        if (right < 0 || right > 32)
            return 2;

        return left << right;
    }

    if (strcmp(op, ">>") == 0)
    {
        if (right < 0 || right > 32)
            return 2;

        return left >> right;
    }

    if (strcmp(op, "&") == 0)
        return left & right;

    if (strcmp(op, "^") == 0)
        return left ^ right;

    if (strcmp(op, "|") == 0)
        return left | right;

    if (strcmp(op, "+") == 0)
        return left + right;

    if (strcmp(op, "-") == 0)
        return left - right;

    if (strcmp(op, "*") == 0)
        return left * right;

    if (strcmp(op, "/") == 0)
    {
        if (right == 0)
            return 2;

        return left / right;
    }

    if (strcmp(op, "%") == 0)
    {
        if (right == 0)
            return 2;

        return left % right;
    }

    if (strcmp(op, "**") == 0)
    {
        if (right < 0)
            return 2;

        return (int)pow(left, right);
    }

    return 1;
}
