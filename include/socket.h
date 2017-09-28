#ifndef _SOCKET_H_
#define _SOCKET_H_

#include "global.h"

void get_public_address();
std::string extract_ip(struct sockaddr_in &);
int read_from_socket(int, std::stringstream *);
int sendall(int &, std::string &);

#endif