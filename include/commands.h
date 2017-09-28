#ifndef COMMANDS_H
#define COMMANDS_H

#include "global.h"


enum commands
{
    CMD_AUTHOR,
    CMD_BLOCK,
    CMD_BLOCKED,
    CMD_BROADCAST,
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
int identify_command(std::string &);

#endif