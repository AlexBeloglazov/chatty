#include "../include/cmds.h"

void cmd_author()
{
    std::stringstream out;
    out << "I, " << AUTHOR
        << ", have read and understood the course academic integrity policy.\n";
    print_success((char *)"AUTHOR", (char *)out.str().c_str(), 1);
}

void cmd_ip()
{
    print_success((char *)"IP", str2char(params->ip_address), 1);
}