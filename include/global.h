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
#include <netdb.h>
#include <sstream>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>

#include "prints.h"
#include "helpers.h"
#include "socket.h"
#include "commands.h"

#define AUTHOR "abelogla"
#define LOOKUP_IP "8.8.8.8"
#define LOOKUP_PORT 53
#define META_LENGTH 8

struct runtime_params
{
    bool is_server;
    bool is_logged;
    std::string hostname, ip_address, port;
};

class Machine
{
    int fd, port, sent, rcvd;
    bool is_logged;
    std::string ip, hostname;
    std::vector<Machine *> blocked;

    public:
      Machine(int f, int p, std::string i, std::string h) :
      fd(f), port(p), ip(i), hostname(h), is_logged(0), sent(0), rcvd(0) {};
};

extern runtime_params *params;

#endif
