/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "airport.h"

bool_t
xdr_name_as (XDR *xdrs, name_as *objp)
{
    register int32_t *buf;

     if (!xdr_string (xdrs, objp, MAXLEN))
         return FALSE;
    return TRUE;
}

bool_t
xdr_code_as (XDR *xdrs, code_as *objp)
{
    register int32_t *buf;

     if (!xdr_string (xdrs, objp, CODELEN))
         return FALSE;
    return TRUE;
}

bool_t
xdr_location_as (XDR *xdrs, location_as *objp)
{
    register int32_t *buf;

     if (!xdr_coordinates_as (xdrs, objp))
         return FALSE;
    return TRUE;
}

bool_t
xdr_airport_list_as (XDR *xdrs, airport_list_as *objp)
{
    register int32_t *buf;

     if (!xdr_pointer (xdrs, (char **)objp, sizeof (struct airport_info_as), (xdrproc_t) xdr_airport_info_as))
         return FALSE;
    return TRUE;
}

bool_t
xdr_airport_info_as (XDR *xdrs, airport_info_as *objp)
{
    register int32_t *buf;

     if (!xdr_code_as (xdrs, &objp->airport_code))
         return FALSE;
     if (!xdr_name_as (xdrs, &objp->city))
         return FALSE;
     if (!xdr_code_as (xdrs, &objp->state))
         return FALSE;
     if (!xdr_double (xdrs, &objp->distance))
         return FALSE;
     if (!xdr_airport_list_as (xdrs, &objp->next))
         return FALSE;
    return TRUE;
}

bool_t
xdr_coordinates_as (XDR *xdrs, coordinates_as *objp)
{
    register int32_t *buf;

     if (!xdr_double (xdrs, &objp->latitude))
         return FALSE;
     if (!xdr_double (xdrs, &objp->longitude))
         return FALSE;
    return TRUE;
}

bool_t
xdr_list_location_res (XDR *xdrs, list_location_res *objp)
{
    register int32_t *buf;

     if (!xdr_int (xdrs, &objp->errno))
         return FALSE;
    switch (objp->errno) {
    case 0:
         if (!xdr_airport_list_as (xdrs, &objp->list_location_res_u.list_location_res))
             return FALSE;
        break;
    default:
        break;
    }
    return TRUE;
}
