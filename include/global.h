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
#include <netdb.h>
#include <sstream>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>

#define AUTHOR "abelogla"
#define LOOKUP_IP "8.8.8.8"
#define LOOKUP_PORT 53

struct runtime_params
{
    bool is_server;
    bool is_logged;
    std::string hostname, ip_address, port;
};

class Machine
{
    public:
      int fd, port, sent, rcvd;
      bool is_logged;
      std::string ip, hostname;
      std::vector<Machine *> blocked;
      
      Machine(int f, int p, std::string i, std::string h) :
        fd(f), port(p), ip(i), hostname(h), is_logged(0), sent(0), rcvd(0){};
};

#include "log.h"
#include "helpers.h"
#include "protocol.h"
#include "commands.h"
#include "messages.h"

extern runtime_params *params;
extern std::map<std::string, Machine*> *ip2machine;

#endif
