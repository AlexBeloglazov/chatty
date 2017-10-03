namespace server {

extern std::vector<Machine *> clients;
extern void buffer_msg(std::stringstream &, std::string);

void msg_refresh(int fd)
{
    std::stringstream stream, payload;
    int cl_count = 0;
    Machine *m;
    for (std::vector<Machine *>::iterator it = clients.begin(); it != clients.end(); ++it)
    {
        m = *it;
        if (m->is_logged)
        {
            cl_count++;
            payload << " " << m->hostname
                    << " " << m->ip
                    << " " << m->port;
        }
    }
    stream << _MSG_REFRESH << " " << cl_count << payload.str();
    send_packet(fd, stream.str());
}

void msg_block(const std::string &who, const std::string &whom) {
    std::map<std::string, Machine *>::iterator it;
    it = ip2machine->find(whom);
    if (it == ip2machine->end())
        return;
    Machine *who_m = ip2machine->find(who)->second, *whom_m = it->second;
    who_m->blocked.push_back(whom_m);
}

void msg_unblock(const std::string &who, const std::string &whom) {
    std::vector<Machine*>::iterator blocked;
    Machine *who_m = get_machine(who);
    for(blocked = who_m->blocked.begin(); blocked != who_m->blocked.end(); ++blocked) {
        if ((*blocked)->ip == whom) {
            who_m->blocked.erase(blocked);
            break;
        }
    }
}

void msg_send(std::stringstream &stream) {
    std::string from_ip, to_ip, packet;
    stream >> from_ip >> to_ip;
    std::vector<Machine*> all_rcv = clients;
    if (to_ip != BROADCAST_IP) {
        all_rcv = std::vector<Machine *>();
        all_rcv.push_back(get_machine(to_ip));
    }

    Machine *from_m = get_machine(from_ip);
    from_m->sent += 1;

    std::stringstream success_mes;
    std::string sent_message(stream.str().substr((int)stream.tellg() + 1));

    std::vector<Machine*>::iterator receiver;
    
    for(receiver = all_rcv.begin(); receiver != all_rcv.end(); ++receiver) {
        Machine *rcv = *receiver;
        if (rcv == NULL || rcv->is_blocked_ip(from_ip) || rcv->ip == from_ip)
        {
            continue;
        }
        else if (!rcv->is_logged) {
            buffer_msg(stream, rcv->ip);
            std::cout << "buffering..." << "\n";
        }
        else {
            send_packet(rcv->fd, stream.str());
            rcv->rcvd += 1;
        }
    }

    success_mes << "msg from:" << from_ip
                << ", to:" << to_ip << "\n"
                << "[msg]:" << sent_message << "\n";
    print_success(_RELAYED, &success_mes.str()[0]);
}


}