#ifndef X_OPERATION_H
#define X_OPERATION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define APT_PATH "/usr/bin/apt"
#define BREW_PATH "/usr/local/bin/brew"

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

int operation_parses(int argc, char **argv, Operation **operations);

int operation_parse(char *line, Operation *operation);

int operation_free(Operation *operation);

int operation_execute(Operation operation);

#endif //X_OPERATION_H
