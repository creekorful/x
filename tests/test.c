#include "../src/operation.h"

int test_add_vim()
{
    printf("--- executing test_add_vim\n");

    char *line = "+vim";

    Operation operation;
    if (operation_parse(line, &operation) != 0) {
        printf("failed to parse the operation\n");
        return 1;
    }

    if (operation.opType != Install) {
        printf("wrong operation type");
        return 1;
    }
    if (strcmp(operation.package, "vim") != 0) {
        printf("wrong package");
        return 1;
    }

    printf("--- passed test_add_vim\n");

    return 0;
}

int test_remove_neofetch()
{
    printf("--- executing test_remove_neofetch\n");

    char *line = "-neofetch";

    Operation operation;
    if (operation_parse(line, &operation) != 0) {
        printf("failed to parse the operation\n");
        return 1;
    }

    if (operation.opType != Remove) {
        printf("wrong operation type");
        return 1;
    }
    if (strcmp(operation.package, "neofetch") != 0) {
        printf("wrong package");
        return 1;
    }

    printf("--- passed test_remove_neofetch\n");

    return 0;
}

int test_update_gcc()
{
    printf("--- executing test_update_gcc\n");

    char *line = "^gcc";

    Operation operation;
    if (operation_parse(line, &operation) != 0) {
        printf("failed to parse the operation\n");
        return 1;
    }

    if (operation.opType != Update) {
        printf("wrong operation type");
        return 1;
    }
    if (strcmp(operation.package, "gcc") != 0) {
        printf("wrong package");
        return 1;
    }

    printf("--- passed test_update_gcc\n");

    return 0;
}

int test_update_all_packages()
{
    printf("--- executing test_update_all_packages\n");

    char *line = "^";

    Operation operation;
    if (operation_parse(line, &operation) != 0) {
        printf("failed to parse the operation\n");
        return 1;
    }

    if (operation.opType != Update) {
        printf("wrong operation type");
        return 1;
    }
    if (operation.package != NULL) {
        printf("wrong package");
        return 1;
    }

    printf("--- passed test_update_all_packages\n");

    return 0;
}

int main()
{
    printf("--- executing tests\n");

    if (test_add_vim() != 0) {
        return 1;
    }
    if (test_remove_neofetch() != 0) {
        return 1;
    }
    if (test_update_gcc() != 0) {
        return 1;
    }
    if (test_update_all_packages() != 0) {
        return 1;
    }

    printf("--- passed tests\n");

    return 0;
}