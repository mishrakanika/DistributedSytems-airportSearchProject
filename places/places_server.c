
/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include <iostream>
#include "places.h"
#include "mytries.h"
#include "airport.h"
#include "string.h"






list_airport_res *
listairport_1_svc(user_input *argp, struct svc_req *rqstp) {
	name city, state;
	location loc;
	city = strdup(argp->city);
	state = strdup(argp->state);
	static list_airport_res result;

	loadtrie(); //calling it to create the trei


	char searchStr[100];
	strcpy(searchStr, argp->state);
	strcat(searchStr, argp->city);

	//converting the user input to lower case for searching in trie
	int i;
	for (i = 0; searchStr[i]; i++) {
		searchStr[i] = tolower(searchStr[i]);
	}
//calling the function to search the user input into the tries
	cityData searchResult = trieSearch(searchStr);

	if (searchResult.err == 7) {
//if ambiguity return error
		result.errno = 7;
		return &result;
	}

	if (searchResult.err == 1) {
//if city not found return error
		result.errno = 1;
		return &result;
	}

	//freeing the previously allocated memory
	xdr_free((xdrproc_t) xdr_list_airport_res, (char *) &result);

	//created the airport server client
	CLIENT *clnt;
	list_location_res *result_1;
	location_as listlocation_as_arg;
	char host[10];
	strcpy(host, "localhost");

#ifndef    DEBUG
	clnt = clnt_create(host, LOCATIONPROG, LOCATIONVER, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror(host);
		std::cout << "Unable to create client for airport server on localhost";
		fflush(stdout);
		exit(1);
	}
#endif    /* DEBUG */
    //passing the coordinates to airport server
	listlocation_as_arg.latitude = searchResult.latlong.latitude;
	listlocation_as_arg.longitude = searchResult.latlong.longitude;

//calling airport server
	result_1 = listlocation_1(&listlocation_as_arg, clnt);
	if (result_1 == (list_location_res *) NULL) {
		clnt_perror(clnt, "call failed");
		exit(1);
	}

	if (result_1->errno > 0) {
		//freeing the memory and returning  error if airport location is not available
		clnt_freeres(clnt, (xdrproc_t) xdr_list_location_res, (char *) result_1);
		result.errno = 2;
		return &result;
	}

	//copying the airport server result to places server result
	result.errno = 0;
	result.list_airport_res_u.result.input_res.city = strdup(searchResult.city + 2);
	result.list_airport_res_u.result.input_res.state = strdup(state);
	result.list_airport_res_u.result.input_res.latlong.longitude = searchResult.latlong.latitude;
	result.list_airport_res_u.result.input_res.latlong.latitude = searchResult.latlong.longitude;

	airport_info_as *linkedListFromAirportServ = result_1->list_location_res_u.list_location_res;

	airport_info *linkedListForClient, *curr;

	linkedListForClient = curr = NULL;
//copying returned link list into the places server result
	while (linkedListFromAirportServ != NULL) {
		if (linkedListForClient == NULL) {
			linkedListForClient = new airport_info();
			curr = linkedListForClient;
			curr->next = NULL;
		} else {
			curr->next = new airport_info();
			curr = curr->next;
			curr->next = NULL;
		}

		char * positionOfComma = strchr(linkedListFromAirportServ->city, ',');
		*positionOfComma = '\0';
		*(positionOfComma+3) = '\0';
		char* airportName = strdup(linkedListFromAirportServ->city);
		curr->city = strdup(linkedListFromAirportServ->city);
		curr->state = strdup(positionOfComma+1);
		curr->airport_code = strdup(linkedListFromAirportServ->airport_code);
		curr->distance = linkedListFromAirportServ->distance;

		linkedListFromAirportServ = linkedListFromAirportServ->next;
	}
	//result.list_airport_res_u.result = *result_1;

	xdr_free((xdrproc_t) xdr_list_location_res, (char *) result_1);

	clnt_destroy(clnt);
//returning result from airport server and user input to places client
	result.list_airport_res_u.result.list = linkedListForClient;
	return &result;
}
