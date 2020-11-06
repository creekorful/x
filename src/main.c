#include <stdio.h>
#include "operation.h"

int main(int argc, char **argv)
{
    Operation *operations = NULL;

    if (operation_parses(argc - 1, ++argv, &operations) != 0) {
        fprintf(stderr, "error while parsing operations\n");
        return 1;
    }

    int i;
    for (i = 0; i < argc - 1; i++) {
        Operation operation = operations[i];
        if (operation_execute(operation) != 0) {
            fprintf(stderr, "error while executing operation\n");
            return 1;
        }

        operation_free(&operation);
    }
    free(operations);

    return 0;
}
