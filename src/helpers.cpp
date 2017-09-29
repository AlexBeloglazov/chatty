#include "../include/helpers.h"

bool cmp_ports(Machine *l, Machine *r) {
    return (l->port > r->port);
}

std::string extract_ip(struct sockaddr_in &sa)
{
    char str_ip[INET_ADDRSTRLEN];
    inet_ntop(sa.sin_family, &(sa.sin_addr), str_ip, sizeof(str_ip));
    return std::string(str_ip);
}

bool is_valid_ip(const std::string &ip)
{
    struct sockaddr_in sa;
    return inet_pton(AF_INET, &ip[0], &(sa.sin_addr)) == 1;
}

void read_stdin(std::istringstream &inp)
{
    std::string line;
    std::getline(std::cin, line);
    inp.str(line);
}


char *str2char(std::string &line) {
    return (char *) (line + "\n").c_str();
}
