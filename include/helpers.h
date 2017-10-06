#ifndef HELPERS_H_
#define HELPERS_H_

#include "global.h"


void read_stdin(std::stringstream &);
void read_from_stream(std::istringstream &, int, std::string &);
void ml_sort_by_port(std::vector<Machine*> *);
void ml_remove_by_ip(std::vector<Machine*> *, const std::string &);
std::string extract_ip(struct sockaddr_in &);
bool is_valid_ip(const std::string &);
bool is_number(const std::string &);
Machine *get_machine(const std::string &);
Machine *get_machine(const std::string &, std::vector<Machine*> &);

#endif