#include "../include/protocol.h"



int send_packet(int fd, std::string message)
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

int read_packet(int fd, std::stringstream *stream)
{
    int rcvd;
    char meta[META_LENGTH + 1] = {0};
    rcvd = readall(fd, meta, META_LENGTH);
    if (rcvd <= 0)
    {
        if (rcvd == -1)
            std::cout << "ERROR reading meta\n";
        return rcvd;
    }

    int m_length = std::atoi(meta);
    char m_buffer[m_length + 1];
    memset(m_buffer, 0, sizeof m_buffer);

    rcvd = readall(fd, m_buffer, m_length);

    if (rcvd <= 0)
    {
        if (rcvd == -1)
            std::cout << "ERROR reading message body\n";
        return rcvd;
    }

    stream->str(m_buffer);
    return rcvd;
}