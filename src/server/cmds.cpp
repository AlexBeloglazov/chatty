
namespace server
{

void cmd_port()
{
    print_success((char *)"PORT", str2char(params->port), 1);
}

}