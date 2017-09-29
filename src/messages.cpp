#include "../include/messages.h"

int identify_msg(std::string &msg)
{
    messages out;
    if (msg == _MSG_LOGIN)
        out = MSG_LOGIN;
    else
        out = MSG_UNKNOWN;
    return out;
}