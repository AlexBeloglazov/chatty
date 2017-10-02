#ifndef HELPERS_H_
#define HELPERS_H_

#include "global.h"


void read_stdin(std::istringstream &);
void read_from_stream(std::istringstream &, int, std::string &);
char *str2char(std::string &);
void ml_sort_by_port(std::vector<Machine*> *);
void ml_remove_by_ip(std::vector<Machine*> *, const std::string &);
std::string extract_ip(struct sockaddr_in &);
bool is_valid_ip(const std::string &);

#endif