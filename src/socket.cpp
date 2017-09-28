#include "../include/socket.h"

std::string extract_ip(struct sockaddr_in &sa)
{
    char str_ip[INET_ADDRSTRLEN];
    inet_ntop(sa.sin_family, &(sa.sin_addr), str_ip, sizeof(str_ip));
    return std::string(str_ip);
}

void get_public_address()
{
    int socket_fd;
    struct sockaddr_in serv_addr, self_addr;
    socklen_t addr_len = sizeof(self_addr);
    if ((socket_fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        perror("ERROR openning UDP socket");
        exit(1);
    }
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(LOOKUP_PORT);
    inet_pton(AF_INET, LOOKUP_IP, &(serv_addr.sin_addr));
    if (connect(socket_fd, (sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror((std::string("ERROR connecting to ") + std::string(LOOKUP_IP)).c_str());
        exit(1);
    }
    getsockname(socket_fd, (sockaddr *)&self_addr, &addr_len);
    params->ip_address = extract_ip(self_addr);
    struct hostent *host_info = gethostbyaddr(
        &(self_addr.sin_addr), sizeof(struct in_addr), AF_INET);
    params->hostname = std::string(host_info->h_name);
    close(socket_fd);
}

int sendall(int &fd, std::string &message)
{
    int m_len, b_sent, b_total = 0;
    std::stringstream meta;

    meta << std::setfill('0') << std::setw(META_LENGTH) << message.length();
    message = meta.str() + message;

    m_len = message.length();
    while (b_total < m_len)
    {
        b_sent = send(fd, &message[0] + b_total, m_len - b_total, 0);
        if (b_sent == -1)
            break;
        b_total += b_sent;
    }
    return b_sent == -1 ? -1 : 0;
}

int readall(int fd, char *buffer, int length) {
    int b_total = 0, b_received = 0;
    while (b_total < length) {
        b_received = read(fd, buffer + b_total, length - b_total);
        if (b_received <= 0) {
            if (b_received == 0 && b_total == 0)
                return 0;
            return -1;
        }
        else if (b_received == 0) break;
        b_total += b_received;
    }
    return b_total;
}

int read_from_socket(int fd, std::stringstream *stream)
{
    int rcvd;
    char meta[META_LENGTH + 1] = {0};
    rcvd = readall(fd, meta, META_LENGTH);
    if (rcvd <= 0)
    {
        if (rcvd == -1)
            perror("ERROR read meta");
        return rcvd;
    }

    int m_length = std::atoi(meta);
    char m_buffer[m_length + 1];
    memset(m_buffer, 0, sizeof m_buffer);

    rcvd = readall(fd, m_buffer, m_length);

    if (rcvd <= 0)
    {
        if (rcvd == -1)
            perror("ERROR reading message body");
        return rcvd;
    }

    stream->str(m_buffer);
    return rcvd;
}