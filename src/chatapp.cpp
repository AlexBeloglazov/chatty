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

using namespace std;


void parse_params(int ac, char *av[], runtime_config *cfg) {
	if (ac == 3) {
		cfg->is_server = string(av[1]) == "s";
		cfg->port = av[2];
		return;
	}
	cout << "Bad parameters\n";
	exit(1);
}

void server(runtime_config *config) {
	
}

void client (runtime_config *config) {
	while (1) {

	}
}


int main(int argc, char **argv)
{
	runtime_config *config = new runtime_config();

	parse_params(argc, argv, config);
	(config->is_server) ? server(config) : client(config);

	return 0;
}
