const MAXLEN = 255;
const CODELEN = 3;

typedef string name<MAXLEN>;
typedef string code<CODELEN>;
typedef struct final_result final_result_u;
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


struct user_input {
   name city;
   code state;
};


struct final_result {
   struct user_input input_res;
    airport_list list;
};


union list_airport_res switch (int errno) {
case 0:
final_result_u result;  
default:
void;      
};

program AIRPORTPROG {
       version AIRPORTVERS {
           list_airport_res LISTAIRPORT(user_input) = 1;
       } = 1;
} = 0x20001111;

