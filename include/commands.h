#ifndef COMMANDS_H
#define COMMANDS_H

#include "global.h"

#define _RELAYED "RELAYED"

#define _CMD_AUTHOR "AUTHOR"
#define _CMD_BLOCK "BLOCK"
#define _CMD_BLOCKED "BLOCKED"
#define _CMD_EXIT "EXIT"
#define _CMD_IP "IP"
#define _CMD_LIST "LIST"
#define _CMD_LOGIN "LOGIN"
#define _CMD_LOGOUT "LOGOUT"
#define _CMD_PORT "PORT"
#define _CMD_REFRESH "REFRESH"
#define _CMD_SEND "SEND"
#define _CMD_STATISTICS "STATISTICS"
#define _CMD_UNBLOCK "UNBLOCK"

enum commands
{
    CMD_AUTHOR,
    CMD_BLOCK,
    CMD_BLOCKED,
    CMD_EXIT,
    CMD_IP,
    CMD_LIST,
    CMD_LOGIN,
    CMD_LOGOUT,
    CMD_PORT,
    CMD_REFRESH,
    CMD_SEND,
    CMD_STATISTICS,
    CMD_UNBLOCK,
    CMD_UNKNOWN
};

void cmd_author();
void cmd_ip();
void cmd_list(std::vector<Machine *> *);
int identify_cmd(std::string &);

#endif