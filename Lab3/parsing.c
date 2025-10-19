#include "parsing.h"

#include "is_unary_operation.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

int parse_expression(const char *expression, ParsedExpression *parsed)
{
    parsed->token_count = 0;
    const char *current = expression;
    int parentheses_balance = 0;
    bool might_last_was_operator = true;

    while (*current != '\0')
    {
        while (isspace(*current))
            current++;

        if (isdigit(*current) ||
        (*current == '-' && isdigit(*(current + 1)) && might_last_was_operator))
        {
            int len = 0;

            if (*current == '-')
                parsed->tokens[parsed->token_count][len++] = *current++;

            while (isdigit(*current))
                parsed->tokens[parsed->token_count][len++] = *current++;

            parsed->tokens[parsed->token_count][len] = '\0';
            parsed->token_count++;
            might_last_was_operator = false;

        } else if (*current == '(')
        {
            parentheses_balance++;
            parsed->tokens[parsed->token_count][0] = *current++;
            parsed->tokens[parsed->token_count][1] = '\0';
            parsed->token_count++;
            might_last_was_operator = true;

        } else if (*current == ')')
        {
            parentheses_balance--;

            if (parentheses_balance < 0)
            {
                return 3;
            }

            parsed->tokens[parsed->token_count][0] = *current++;
            parsed->tokens[parsed->token_count][1] = '\0';
            parsed->token_count++;
            might_last_was_operator = false;

        } else if (strncmp(current, "**", 2) == 0)
        {

            parsed->tokens[parsed->token_count][0] = '*';
            parsed->tokens[parsed->token_count][1] = '*';
            parsed->tokens[parsed->token_count][2] = '\0';
            parsed->token_count++;
            current += 2;
            might_last_was_operator = true;

        } else if (strchr("+-*/%|&^<>", *current))
        {
            if (might_last_was_operator && !is_unary_operator(current))
            {
                return 3;
            }

            if ((*current == '<' &&
            *(current + 1) == '<') || (*current == '>' && *(current + 1) == '>'))
            {
                parsed->tokens[parsed->token_count][0] = *current++;
                parsed->tokens[parsed->token_count][1] = *current++;
                parsed->tokens[parsed->token_count][2] = '\0';

            } else
            {
                parsed->tokens[parsed->token_count][0] = *current++;
                parsed->tokens[parsed->token_count][1] = '\0';
            }

            parsed->token_count++;
            might_last_was_operator = true;

        } else
        {
            return 1;
        }
    }

    if (parentheses_balance != 0)
        return 3;

    if (parsed->token_count >= MAX_TOKENS)
    {
        return 4;
    }

    return 0;
}