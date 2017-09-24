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

struct runtime_params
{
    bool is_server;
    bool is_logged;
    std::string hostname, ip_address, port;
};

extern runtime_params *params;

#endif
