#include "../include/helpers.h"

bool cmp_ports(Machine *l, Machine *r) {
    return (l->port < r->port);
}

void ml_sort_by_port(std::vector<Machine*> *mlist) {
    std::sort(mlist->begin(), mlist->end(), cmp_ports);
}

void ml_remove_by_ip(std::vector<Machine*> *mlist, const std::string &ip) {
    std::vector<Machine*>::iterator it;
    for(it = mlist->begin(); it != mlist->end(); ++it) {
        if ((*it)->ip == ip) {
            delete *it;
            mlist->erase(it);
            break;
        }
    }
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

void read_from_stream(std::istringstream &ss, int l, std::string &buf) {
    buf.resize(l);
    ss.ignore(1);
    ss.read(&buf[0], l);
}

char *str2char(std::string &line) {
    return (char *) (line + "\n").c_str();
}
