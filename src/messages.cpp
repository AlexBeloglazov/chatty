#include "../include/messages.h"

int identify_msg(std::string &msg)
{
    messages out;
    if (msg == _MSG_EXIT)
        out = MSG_EXIT;
    else if (msg == _MSG_LOGIN)
        out = MSG_LOGIN;
    else if (msg == _MSG_LOGOUT)
        out = MSG_LOGOUT;
    else if (msg == _MSG_BLOCK)
        out = MSG_BLOCK;
    else if (msg == _MSG_REFRESH)
        out = MSG_REFRESH;
    else if (msg == _MSG_SEND)
        out = MSG_SEND_;
    else if (msg == _MSG_UNBLOCK)
        out = MSG_UNBLOCK;
    else
        out = MSG_UNKNOWN;
    return out;
}