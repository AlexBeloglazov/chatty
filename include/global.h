#ifndef GLOBAL_H_
#define GLOBAL_H_

#define HOSTNAME_LEN 128
#define PATH_LEN 256

#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <map>
#include <algorithm>
#include <limits>
#include <netdb.h>
#include <sstream>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>

#define AUTHOR "abelogla"

#define BROADCAST_IP "255.255.255.255"
#define LOOKUP_IP "8.8.8.8"
#define LOOKUP_PORT 53

#define _RELAYED "RELAYED"
#define _RECEIVED "RECEIVED"

struct runtime_params
{
    bool is_server;
    bool is_logged;
    std::string hostname, ip_address, port;
};

#include "machine.h"
#include "log.h"
#include "helpers.h"
#include "protocol.h"
#include "commands.h"
#include "messages.h"

extern runtime_params *params;
extern std::map<std::string, Machine *> *ip2machine;

#endif
