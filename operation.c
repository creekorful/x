#include "operation.h"

int parse_operations(int argc, char **argv, Operation **operations)
{
    *operations = malloc(argc * sizeof **operations);

    int i;
    for (i = 0; i < argc; i++) {
        Operation operation;
        if (parse_operation(argv[i], &operation) != 0) {
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

    operation->package = malloc(strlen(line - 1));
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
    for (i = 0; i < count; i++) {
        if (free_operation(operations[i]) != 0) {
            ret = 1;
        }
    }

    return ret;
}

int execute_operation(const Operation operation)
{
    // On linux update local cache first before everything
#if __linux__
    system("apt update");
#endif

    char cmd[255] = "";
    switch (operation.opType) {
        case Install:
#if __APPLE__
            sprintf(cmd, "brew install %s", operation.package);
#elif __linux__
            sprintf(cmd, "apt install -y %s", operation.package);
#endif
            break;
        case Update:
#if __APPLE__
            if (operation.package == NULL) {
                sprintf(cmd, "brew upgrade");
            } else {
                sprintf(cmd, "brew upgrade %s", operation.package);
            }
#elif __linux__
            if (operation.package == NULL) {
                sprintf(cmd, "apt upgrade -y");
            } else {
                sprintf(cmd, "apt --only-upgrade install %s", operation.package);
            }
#endif
            break;
        case Remove:
#if __APPLE__
            sprintf(cmd, "brew remove %s", operation.package);
#elif __linux__
            sprintf(cmd, "apt remove -y %s", operation.package);
#endif
            break;
    }

    return system(cmd);
}
