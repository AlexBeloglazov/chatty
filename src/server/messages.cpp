/*
 * messages.cpp : File contains handlers for different messages which a server can receive from client
 * Created for CSE 589 Fall 2017 Programming Assignment 1
 * @author Alexander Beloglazov
 */

namespace server {

extern std::vector<Machine *> clients;
extern void buffer_msg(std::stringstream &, std::string);
extern std::map<std::string, std::vector<std::string> *> buffered_msg;
extern fd_set read_fds;

/* 
 * Handler for REFRESH message. Client wants to update its list of peers
 * @input fd file descriptor where to send the list to
 */
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

/* 
 * Handler for BLOCK message. Client wants to block someone
 * @input who IP address of a client who performs blocking
 * @input whom IP address of a client to block 
 */
void msg_block(const std::string &who, const std::string &whom) {
    std::map<std::string, Machine *>::iterator it;
    it = ip2machine->find(whom);
    if (it == ip2machine->end())
        return;
    Machine *who_m = ip2machine->find(who)->second, *whom_m = it->second;
    who_m->blocked.push_back(whom_m);
}

/* 
 * Handler for UNBLOCK message. Client wants to unblock someone
 * @input who IP address of a client who performs unblocking
 * @input whom IP address of a client to unblock 
 */
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

/* 
 * Handler for LOGOUT message. Client wants to logout
 * @input who IP address of a client who logs out
 */
void msg_logout(const std::string &who)
{
    Machine *who_m = get_machine(who);
    
    who_m->is_logged = 0;

    // stop monitoring fd
    FD_CLR(who_m->fd, &read_fds);

    // close socket
    close(who_m->fd);
}

/* 
 * Handler for EXIT message. Client wants to exit
 * @input who IP address of a client who wants to exit
 */
void msg_exit(const std::string &who)
{

    Machine *who_m = get_machine(who);

    // remove from ip2machine
    ip2machine->erase(who);

    // remove from clients
    std::vector<Machine *>::iterator it;
    for (it = clients.begin(); it != clients.end(); ++it)
    {
        if ((*it) == who_m)
        {
            clients.erase(it);
            break;
        }
    }

    // remove from blocked lists
    for (it = clients.begin(); it != clients.end(); ++it)
    {
        msg_unblock((*it)->ip, who);
    }

    // remove from buffered_msg, delete vector object
    std::map<std::string, std::vector<std::string> *>::iterator bufit;
    bufit = buffered_msg.find(who);
    if (bufit != buffered_msg.end()) {
        delete bufit->second;
        buffered_msg.erase(bufit);
    }

    // stop monitoring fd
    FD_CLR(who_m->fd, &read_fds);

    // close socket
    close(who_m->fd);

    // destruct Machine
    delete who_m;
}

/* 
 * Handler for SEND message. Client wants to send a message to another client
 * @input stream stringstream which contains meta information and message itself
 */
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