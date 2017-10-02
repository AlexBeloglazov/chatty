#include "../include/log.h"

void print_success(const char *cmd, char *outcome, bool p_out)
{
    printf("[%s:SUCCESS]\n", cmd);
    if (p_out)
        printf("%s:%s", cmd, outcome);
    printf("[%s:END]\n", cmd);
}

void print_success(const char *cmd, char *outcome)
{
    printf("[%s:SUCCESS]\n", cmd);
    printf("%s", outcome);
    printf("[%s:END]\n", cmd);
}

void print_error(const char *cmd)
{
    printf("[%s:ERROR]\n", cmd);
    printf("[%s:END]\n", cmd);
}
