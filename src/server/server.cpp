#include "commands.cpp"
#include "messages.cpp"

namespace server
{

int server_fd, max_fd;
fd_set read_fds, temp_read_fds;
std::vector<Machine*> clients;
std::map<std::string, std::vector<std::string>*> buffered_msg;


int create_socket_open_port(int port)
{
    int socket_fd, y = 1;
    struct sockaddr_in server_addrinfo, client_addrinfo;
    socklen_t addr_len = sizeof(server_addrinfo);
    memset(&server_addrinfo, 0, addr_len);
    server_addrinfo.sin_family = AF_INET;
    server_addrinfo.sin_port = htons(port);
    inet_pton(AF_INET, params->ip_address.c_str(), &(server_addrinfo.sin_addr));
    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("ERROR openning TCP socket");
        exit(1);
    }
    if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &y, addr_len) == -1)
    {
        perror("ERROR setting TCP socket options");
        exit(1);
    }
    if ((bind(socket_fd, (struct sockaddr *)(&server_addrinfo), addr_len)) == -1)
    {
        perror("ERROR binding TCP socket");
        exit(1);
    }
    if ((listen(socket_fd, SOMAXCONN)) == -1)
    {
        perror("ERROR openning TCP port");
        exit(1);
    }
    return socket_fd;
}

void handle_user_input()
{
    std::string cmd;
    std::stringstream input;
    read_stdin(input);
    input >> cmd;
    switch (identify_cmd(cmd))
    {

    case CMD_AUTHOR:
        cmd_author();
        break;

    case CMD_BLOCKED:
    {
        std::string ip;
        input >> ip;
        cmd_blocked(ip);
        break;
    }

    case CMD_EXIT:
    {
        close(server_fd);
        exit(0);
    }

    case CMD_IP:
        cmd_ip();
        break;

    case CMD_LIST:
        cmd_list(&clients);
        break;

    case CMD_PORT:
        cmd_port();
        break;

    case CMD_STATISTICS:
        cmd_statistics();
        break;

    case CMD_UNKNOWN:
        break;
    }
}

void send_buffered_msg(int fd, const std::string &ip) {
    std::map<std::string, std::vector<std::string>*>::iterator it;
    std::stringstream out;
    it = buffered_msg.find(ip);
    if (it == buffered_msg.end() || it->second->empty()) {
        out << _MSG_BUFFERED << " 0";
    }
    else {
        std::vector<std::string> *msgs = it->second;
        std::vector<std::string>::iterator itv;
        Machine *rcpt;

        out << _MSG_BUFFERED << " " << msgs->size();

        rcpt = get_machine(ip);

        for (itv = msgs->begin(); itv != msgs->end(); ++itv)
        {
            std::stringstream stream(*itv);

            rcpt->rcvd += 1;
            out << " " << itv->length() << " " << *itv;
        }
        // clean up
        msgs->clear();
    }
    send_packet(fd, out.str());
}


int handle_new_client() {
    struct sockaddr_in client_addrinfo;
    socklen_t addr_len = sizeof(client_addrinfo);
    int new_fd = accept(server_fd, (struct sockaddr *)&client_addrinfo, &addr_len);
    if (new_fd == -1) {
        perror("ERROR accepting new client");
    }
    else {
        std::stringstream stream;
        if (read_packet(new_fd, &stream) <= 0)
        {
            std::cout << "ERROR handling new client";
            return -1;
        }
        
        std::string msg, hostname, ip;
        int port;
        
        stream >> msg >> hostname >> port;
        
        if (msg != _MSG_LOGIN)
        {
            std::cout << "ERROR bad LOGIN message";
            return -1;
        }

        ip = extract_ip(client_addrinfo);

        // send a list of logged clients
        msg_refresh(new_fd);

        // send buffered messages if such exist
        send_buffered_msg(new_fd, ip);

        FD_SET(new_fd, &read_fds);
        if (new_fd > max_fd)
            max_fd = new_fd;

        Machine *client = get_machine(ip);

        // HANDLE CASE OF LOGIN AFTER LOGOUT
        if (client == NULL)
        {
            client = new Machine(new_fd, port, ip, hostname);

            // remember the client
            clients.push_back(client);

            // add to the IP->Machine map
            ip2machine->insert(std::pair<std::string, Machine *>(ip, client));
        }
        
        client->is_logged = 1;
    }
    return new_fd;
}

void buffer_msg(std::stringstream &ss, std::string dst_ip) {
    std::map<std::string, std::vector<std::string> *>::iterator it;
    
    // just in case restore the stream
    ss.clear();
    ss.seekg(0, ss.beg);
    
    it = buffered_msg.find(dst_ip);
    if (it == buffered_msg.end())
    {
        std::vector<std::string> *val = new std::vector<std::string>();
        it = buffered_msg.insert(
            std::pair<std::string, std::vector<std::string>*>(dst_ip, val)).first;
    }
    std::vector<std::string> *buffer = it->second;
    buffer->push_back(ss.str());
}

void handle_incoming_data(int fd)
{
    std::stringstream stream;
    std::string msg, who, whom;
    int rcvd = read_packet(fd, &stream);

    // a client closed the connection
    if (rcvd <= 0) {
        return;
    }

    stream >> msg;

    switch (identify_msg(msg))
    {

    case MSG_EXIT:
    {
        stream >> who;
        msg_exit(who);
        break;
    }

    case MSG_LOGIN:
    {
        break;
    }

    case MSG_LOGOUT:
    {
        stream >> who;
        msg_logout(who);
        break;
    }

    case MSG_BLOCK:
    {
        stream >> who >> whom;
        msg_block(who, whom);
        break;
    }

    case MSG_REFRESH:
        msg_refresh(fd);
        break;

    case MSG_SEND_:
    {
        msg_send(stream);
        break;
    }

    case MSG_UNBLOCK:
    {
        stream >> who >> whom;
        msg_unblock(who, whom);
        break;
    }
    }
}

void run()
{
    server_fd = create_socket_open_port(std::atoi(params->port.c_str()));
    FD_ZERO(&read_fds);
    FD_SET(STDIN_FILENO, &read_fds);
    FD_SET(server_fd, &read_fds);
    max_fd = server_fd;
    
    while(1) {

        temp_read_fds = read_fds;

        if (select(max_fd + 1, &temp_read_fds, NULL, NULL, NULL) == -1)
        {
            perror("ERROR while SELECT");
            exit(1);
        }

        for (int i = 0; i <= max_fd; i++) {
            if(FD_ISSET(i, &temp_read_fds)) {
                // new connection
                if (i == server_fd) {
                    handle_new_client();
                }
                // user input
                else if (i == STDIN_FILENO) {
                    handle_user_input();
                }
                // clients data
                else {
                    handle_incoming_data(i);              
                }
            }
        }
    }

    close(server_fd);
}

}