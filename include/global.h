#ifndef GLOBAL_H_
#define GLOBAL_H_

#define HOSTNAME_LEN 128
#define PATH_LEN 256

#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <vector>
#include <sstream>
#include "../include/helpers.h"
#include "../include/cmds.h"

#define AUTHOR "abelogla"
#define LOOKUP_IP "8.8.8.8"
#define LOOKUP_PORT 53

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

struct runtime_params
{
    bool is_server;
    bool is_logged;
    std::string hostname, ip_address, port;
};

struct statistics {

};

struct list {

};

extern runtime_params *params;

#endif
