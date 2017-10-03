#ifndef MACHINE_H_
#define MACHINE_H_

#include <iostream>
#include <vector>

class Machine
{
  public:
    int fd, port, sent, rcvd;
    bool is_logged;
    std::string ip, hostname;
    std::vector<Machine *> blocked;

    Machine(int f, int p, std::string i, std::string h) : fd(f), port(p), ip(i), hostname(h), is_logged(0), sent(0), rcvd(0){};

    bool is_blocked_ip(const std::string &);
    void block(Machine *);
    void unblock(const std::string &);
};

#endif