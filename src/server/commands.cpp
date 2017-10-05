
namespace server
{

extern std::vector<Machine *> clients;

void cmd_statistics() {
    std::vector<Machine *>::iterator it;
    std::string out;
    std::string logged = "logged-in", loggedout = "logged-out";
    std::stringstream stream;
    ml_sort_by_port(&clients);
    for(it = clients.begin(); it != clients.end(); ++it) {
        stream << std::left << std::setw(5) << (it - clients.begin() + 1)
               << std::setw(35) << (*it)->hostname
               << std::setw(8) << (*it)->sent
               << std::setw(8) << (*it)->rcvd
               << std::setw(8) << ((*it)->is_logged ? logged : loggedout) << "\n";
        out += stream.str();
        stream.clear();
        stream.str(std::string());
    }
    print_success(_CMD_STATISTICS, &out[0]);
}

void cmd_blocked(const std::string &ip) {
    std::map<std::string, Machine*>::iterator it;
    it = ip2machine->find(ip);
    if (!is_valid_ip(ip) || it == ip2machine->end()) {
        print_error(_CMD_BLOCKED);
        return;
    }
    std::vector<Machine*> *blocked = &(it->second->blocked);
    std::vector<Machine*>::iterator itb;
    std::stringstream stream;
    std::string out;
    ml_sort_by_port(blocked);
    for(itb = blocked->begin(); itb != blocked->end(); ++itb) {
        stream << std::left << std::setw(5) << (itb - blocked->begin() + 1)
               << std::setw(35) << (*itb)->hostname
               << std::setw(20) << (*itb)->ip
               << std::setw(8) << (*itb)->port << "\n";
        out += stream.str();
        stream.clear();
        stream.str(std::string());
    }
    print_success(_CMD_BLOCKED, &out[0]);
}

}