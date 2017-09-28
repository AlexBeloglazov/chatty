#include "cmds.cpp"

namespace server
{

int server_fd, max_fd;
fd_set read_fds, temp_read_fds;
std::vector<Machine *> clients;


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


void handle_user_input() {
    std::vector<std::string> *line;
    line = read_stdin();
    switch (identify_command(line->front()))
    {

    case CMD_AUTHOR:
        cmd_author();
        break;

    case CMD_BLOCK:
        break;

    case CMD_BLOCKED:
        break;

    case CMD_BROADCAST:
        break;

    case CMD_EXIT:
        {
        close(server_fd);
        exit(0);
        }
        break;

    case CMD_IP:
        cmd_ip();
        break;

    case CMD_LIST:
        break;

    case CMD_LOGIN:
        break;

    case CMD_LOGOUT:
        break;

    case CMD_PORT:
        cmd_port();
        break;

    case CMD_REFRESH:
        break;

    case CMD_SEND:
        break;

    case CMD_STATISTICS:
        break;

    case CMD_UNBLOCK:
        break;

    case CMD_UNKNOWN:
        break;
    }
    delete line;
}


int handle_new_client() {
    struct sockaddr_in client_addrinfo;
    socklen_t addr_len = sizeof(client_addrinfo);
    int new_fd = accept(server_fd, (struct sockaddr *)&client_addrinfo, &addr_len);
    if (new_fd == -1) {
        perror("ERROR accepting new client");
    }
    else {
        // TODO sent a list of logged clients
        std::stringstream *stream;
        stream = new std::stringstream("oops");
        int rcvd = read_from_socket(new_fd, stream);
        if (rcvd <= 0) {
            perror("ERROR handling new client");
            return -1;
        }
        std::cout << stream->str() << "\n";
        Machine *client = new Machine(
            new_fd,
            client_addrinfo.sin_port,
            extract_ip(client_addrinfo),
            std::string("")
        );
        clients.push_back(client);
        FD_SET(new_fd, &read_fds);
        if (new_fd > max_fd)
            max_fd = new_fd;
    }
    return new_fd;
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
                    std::cout << "new connection\n";
                    handle_new_client();
                    exit(0);
                }
                // user input
                else if (i == STDIN_FILENO) {
                    handle_user_input();
                }
                // clients data
                else {
                    std::cout << "new data!\n";                
                }
            }
        }
    }
    close(server_fd);
}

}