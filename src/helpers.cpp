#include "../include/helpers.h"

std::vector<std::string> *read_line()
{
    std::vector<std::string> *out = new std::vector<std::string>();
    std::string line, component;
    std::getline(std::cin, line);
    std::stringstream stream(line);
    while(stream >> component) {
        out->push_back(component);
    }
    if (out->empty()) out->push_back(std::string());
    return out;
}

int identify_cmd(std::string cmd)
{
    commands out;
    if (cmd == "AUTHOR") 
        out = CMD_AUTHOR;
    else if (cmd == "BLOCK")
        out = CMD_BLOCK;
    else if (cmd == "BLOCKED")
        out = CMD_BLOCKED;
    else if (cmd == "BROADCAST")
        out = CMD_BROADCAST;
    else if (cmd == "EXIT")
        out = CMD_EXIT;
    else if (cmd == "IP")
        out = CMD_IP;
    else if (cmd == "LIST")
        out = CMD_LIST;
    else if (cmd == "LOGIN")
        out = CMD_LOGIN;
    else if (cmd == "LOGOUT")
        out = CMD_LOGOUT;
    else if (cmd == "PORT")
        out = CMD_PORT;
    else if (cmd == "REFRESH")
        out = CMD_REFRESH;
    else if (cmd == "SEND")
        out = CMD_SEND;
    else if (cmd == "STATISTICS")
        out = CMD_STATISTICS;
    else if (cmd == "UNBLOCK")
        out = CMD_UNBLOCK;
    else
        out = CMD_UNKNOWN;
    return out;
}

char *str2char(std::string line) {
    return (char *) (line + "\n").c_str();
}

void print_success(char *command, char *outcome, bool print_outcome)
{
    printf("[%s:SUCCESS]\n", command);
    if (print_outcome)
        printf("%s:%s", command, outcome);
    printf("[%s:END]\n", command);
}

void print_error(char *command)
{
    printf("[%s:ERROR]\n", command);
    printf("[%s:END]\n", command);
}