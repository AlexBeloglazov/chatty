#ifndef CMDS_H
#define CMDS_H

#include "global.h"
#include "helpers.h"


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

struct statistics
{
};

struct list
{
};

void cmd_author();
void cmd_ip();

#endif