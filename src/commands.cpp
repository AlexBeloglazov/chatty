#include "../include/commands.h"

void cmd_author()
{
    std::stringstream out;
    out << "I, " << AUTHOR
        << ", have read and understood the course academic integrity policy.\n";
    print_success((char *)"AUTHOR", (char *)out.str().c_str(), 1);
}

void cmd_ip()
{
    print_success((char *)"IP", str2char(params->ip_address), 1);
}

int identify_command(std::string &cmd)
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