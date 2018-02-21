/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "airport.h"


void
locationprog_1(char *host)
{
	CLIENT *clnt;
	list_location_res  *result_1;
	location  listlocation_1_arg;

#ifndef	DEBUG
	clnt = clnt_create (host, LOCATIONPROG, LOCATIONVER, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

	result_1 = listlocation_1(&listlocation_1_arg, clnt);
	if (result_1 == (list_location_res *) NULL) {
		clnt_perror (clnt, "call failed");
	}
#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


int
main (int argc, char *argv[])
{
	char *host;

	if (argc < 2) {
		printf ("usage: %s server_host\n", argv[0]);
		exit (1);
	}
	host = argv[1];
	locationprog_1 (host);
exit (0);
}
