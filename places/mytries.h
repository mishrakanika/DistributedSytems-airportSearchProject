//
// Created by Kanika Mishra on 2/23/18.
//
#include "places.h"
#include "string.h"


#ifndef DISTRIBUTEDSYTEMS_AIRPORTSEARCHPROJECT_MYTRIES_H
#define DISTRIBUTEDSYTEMS_AIRPORTSEARCHPROJECT_MYTRIES_H
typedef struct trienode trienode;
typedef struct cityData cityData;
typedef struct autoCompleteReply autoCompleteReply;

bool autoComplete(trienode *, char *, int, coordinates *latlong);


struct place {
    char name[255];
    char state[2];
    float latitude;
    float longitude;
};

typedef struct place Place;

struct trienode
{
    struct trienode *children[256];
    char data;
    coordinates latlong;
    bool isWordEnd;
};

struct cityData
{
    int err;
    name city;
    coordinates latlong;
};

char *trimSpaces(char *str)
{
    char *endl;

    while(isspace(*str))
        str++;

    endl = str + strlen(str) - 1;
    while(endl > str && isspace(*endl)) endl--;

    *(endl+1) = 0;

    return str;
}

trienode* root;

//adding to trie structure
void addToTrie(name input , coordinates latlong ) {
    trienode *curr;
    int length, i, childrenIndex;
    length = strlen(input);
    char ch;
    curr = root;
    for (i = 0; i < length; i++) {
        ch = *input;
        childrenIndex = ch;
        if (curr->children[childrenIndex] == NULL) {
            curr->children[childrenIndex] = new trienode();
        }

        curr = curr->children[childrenIndex];
        curr->data = ch;
        input++;
    }
    if (*input == '\0') {
        curr->isWordEnd = true;
        curr->latlong.latitude = latlong.latitude;
        curr->latlong.longitude = latlong.longitude;
    }

}

//search for city even if it is incomplete or reject for ambiguous city name
 cityData trieSearch(name searchStr)
 {
     trienode *curr;
     cityData result;
     int i=0;
     char ch;
     char city_name[MAXLEN];
     int childrenIndex;
     curr = root;

     while(*searchStr != '\0') {
         ch = *searchStr;
         childrenIndex = ch;
         if(curr->children[childrenIndex] != NULL)
         {
             curr = curr->children[childrenIndex];
             city_name[i] = ch;
             searchStr++;
             i++;
         } else {
             result.err = 1;
             return result;
         }
     }

     if(*searchStr == '\0')
     {
         if(curr->isWordEnd == true)
         {
             city_name[i] = '\0';
             result.city = strdup(city_name);
             result.latlong.longitude = curr->latlong.longitude;
             result.latlong.latitude = curr->latlong.latitude;
             result.err = 0;
             return result;
         }
         else
         {
             coordinates searchedlatlong;
             bool isAmbig = autoComplete(curr, city_name, i, &searchedlatlong);
             if(isAmbig)
             {
                 result.err = 7;
                 return result;
             }
             else
             {

                 result.city = strdup(city_name);
                 result.latlong.longitude = searchedlatlong.longitude;
                 result.latlong.latitude = searchedlatlong.latitude;
                 result.err = 0;
                 return result;
             }
         }

     }

 }

//given an incomplete city name, it tries to find the closest match
bool autoComplete(trienode *curr, char *city_name, int charCount, coordinates *latlong) {
    int index,count;
    index = count = 0;
    for (int j = 0; j < 256; j++) {
        if (curr->children[j] != NULL) {
            index = j;
            count++;
        }
    }
    if (count > 1) {
        return true;
    } else {
        curr = curr->children[index];
        city_name[charCount] = curr->data;
        charCount++;
    }

    if (curr->isWordEnd == true) {
        city_name[charCount] = '\0';
        latlong->latitude = curr->latlong.latitude;
        latlong->longitude = curr->latlong.longitude;
        return false;
    }
    return autoComplete(curr, city_name, charCount, latlong);
}

//parsing the data file line by line
Place *  parseLine(char * line){

    Place *p = (Place *)malloc(sizeof *p);
    char * temp = (char *)malloc(sizeof *temp);

    strncpy(p->name, line+9, 64); // name
    strncpy(p->name, trimSpaces(p->name), strlen(p->name)); // trimming spaces

    strncpy(p->state, line, 2);   // state

    strncpy(temp, line+143, 10);
    p->latitude = atof(temp);     // latitude

    strncpy(temp, line+153, 11);  // longitude
    p->longitude = atof(temp);

    return p;
};


// load the internal trie data structure based on data file. Assumes data file
// is called places2k.txt and is in same directory as places_server
void loadtrie(){
    FILE *placesFile;
    char line[255];


    placesFile = fopen("./places2k.txt", "r");

    if (root == NULL) {
    root = new trienode();
    if(placesFile != NULL){

        while(fgets(line, sizeof(line), placesFile) != NULL){

            char key[255];
            Place *p = parseLine(line);
            // printf("debug1");

            memset(key, 0, 256);

            strncpy(key,p->state, 2);
            strcat(key,p->name);

            int i;
            for(i=0; key[i]; i++)
                key[i] = tolower(key[i]);

            coordinates latlong;
            latlong.latitude = p->latitude;
            latlong.longitude = p->longitude;
            addToTrie(key, latlong);
            free(p);
            //  printf("debug2");
        }
        fclose(placesFile);
    }
    }
}





#endif //DISTRIBUTEDSYTEMS_AIRPORTSEARCHPROJECT_MYTRIES_H
