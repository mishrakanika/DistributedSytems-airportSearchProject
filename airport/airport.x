const MAXLEN = 255;
const CODELEN = 3;
typedef string name<MAXLEN>;
typedef string code<CODELEN>;
typedef struct coordinates_as location_as;
typedef struct airport_info_as *airport_list_as;

struct airport_info_as {
code airport_code;
  name city;
   code state;
   double distance;
   airport_list_as next;
};

struct coordinates_as {
   double latitude;
   double  longitude;
};


union list_location_res switch (int errno) {
case 0:
struct airport_info_as list_location_res;
default:
void;  };

program LOCATIONPROG
       {
               version LOCATIONVER
       {
           list_location_res LISTLOCATION(location)=1;
       } =1;
       } = 0x20001112;
