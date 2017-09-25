#include "../include/helpers.h"

std::vector<std::string> *read_line()
{
    std::vector<std::string> *out = new std::vector<std::string>();
    std::string line, component;
    std::getline(std::cin, line);
    std::stringstream stream(line);
    while(stream >> component) {
        out->push_back(component);
    }
    if (out->empty()) out->push_back(std::string());
    return out;
}

int identify_cmd(std::string cmd)
{
    commands out;
    if (cmd == "AUTHOR") 
        out = CMD_AUTHOR;
    else if (cmd == "BLOCK")
        out = CMD_BLOCK;
    else if (cmd == "BLOCKED")
        out = CMD_BLOCKED;
    else if (cmd == "BROADCAST")
        out = CMD_BROADCAST;
    else if (cmd == "EXIT")
        out = CMD_EXIT;
    else if (cmd == "IP")
        out = CMD_IP;
    else if (cmd == "LIST")
        out = CMD_LIST;
    else if (cmd == "LOGIN")
        out = CMD_LOGIN;
    else if (cmd == "LOGOUT")
        out = CMD_LOGOUT;
    else if (cmd == "PORT")
        out = CMD_PORT;
    else if (cmd == "REFRESH")
        out = CMD_REFRESH;
    else if (cmd == "SEND")
        out = CMD_SEND;
    else if (cmd == "STATISTICS")
        out = CMD_STATISTICS;
    else if (cmd == "UNBLOCK")
        out = CMD_UNBLOCK;
    else
        out = CMD_UNKNOWN;
    return out;
}

char *str2char(std::string line) {
    return (char *) (line + "\n").c_str();
}

void print_success(char *cmd, char *outcome, bool p_out)
{
    printf("[%s:SUCCESS]\n", cmd);
    if (p_out)
        printf("%s:%s", cmd, outcome);
    printf("[%s:END]\n", cmd);
}

void print_success(char *cmd, char *outcome)
{
    printf("[%s:SUCCESS]\n", cmd);
    printf("%s", outcome);
    printf("[%s:END]\n", cmd);
}

void print_error(char *cmd)
{
    printf("[%s:ERROR]\n", cmd);
    printf("[%s:END]\n", cmd);
}

void print_usage(const char *exec)
{
    std::cout << "\nUSAGE: " << exec << " {c|s} <port>\n\n"
              << "Options:\n"
              << "\tc\tExecute in the client mode;\n"
              << "\ts\tExecute in the server mode;\n"
              << "\t<port>\tPort number to listen for connections on;\n\n";
    exit(1);
};

void get_public_address()
{
    int socket_fd;
    struct sockaddr_in serv_addr, self_addr;
    socklen_t addr_len = sizeof(self_addr);
    if ((socket_fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        std::cout << "ERROR openning UDP socket\n";
        exit(1);
    }
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(LOOKUP_PORT);
    inet_pton(AF_INET, LOOKUP_IP, &(serv_addr.sin_addr));
    if (connect(socket_fd, (sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        std::cout << "ERROR connecting to " << LOOKUP_IP << "\n";
        exit(1);
    }
    getsockname(socket_fd, (sockaddr *)&self_addr, &addr_len);
    char str_ip[INET_ADDRSTRLEN];
    inet_ntop(self_addr.sin_family, &(self_addr.sin_addr), str_ip, sizeof(str_ip));
    params->ip_address = std::string(str_ip);
    struct hostent *host_info = gethostbyaddr(
        &(self_addr.sin_addr), sizeof(struct in_addr), AF_INET);
    params->hostname = std::string(host_info->h_name);
    close(socket_fd);
}