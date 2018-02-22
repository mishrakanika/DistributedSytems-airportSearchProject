/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include <stdlib.h>
#include "places.h"
#include "iostream"


void
airportprog_1(char *host, name city,name state)
{
	CLIENT *clnt;
	list_airport_res  *result_1;
	user_input  listairport_1_arg;

#ifndef	DEBUG
	clnt = clnt_create (host, AIRPORTPROG, AIRPORTVERS, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */
    listairport_1_arg.city = city;
    listairport_1_arg.state = state;

	result_1 = listairport_1(&listairport_1_arg, clnt);
	if (result_1 == (list_airport_res *) NULL) {
		clnt_perror (clnt, "call failed");
	}
#ifndef	DEBUG

  if(result_1->errno != 0) {
    std::cout<<"City not found , please try again";
       perror("The Following error occurred:");
       exit(1);
    }

	 std::cout<<result_1->list_airport_res_u.result.input_res.city<<", ";
	 std::cout<<result_1->list_airport_res_u.result.input_res.state<<": ";
	 std::cout<<result_1->list_airport_res_u.result.input_res.latlong.latitude<<", ";
	 std::cout<<result_1->list_airport_res_u.result.input_res.latlong.longitude<<"\n";

   airport_list curr = result_1->list_airport_res_u.result.list;
	 while(curr != NULL)
	 {
			std::cout<<"code = "<<curr->airport_code<<", ";
      std::cout<<"name = "<<curr->city<<", ";
			std::cout<<"state = "<<curr->state<<", ";
			std::cout<<"distance = "<<curr->distance<<" miles"<<"\n";
			curr = curr->next;
	 }

    clnt_freeres (clnt,(xdrproc_t) xdr_list_airport_res, (char *)result_1);

	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


int
main (int argc, char *argv[])
{
	char *host;
    name city,state;

	if (argc < 2) {
		printf("usage: %s server_host\n", argv[0]);
		exit (1);
	}
	host = argv[1];
    host = argv[1];
    city = argv[2];
    state = argv[3];
    airportprog_1 (host,city,state);
exit (0);
}
