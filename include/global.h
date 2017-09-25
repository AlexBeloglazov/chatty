#ifndef GLOBAL_H_
#define GLOBAL_H_

#define HOSTNAME_LEN 128
#define PATH_LEN 256

#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <netdb.h>
#include <sstream>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>

#include "helpers.h"
#include "cmds.h"

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
