#ifndef X_OPERATION_H
#define X_OPERATION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum OperationType
{
    Install,
    Update,
    Remove
} typedef OperationType;

struct Operation
{
    OperationType opType;
    char *package;
} typedef Operation;

int parse_operations(int argc, char **argv, Operation **operations);

int parse_operation(const char *line, Operation *operation);

int free_operation(Operation *operation);

int free_operations(Operation **operations, int count);

int execute_operation(Operation operation);

#endif //X_OPERATION_H
