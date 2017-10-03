
namespace client
{

extern int connection_fd;
extern fd_set read_fds;

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
}