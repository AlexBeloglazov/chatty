#ifndef GLOBAL_H_
#define GLOBAL_H_

#include <vector>
#include <iostream>

#define HOSTNAME_LEN 128
#define PATH_LEN 256


#define USER_UBIT "abelogla"

struct runtime_config {
    bool is_server;
    std::string ip_address, port;
};


void parse_params(int, char *, runtime_config *);
void server(runtime_config *);
void client(runtime_config *);

#endif
