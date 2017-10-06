/*
 * client.cpp : Main file for the client mode of the programm
 * Created for CSE 589 Fall 2017 Programming Assignment 1
 * @author Alexander Beloglazov
 */

#include "messages.cpp"
#include "commands.cpp"

namespace client
{

int connection_fd = -1, max_fd = 0;
fd_set read_fds, temp_read_fds;
Machine *self;
std::vector<Machine *> peers;

/* 
 * Method reads STDIN and depending on which command has been entered, executes corresponding helper from commands.cpp
 */
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
        cmd_exit();
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
        cmd_login(input);
        break;
    }

    case CMD_LOGOUT:
        cmd_logout();
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

/* 
 * Method reads STDIN and depending on which command has been entered, executes corresponding helper
 */
void handle_server_message()
{
    std::stringstream stream;
    std::string msg;

    int rcvd = read_packet(connection_fd, &stream);

    // most likely the server closed the connection
    if (rcvd <= 0)
    {
        return;
    }

    stream >> msg;

    switch (identify_msg(msg))
    {

    case MSG_SEND_:
    {
        msg_send(stream);
        break;
    }

    }
}

/* 
 * Method which executes the programm in the client mode
 */
void run()
{
    FD_ZERO(&read_fds);
    FD_SET(STDIN_FILENO, &read_fds);
    max_fd = STDIN_FILENO;

    self = new Machine(-1, std::atoi(params->port.c_str()), params->ip_address, params->hostname);
    peers.push_back(self);

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