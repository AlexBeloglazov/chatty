namespace client {

extern int connection_fd;
extern std::vector<Machine *> peers;


void msg_refresh(std::stringstream &stream)
{

}

void msg_send(std::stringstream &stream) {
    std::string from_ip, to_ip, msg;
    std::stringstream success_msg;

    stream >> from_ip >> to_ip;
    stream >> std::ws;

    msg = stream.str();
    msg = msg.substr(stream.tellg());

    success_msg << "msg from:"
                << from_ip << "\n"
                << "[msg]:"
                << msg << "\n";
    
    print_success(_RECEIVED, &success_msg.str()[0]);
}

void msg_buffered(std::stringstream &stream)
{
    int m_count, m_size;
    std::string msg;
    std::stringstream msg_stream;

    stream >> m_count;

    for (int i = 0; i < m_count; ++i) {
        stream >> m_size;
        read_from_stream((std::istringstream &) stream, m_size, msg);
        msg_stream.str(msg);

        // just skip MSG part
        msg_stream >> msg;
        
        msg_send(msg_stream);
    }
}

}