#include "is_unary_operation.h"

#include <stdbool.h>
#include <string.h>

bool is_unary_operator(const char *token)
{
    return (strcmp(token, "~") == 0 || strcmp(token, "-") == 0);
}