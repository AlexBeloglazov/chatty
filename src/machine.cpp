#include "../include/machine.h"

bool Machine::is_blocked_ip(const std::string &ip)
{
    std::vector<Machine *>::iterator it;
    for (it = this->blocked.begin(); it != this->blocked.end(); ++it)
    {
        if (ip == (*it)->ip)
            return 1;
    }
    return 0;
}

void Machine::block(Machine * m)
{
    this->blocked.push_back(m);
}

void Machine::unblock(const std::string &unblock_ip)
{
    std::vector<Machine *>::iterator it;
    for (it = this->blocked.begin(); it != this->blocked.end(); ++it)
    {
        if (unblock_ip == (*it)->ip) {
            this->blocked.erase(it);
            break;
        }
    }
}