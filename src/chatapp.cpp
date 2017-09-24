/**
 * @author  Alexander Beloglazov <abelogla@buffalo.edu>
 * @version 1.0
 *
 * @section LICENSE
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details at
 * http://www.gnu.org/copyleft/gpl.html
 *
 * @section DESCRIPTION
 *
 * This contains the main function. Add further description here....
 */


#include "../include/global.h"

#include "server/server.cpp"
#include "client/client.cpp"


using namespace std;

runtime_params *params;

void print_usage(const char *exec)
{
	std::cout << "\nUSAGE: " << exec << " {c|s} <port>\n\n"
			  << "Options:\n"
			  << "\tc\tExecute in the client mode;\n"
			  << "\ts\tExecute in the server mode;\n"
			  << "\t<port>\tPort number to listen for connections on;\n\n";
	exit(1);
};

void get_public_address()
{
	int socket_fd;
	struct sockaddr_in serv_addr, self_addr;
	socklen_t addr_len = sizeof(self_addr);
	if ((socket_fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
	{
		cout << "ERROR openning UDP socket\n";
		exit(1);
	}
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(LOOKUP_PORT);
	inet_pton(AF_INET, LOOKUP_IP, &(serv_addr.sin_addr));
	if (connect(socket_fd, (sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		cout << "ERROR connecting to " << LOOKUP_IP << "\n";
		exit(1);
	}
	getsockname(socket_fd, (sockaddr *)&self_addr, &addr_len);
	char str_ip[INET_ADDRSTRLEN];
	inet_ntop(self_addr.sin_family, &(self_addr.sin_addr), str_ip, sizeof(str_ip));
	params->ip_address = string(str_ip);
	struct hostent *host_info = gethostbyaddr(
		&(self_addr.sin_addr), sizeof(struct in_addr), AF_INET);
	params->hostname = string(host_info->h_name);
	close(socket_fd);
}


int main(int argc, char **argv)
{

	if (argc != 3) {
		print_usage(argv[0]);
	}

	params = new runtime_params();
	params->is_server = string(argv[1]) == "s";
	params->is_logged = 0;
	params->port = argv[2];
	
	get_public_address();

	(params->is_server) ? server::run() : client::run();
	
	return 0;
}
