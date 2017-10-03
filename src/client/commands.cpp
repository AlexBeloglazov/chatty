
namespace client
{

extern int connection_fd;
extern fd_set read_fds;
extern std::vector<std::string> blocked_ip;
extern Machine *self;

void cmd_login(std::string &server_ip, std::string &server_port)
{
    // check ip validity and whether we already logged-in
    if (connection_fd > -1 || !is_valid_ip(server_ip) || !is_number(server_port))
    {
        print_error(_CMD_LOGIN);
        return;
    }

    struct sockaddr_in serv_addr;
    socklen_t addr_len = sizeof(serv_addr);

    memset(&serv_addr, 0, addr_len);

    if ((connection_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("ERROR creating TCP socket");
        exit(1);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(std::atoi(server_port.c_str()));

    inet_pton(AF_INET, server_ip.c_str(), &(serv_addr.sin_addr));

    if (connect(connection_fd, (sockaddr *)&serv_addr, addr_len) < 0)
    {
        perror((std::string("ERROR connecting to ") + server_ip).c_str());
        exit(1);
    }

    std::stringstream stream;
    std::string msg;

    if (read_packet(connection_fd, &stream) <= 0)
    {
        std::cout << "ERROR could not get list of users";
        return;
    }

    stream >> msg;

    if (msg != _MSG_REFRESH) {
        std::cout << "ERROR while parsing list of users";
        return;
    }

    msg_refresh(stream);

    if (read_packet(connection_fd, &stream) <= 0)
    {
        std::cout << "ERROR could not get list of buffered messages";
        return;
    }

    stream >> msg;

    if (msg != _MSG_BUFFERED)
    {
        std::cout << "ERROR while parsing list of buffered messages";
        return;
    }

    msg_buffered(stream);

    // add to the monitored FDs
    FD_SET(connection_fd, &read_fds);

    print_success(_CMD_LOGIN, NULL, 0);
}

void cmd_logout()
{
}

void cmd_port()
{
    if (params->is_logged)
        print_success((char *)"PORT", str2char(params->port), 1);
    else
        print_error((char *)"PORT");
}


void cmd_refresh() {

    std::string packet = _MSG_REFRESH, msg;
    std::stringstream stream;

    if (connection_fd == -1) {
        print_error(_CMD_REFRESH);
        return;
    }

    send_packet(connection_fd, packet);

    read_packet(connection_fd, &stream);

    stream >> msg;

    if(msg != _MSG_REFRESH) {
        std::cout << "ERROR while REFRESH";
        return;
    }

    msg_refresh(stream);

    print_success(_CMD_REFRESH, NULL, 0);

}

void cmd_send(std::stringstream &stream) {
    std::string to_ip, msg;
    std::stringstream msg_stream;

    if (connection_fd == -1)
    {
        print_error(_CMD_SEND);
        return;
    }

    stream >> to_ip;
    stream >> std::ws;

    if (!is_valid_ip(to_ip) || get_machine(to_ip, peers) == NULL)
    {
        print_error(_CMD_SEND);
        return;
    }

    msg = stream.str().substr(stream.tellg());

    msg_stream << _MSG_SEND << " "
               << params->ip_address << " "
               << BROADCAST_IP << " "
               << msg;

    send_packet(connection_fd, msg_stream.str());

    print_success(_CMD_SEND, NULL, 0);
}

void cmd_broadcast(std::stringstream &stream) {
    std::string msg;
    std::stringstream msg_stream;

    if (connection_fd == -1)
    {
        print_error(_CMD_BROADCAST);
        return;
    }

    stream >> std::ws;
    
    msg = stream.str().substr(stream.tellg());
    
    msg_stream << _MSG_SEND << " "
               << params->ip_address << " "
               << BROADCAST_IP << " "
               << msg;
    
    send_packet(connection_fd, msg_stream.str());

    print_success(_CMD_BROADCAST, NULL, 0);
}

void cmd_block(std::stringstream &stream) {
    std::string whom;
    std::stringstream packet_stream;
    stream >> whom;

    if (connection_fd == -1 || !is_valid_ip(whom))
    {
        print_error(_CMD_BLOCK);
        return;
    }

    Machine *whom_m = get_machine(whom, peers);

    if (whom_m == NULL || self->is_blocked_ip(whom)) {
        print_error(_CMD_BLOCK);
        return;
    }

    self->block(whom_m);

    packet_stream << _CMD_BLOCK << " "
                  << params->ip_address << " "
                  << whom;
    
    send_packet(connection_fd, packet_stream.str());

    print_success(_MSG_BLOCK, NULL, 0);

}

void cmd_unblock(std::stringstream &stream) {
    std::string whom;
    stream >> whom;

    if (connection_fd == -1 || !is_valid_ip(whom))
    {
        print_error(_CMD_UNBLOCK);
        return;
    }

    Machine *whom_m = get_machine(whom, peers);

    if (whom_m == NULL || !self->is_blocked_ip(whom))
    {
        print_error(_CMD_UNBLOCK);
        return;
    }

    self->unblock(whom);

    std::stringstream packet_stream;
    packet_stream << _MSG_UNBLOCK << " "
                  << params->ip_address << " "
                  << whom;
        
    send_packet(connection_fd, packet_stream.str());

    print_success(_CMD_UNBLOCK, NULL, 0);
}


}