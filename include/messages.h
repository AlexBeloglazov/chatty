#ifndef MESSAGES_H_
#define MESSAGES_H_

#include "global.h"

#define _MSG_LOGIN "LOGIN"
#define _MSG_REFRESH "REFRESH"
#define _MSG_BUFFERED "BUFFERED"

enum messages
{
    MSG_LOGIN,
    MSG_REFRESH,
    MSG_BUFFERED,
    MSG_UNKNOWN
};

int identify_msg(std::string &);

#endif