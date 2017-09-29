
namespace server
{

extern std::vector<Machine *> clients;

void cmd_port()
{
    print_success(_CMD_PORT, str2char(params->port), 1);
}



}