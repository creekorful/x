#include "operation.h"

int parse_operations(int argc, char **argv, Operation **operations)
{
    *operations = malloc(argc * sizeof **operations);

    int i;
    for (i = 0; i < argc; i++) {
        Operation operation;
        if (parse_operation(argv[i], &operation) != 0) {
            fprintf(stderr, "error while parsing operation `%s`\n", argv[i]);
            return 1;
        }

        (*operations)[i] = operation;
    }

    return 0;
}

int parse_operation(const char *line, Operation *operation)
{
    // Update all packages
    if (strlen(line) == 1 && line[0] == '^') {
        operation->opType = Update;
        operation->package = NULL;
        return 0;
    }

    char op = line[0];
    switch (op) {
        case '+':
            operation->opType = Install;
            break;
        case '-':
            operation->opType = Remove;
            break;
        case '^':
            operation->opType = Update;
            break;
        default:
            return 1;
    }

    operation->package = malloc(strlen(line-1));
    strcpy(operation->package, ++line);

    return 0;
}

int free_operation(Operation *operation)
{
    return 0;
}

int free_operations(Operation **operations, int count)
{
    int ret = 0;
    int i;
    for (i = 0; i < count; i++)
    {
        if (free_operation(operations[i]) != 0) {
            ret = 1;
        }
    }

    return ret;
}
