#include <stdio.h>
#include "operation.h"

int main(int argc, char **argv)
{
    Operation *operations = NULL;

    if (parse_operations(argc-1, ++argv, &operations) != 0) {
        fprintf(stderr, "error while parsing operations\n");
        return 1;
    }

    int i;
    for (i = 0; i < argc-1; i++) {
        Operation operation = operations[i];
        if (execute_operation(operation) != 0) {
            fprintf(stderr, "error while executing operation");
            return 1;
        }
    }

    free_operations(&operations, argc-1);

    return 0;
}
