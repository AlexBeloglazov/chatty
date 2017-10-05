#include "../include/commands.h"

void cmd_author()
{
    std::stringstream out;
    out << "I, " << AUTHOR
        << ", have read and understood the course academic integrity policy.\n";
    print_success(_CMD_AUTHOR, (char *)out.str().c_str());
}

void cmd_ip()
{
    std::string ip = params->ip_address + "\n";
    print_success(_CMD_IP, &ip[0], 1);
}

void cmd_port()
{
    std::string port = params->port + "\n";
    print_success(_CMD_PORT, &port[0], 1);
}

void cmd_list(std::vector<Machine*> *ml) {
    std::stringstream stream;
    std::string out;
    std::vector<Machine*>::iterator it;
    int index = 0;
    ml_sort_by_port(ml);
    for (it = ml->begin(); it != ml->end(); ++it) {
        if (!(*it)->is_logged) {
            continue;
        }
        stream << std::left << std::setw(5) << ++index
            << std::setw(35) << (*it)->hostname
            << std::setw(20) << (*it)->ip
            << std::setw(8) << (*it)->port << "\n";
        out += stream.str();
        stream.clear();
        stream.str(std::string());
    }
    print_success(_CMD_LIST, &out[0]);
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