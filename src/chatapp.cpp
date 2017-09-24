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
