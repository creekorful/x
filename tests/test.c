#include "../src/operation.h"

int test_add_vim()
{
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

    return 0;
}

int test_remove_neofetch()
{
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

    return 0;
}

int test_update_gcc()
{
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

    return 0;
}

int test_update_all_packages()
{
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

    return 0;
}

int test_operation_parses()
{
    char **args = malloc(3 * sizeof(char *));
    args[0] = "+vim";
    args[1] = "-neofetch";
    args[2] = "^gcc";

    Operation *operations;

    if (operation_parses(3, args, &operations) != 0) {
        printf("failed to parse the operations\n");
        return 1;
    }

    if (operations[0].opType != Install) {
        printf("operations[0]: wrong operation type\n");
        return 1;
    }
    if (strcmp(operations[0].package, "vim") != 0) {
        printf("operations[0]: wrong package name\n");
        return 1;
    }

    if (operations[1].opType != Remove) {
        printf("operations[1]: wrong operation type\n");
        return 1;
    }
    if (strcmp(operations[1].package, "neofetch") != 0) {
        printf("operations[1]: wrong package name\n");
        return 1;
    }

    if (operations[2].opType != Update) {
        printf("operations[0]: wrong operation type\n");
        return 1;
    }
    if (strcmp(operations[2].package, "gcc") != 0) {
        printf("operations[0]: wrong package name\n");
        return 1;
    }

    return 0;
}

int main()
{
    printf("--- executing tests\n");

    printf("--- executing test_add_vim\n");
    if (test_add_vim() != 0) {
        printf("--- failed test_add_vim\n");
        return 1;
    }
    printf("--- passed test_add_vim\n");
    printf("--- executing test_remove_neofetch\n");
    if (test_remove_neofetch() != 0) {
        printf("--- failed test_remove_neofetch\n");
        return 1;
    }
    printf("--- passed test_remove_neofetch\n");
    printf("--- executing test_update_gcc\n");
    if (test_update_gcc() != 0) {
        printf("--- failed test_update_gcc\n");
        return 1;
    }
    printf("--- passed test_update_gcc\n");
    printf("--- executing test_update_all_packages\n");
    if (test_update_all_packages() != 0) {
        printf("--- failed test_update_all_packages\n");
        return 1;
    }
    printf("--- passed test_update_all_packages\n");
    printf("--- executing test_operation_parses\n");
    if (test_operation_parses() != 0) {
        printf("--- failed test_operation_parses\n");
        return 1;
    }
    printf("--- passed test_operation_parses\n");

    printf("--- passed tests\n");

    return 0;
}