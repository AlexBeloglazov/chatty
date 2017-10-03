#include "messages.cpp"
#include "commands.cpp"

namespace client
{

int connection_fd = -1, max_fd;
fd_set read_fds, temp_read_fds;
Machine *self;
std::vector<Machine *> peers;

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

    case CMD_BLOCK:
        cmd_block(input);
        break;

    case CMD_BROADCAST:
        cmd_broadcast(input);
        break;

    case CMD_EXIT:
        exit(0);
        break;

    case CMD_IP:
        cmd_ip();
        break;

    case CMD_LIST:
    {
        if (connection_fd == -1) {
            print_error(_CMD_LIST);
        }
        else {
            cmd_list(&peers);
        }
        break;
    }
        
    case CMD_LOGIN:
    {
        std::string server_ip, server_port;
        input >> server_ip >> server_port;
        cmd_login(server_ip, server_port);
        break;
    }

    case CMD_LOGOUT:
        break;

    case CMD_PORT:
        cmd_port();
        break;

    case CMD_REFRESH:
        cmd_refresh();
        break;

    case CMD_SEND:
        cmd_send(input);
        break;

    case CMD_UNBLOCK:
        cmd_unblock(input);
        break;

    case CMD_UNKNOWN:
        break;
    }
}

void handle_server_message()
{
    std::stringstream stream;
    std::string msg;

    int rcvd = read_packet(connection_fd, &stream);

    // the server closed the connection
    if (rcvd <= 0)
    {
        return;
    }

    stream >> msg;

    switch (identify_msg(msg))
    {

    case MSG_SEND:
    {
        msg_send(stream);
        break;
    }

    }
}

void run()
{
    std::cout << "client started!" << "\n";
    FD_ZERO(&read_fds);
    FD_SET(STDIN_FILENO, &read_fds);
    max_fd = STDIN_FILENO;

    Machine *g = new Machine(34, 90, "128.205.36.34", "euston.cse.buffalo.edu");
    g->is_logged = 1;
    peers.push_back(g);
    ip2machine->insert(std::pair<std::string, Machine *>(g->ip, g));
    g = new Machine(456, 91, "128.205.36.33", "highgate.cse.buffalo.edu");
    g->is_logged = 1;
    peers.push_back(g);
    ip2machine->insert(std::pair<std::string, Machine *>(g->ip, g));

    self = new Machine(-1, std::atoi(params->port.c_str()), params->ip_address, params->hostname);

    while(1) {
        temp_read_fds = read_fds;
        if (select(max_fd + 1, &temp_read_fds, NULL, NULL, NULL) == -1)
        {
            perror("ERROR while SELECT");
            exit(1);
        }
        for (int i = 0; i <= max_fd; i++)
        {
            if (FD_ISSET(i, &temp_read_fds))
            {
                // message from server
                if (i == connection_fd)
                {
                    std::cout << "server message\n";
                    handle_server_message();
                }
                // user input
                else if (i == STDIN_FILENO)
                {
                    handle_user_input();
                }
            }
        }
    }
}
}