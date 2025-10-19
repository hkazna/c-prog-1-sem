#ifndef APPLYING_OPERATIONS_H
#define APPLYING_OPERATIONS_H

int precedence(const char *op);

int apply_operator(const char *op, int left, int right);

#endif	  // APPLYING_OPERATIONS_H