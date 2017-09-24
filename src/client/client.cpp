#include "cmds.cpp"

namespace client
{

void run()
{
    //--------------------------------------------------------------------------
    std::vector<std::string> *line;

    //--------------------------------------------------------------------------

    while (1)
    {
        line = read_line();
        switch (identify_cmd(line->front()))
        {
        case CMD_AUTHOR:
            cmd_author();
            break;

        case CMD_BLOCK:
            break;

        case CMD_BLOCKED:
            break;

        case CMD_BROADCAST:
            break;

        case CMD_EXIT:
            exit(0);
            break;

        case CMD_IP:
            cmd_ip();
            break;

        case CMD_LIST:
            break;

        case CMD_LOGIN:
            break;

        case CMD_LOGOUT:
            break;

        case CMD_PORT:
            cmd_port();
            break;

        case CMD_REFRESH:
            break;

        case CMD_SEND:
            break;

        case CMD_STATISTICS:
            break;

        case CMD_UNBLOCK:
            break;

        case CMD_UNKNOWN:
            break;
        }
        delete line;
    }
}
}