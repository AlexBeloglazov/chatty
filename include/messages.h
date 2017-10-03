#ifndef MESSAGES_H_
#define MESSAGES_H_

#include "global.h"

#define _MSG_BLOCK "BLOCK"
#define _MSG_UNBLOCK "UNBLOCK"
#define _MSG_BUFFERED "BUFFERED"
#define _MSG_LOGIN "LOGIN"
#define _MSG_REFRESH "REFRESH"

enum messages
{
    MSG_BLOCK,
    MSG_BUFFERED,
    MSG_LOGIN,
    MSG_REFRESH,
    MSG_UNBLOCK,
    MSG_UNKNOWN
};

int identify_msg(std::string &);

#endif