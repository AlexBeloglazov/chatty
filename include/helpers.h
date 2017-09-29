#ifndef HELPERS_H_
#define HELPERS_H_

#include "global.h"


void read_stdin(std::istringstream &);
char *str2char(std::string &);
bool cmp_ports(Machine *, Machine *);
std::string extract_ip(struct sockaddr_in &);
bool is_valid_ip(const std::string &);

#endif