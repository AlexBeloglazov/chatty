#include "cmds.cpp"

namespace client
{

int connection_fd = -1, max_fd;
fd_set read_fds, temp_read_fds;

void handle_user_input()
{
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
        exit(0);
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

    case CMD_UNBLOCK:
        break;

    case CMD_UNKNOWN:
        break;
    }
    delete line;
}


void handle_server_message() {

}


void run()
{
    FD_ZERO(&read_fds);
    FD_SET(STDIN_FILENO, &read_fds);
    max_fd = STDIN_FILENO;
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