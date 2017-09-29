#ifndef _SOCKET_H_
#define _SOCKET_H_

#include "global.h"

#define META_LENGTH 5

int read_packet(int, std::stringstream *);
int send_packet(int, std::string);
int readall(int, char *, int);

#endif