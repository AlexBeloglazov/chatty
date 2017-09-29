
namespace client
{

void cmd_port()
{
    if (params->is_logged)
        print_success((char *)"PORT", str2char(params->port), 1);
    else
        print_error((char *)"PORT");
}
}