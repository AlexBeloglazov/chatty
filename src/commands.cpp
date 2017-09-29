#include "../include/commands.h"

void cmd_author()
{
    std::stringstream out;
    out << "I, " << AUTHOR
        << ", have read and understood the course academic integrity policy.\n";
    print_success(_CMD_AUTHOR, (char *)out.str().c_str(), 1);
}

void cmd_ip()
{
    print_success(_CMD_IP, str2char(params->ip_address), 1);
}

int identify_cmd(std::string &cmd)
{
    commands out;
    if (cmd == _CMD_AUTHOR)
        out = CMD_AUTHOR;
    else if (cmd == _CMD_BLOCK)
        out = CMD_BLOCK;
    else if (cmd == _CMD_BLOCKED)
        out = CMD_BLOCKED;
    else if (cmd == _CMD_BROADCAST)
        out = CMD_BROADCAST;
    else if (cmd == _CMD_EXIT)
        out = CMD_EXIT;
    else if (cmd == _CMD_IP)
        out = CMD_IP;
    else if (cmd == _CMD_LIST)
        out = CMD_LIST;
    else if (cmd == _CMD_LOGIN)
        out = CMD_LOGIN;
    else if (cmd == _CMD_LOGOUT)
        out = CMD_LOGOUT;
    else if (cmd == _CMD_PORT)
        out = CMD_PORT;
    else if (cmd == _CMD_REFRESH)
        out = CMD_REFRESH;
    else if (cmd == _CMD_SEND)
        out = CMD_SEND;
    else if (cmd == _CMD_STATISTICS)
        out = CMD_STATISTICS;
    else if (cmd == _CMD_UNBLOCK)
        out = CMD_UNBLOCK;
    else
        out = CMD_UNKNOWN;
    return out;
}