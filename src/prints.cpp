#include "../include/prints.h"

void print_success(char *cmd, char *outcome, bool p_out)
{
    printf("[%s:SUCCESS]\n", cmd);
    if (p_out)
        printf("%s:%s", cmd, outcome);
    printf("[%s:END]\n", cmd);
}

void print_success(char *cmd, char *outcome)
{
    printf("[%s:SUCCESS]\n", cmd);
    printf("%s", outcome);
    printf("[%s:END]\n", cmd);
}

void print_error(char *cmd)
{
    printf("[%s:ERROR]\n", cmd);
    printf("[%s:END]\n", cmd);
}

void print_usage(const char *exec)
{
    std::cout << "\nUSAGE: " << exec << " {c|s} <port>\n\n"
              << "Options:\n"
              << "\tc\tExecute in the client mode;\n"
              << "\ts\tExecute in the server mode;\n"
              << "\t<port>\tPort number to listen for connections on;\n\n";
    exit(1);
};