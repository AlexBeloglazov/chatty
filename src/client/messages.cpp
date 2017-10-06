/*
 * messages.cpp : File contains handlers for different messages which a client can receive from server
 * Created for CSE 589 Fall 2017 Programming Assignment 1
 * @author Alexander Beloglazov
 */

namespace client {

extern int connection_fd;
extern std::vector<Machine *> peers;
extern Machine *self;

/* 
 * Handler for REFRESH message. Updates local list of peers
 * @input stream stringstream which contains list of peers
 */
void msg_refresh(std::stringstream &stream)
{
    std::string p_hostname, p_ip;
    int p_count, p_port;
    stream >> p_count;

    // delete previous list of peers;
    std::vector<Machine*>::iterator it;

    for(it = peers.begin(); it != peers.end(); ++it) {

        if ((*it) == self) continue;
        
        // if the peer is blocked, keep the pointer in the blocked vector
        if (!self->is_blocked_ip((*it)->ip)) {
            delete *it;
        }
    }
    
    peers.clear();
    peers.push_back(self);

    for (int i = 0; i < p_count; ++i) {
        stream >> p_hostname >> p_ip >> p_port;

        if (self->ip == p_ip) continue;

        Machine *peer = new Machine(-1, p_port, p_ip, p_hostname);
        
        peer->is_logged = 1;
        peers.push_back(peer);
    }
}

/* 
 * Handler for SEND message. This message means we've got a message from peer
 * @input stream stringstream contains meta information and the message itself
 */
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

/* 
 * Handler for BUFFERED message. Receives messages from the server which were buffered
 * @input stream stringstream contains buffered messages
 */
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
        
        // handle each message
        msg_send(msg_stream);
    }
}

}