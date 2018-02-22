
/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include <iostream>
#include "places.h"
#include "tries.h"
#include "airport.h"
#include "string.h"

list_airport_res *
listairport_1_svc(user_input *argp, struct svc_req *rqstp)
{
	name city, state;
	location loc;
	city = strdup(argp->city);
	state = strdup(argp->state);
	static list_airport_res  result;

    std::cout<<"Entering verymain";
		verymain();
    trieNode *pNode = (struct trieNode *) malloc(sizeof(struct trieNode));
    std::cout<<"Done with verymain!";
		fflush(stdout);
		char searchStr[100];
		strcpy(searchStr, argp->state);
		strcat(searchStr, argp->city);
    pNode = partialSearch(root->children, searchStr);
    std::cout<<"after  partial search";
		fflush(stdout);
		if (pNode != NULL)
		{
			std::cout<<pNode->longitude;
			std::cout<<pNode->latitude;
			std::cout<<pNode->entry+2;
			fflush(stdout);
		} else
		{
			std::cout<<"Partial search returned empty!";
			fflush(stdout);
			result.errno=1;
			return &result;
		}

		CLIENT *clnt;
		list_location_res  *result_1;
		location_as  listlocation_as_arg;
		char host[10];
		strcpy(host,"localhost");
    std::cout<<"calling localhost";
		fflush(stdout);
	#ifndef	DEBUG
		clnt = clnt_create (host, LOCATIONPROG, LOCATIONVER, "udp");
		if (clnt == NULL) {
			clnt_pcreateerror (host);
			std::cout<<"Unable to create client for airport server on localhost";
			fflush(stdout);
			exit (1);
		}
	#endif	/* DEBUG */
  listlocation_as_arg.latitude = pNode->latitude;
	listlocation_as_arg.longitude = pNode->longitude;


   result_1 = listlocation_1(&listlocation_as_arg, clnt);
	 if (result_1 == (list_location_res *) NULL)
	 {
 		clnt_perror (clnt, "call failed");
		result.errno=1;
		return &result;
 	 }

	std::cout<<"Successfully result return from airport server";
	fflush(stdout);

	result.errno = 0;
	result.list_airport_res_u.result.input_res.city = strdup(pNode->entry+2);
  result.list_airport_res_u.result.input_res.state = strdup(state);
	result.list_airport_res_u.result.input_res.latlong.longitude = pNode->latitude;
  result.list_airport_res_u.result.input_res.latlong.latitude = pNode->latitude;

	airport_info_as* linkedListFromAirportServ = result_1->list_location_res_u.list_location_res;

	airport_info* linkedListForClient, *curr;

	linkedListForClient = curr = NULL;

	while(linkedListFromAirportServ != NULL)
	{
		if (linkedListForClient == NULL)
		{
			linkedListForClient = new airport_info;
			curr = linkedListForClient;
			curr->next = NULL;
		}
		else
		{
			curr->next = new airport_info;
			curr = curr->next;
			curr->next = NULL;
		}

		curr->city = strdup(linkedListFromAirportServ->city);
		curr->state = strdup(linkedListFromAirportServ->state);
		curr->airport_code = strdup(linkedListFromAirportServ->airport_code);
		curr->distance = linkedListFromAirportServ->distance;

		linkedListFromAirportServ = linkedListFromAirportServ->next;
	}
  //result.list_airport_res_u.result = *result_1;
	std::cout<<"Successfully result return to main client";
	fflush(stdout);
	// strcpy(result.input_res.city , substr(pNode->entry,2));
	// strcpy(result.input_res.state , state);

	result.list_airport_res_u.result.list = linkedListForClient;
	return &result;
}
