namespace server {

extern std::vector<Machine *> clients;

void msg_refresh(int fd)
{
    std::stringstream stream, payload;
    int cl_count = 0;
    Machine *m;
    for (std::vector<Machine *>::iterator it = clients.begin(); it != clients.end(); ++it)
    {
        m = *it;
        if (m->is_logged)
        {
            cl_count++;
            payload << " " << m->hostname
                    << " " << m->ip
                    << " " << m->port;
        }
    }
    stream << _MSG_REFRESH << " " << cl_count << payload.str();
    send_packet(fd, stream.str());
}
}