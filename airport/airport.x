const MAXLEN = 255;
const CODELEN = 3;
typedef string name<MAXLEN>;
typedef string code<CODELEN>;
typedef struct coordinates location;
typedef struct airport_info *airport_list;

struct airport_info {
code airport_code; 
  name city;
   code state;
   double distance;
   airport_list next;
};

struct coordinates {
   double latitude;
   double  longitude;
};


union list_location_res switch (int errno) {
case 0:
struct airport_info list_location_res;  
default:
void;  };

program LOCATIONPROG
       {
               version LOCATIONVER
       {
           list_location_res LISTLOCATION(location)=1;
       } =1;
       } = 0x20001112;

