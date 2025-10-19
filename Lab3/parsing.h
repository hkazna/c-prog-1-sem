#ifndef PARSER_H
#define PARSER_H
#define MAX_TOKENS 1024

#include <stdbool.h>

typedef struct
{
    char tokens[MAX_TOKENS][32];
    int token_count;
} ParsedExpression;

int parse_expression(const char *expression, ParsedExpression *parsed);

#endif	  // PARSER_H