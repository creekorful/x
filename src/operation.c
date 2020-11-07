#include "operation.h"

int operation_parses(int argc, char **argv, Operation **operations)
{
    *operations = malloc(argc * sizeof **operations);

    int i;
    for (i = 0; i < argc; i++) {
        Operation operation;
        if (operation_parse(argv[i], &operation) != 0) {
            return 1;
        }

        (*operations)[i] = operation;
    }

    return 0;
}

int operation_parse(char *line, Operation *operation)
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

int operation_free(Operation *operation)
{
    free(operation->package);
    return 0;
}

int operation_execute(Operation operation)
{
    char cmd[255] = "";
    // On linux update local cache first before everything
#if __linux__
    sprintf(cmd, "%s update", APT_PATH);
    system(cmd);
#endif
    switch (operation.opType) {
        case Install:
#if __APPLE__
            sprintf(cmd, "%s install %s", BREW_PATH, operation.package);
#elif __linux__
            sprintf(cmd, "%s install -y %s", APT_PATH, operation.package);
#elif _WIN32
            sprintf(cmd, "%s install -y %s", CHOCO_PATH, operation.package);
#endif
            break;
        case Update:
#if __APPLE__
            if (operation.package == NULL)
                sprintf(cmd, "%s upgrade", BREW_PATH);
            else
                sprintf(cmd, "%s upgrade %s", BREW_PATH, operation.package);
#elif __linux__
            if (operation.package == NULL)
                sprintf(cmd, "%s upgrade -y", APT_PATH);
            else
                sprintf(cmd, "%s --only-upgrade install %s", APT_PATH, operation.package);
#elif _WIN32
            if (operation.package == NULL)
                sprintf(cmd, "%s upgrade -y all", CHOCO_PATH);
            else
                sprintf(cmd, "%s upgrade -y %s", CHOCO_PATH, operation.package);
#endif
            break;
        case Remove:
#if __APPLE__
            sprintf(cmd, "%s remove %s", BREW_PATH, operation.package);
#elif __linux__
            sprintf(cmd, "%s remove -y %s", APT_PATH, operation.package);
#elif _WIN32
            sprintf(cmd, "%s uninstall %s", CHOCO_PATH, operation.package);
#endif
            break;
    }

    return system(cmd);
}
