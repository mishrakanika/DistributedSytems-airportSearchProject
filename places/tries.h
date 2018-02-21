//
// Created by Kanika Mishra on 2/21/18.
//

#include <cstdlib>
#include <string.h>
#include <cstdio>
#include "string.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#ifndef AIRPORTPROJECT_TRIES_H
#define AIRPORTPROJECT_TRIES_H


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//      TRIE DATA STRUCTURE                                                     //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct trieNode {
    char key;
    char *entry;
    double longitude;
    double latitude;

    struct trieNode *parent;
    struct trieNode *children;
    struct trieNode *next;
    struct trieNode *previous;
}trieNode_t;

void trieCreate(trieNode_t **root);
void trieAdd(trieNode_t **root, char *key, double longt, double latt);
trieNode_t* TrieSearch(trieNode_t *root, const char *key);
trieNode_t * createTrieNode(char key, char *entry_name, double longt, double latt);
void TrieAddEntry(trieNode_t **root, char *key, char *entry_name, double longt, double latt);

void createNode(trieNode_t **root){

    *root = createTrieNode('\0',"\0", 0xffffffff,0xffffffff);
}

trieNode_t * createTrieNode(char key, char *entry_name, double longt, double latt)
{
    trieNode_t *node = (trieNode_t *)malloc(sizeof(trieNode_t));

    node->next = NULL;
    node->key = key;
    node->entry = strdup(entry_name);
    node->longitude = longt;
    node->latitude = latt;
    node->previous = NULL;
    node->parent = NULL;
    node->children = NULL;

    return node;
}

void trieAdd(trieNode_t **root, char *key, double longt, double latt)
{
    TrieAddEntry(root, key, key, longt, latt);
}

void TrieAddEntry(trieNode_t **root, char *key, char *entry_name, double lon, double lat)
{
    trieNode_t *pTrav = NULL;

    if(NULL == *root)
    {
        //printf("NULL tree\n");
        return;
    }

    //printf("\nInserting key %s: \n",key);

    pTrav = (*root)->children;

    if(pTrav == NULL)
    {
        /*First Node*/
        for(pTrav = *root; *key; pTrav = pTrav->children)
        {
            pTrav->children = createTrieNode(*key, "\0", 0xffffffff, 0xffffffff);
            pTrav->children->parent = pTrav;
            //printf("Inserting: [%c]\n",pTrav->children->key);

            key++;
        }

        pTrav->children = createTrieNode('\0', entry_name, lon, lat);
        pTrav->children->parent = pTrav;

        //printf("Inserting: [%c]\n",pTrav->children->key);

        return;
    }

    if(TrieSearch(pTrav, key))
    {
        //printf("Duplicate!\n");
        //return;
    }

    while(*key != '\0')
    {
        if(*key == pTrav->key)
        {
            key++;

            //printf("Traversing child: [%c]\n",pTrav->children->key);

            pTrav = pTrav->children;
        }
        else
            break;
    }

    while(pTrav->next)
    {
        if(*key == pTrav->next->key)
        {
            key++;
            TrieAddEntry(&(pTrav->next), key, entry_name, lon, lat);
            return;
        }
        pTrav = pTrav->next;
    }

    if(*key)
    {
        pTrav->next = createTrieNode(*key, "\0", 0xffffffff, 0xffffffff);
    }
    else
    {
        pTrav->next = createTrieNode(*key, entry_name, lon, lat);
    }

    pTrav->next->parent = pTrav->parent;
    pTrav->next->previous = pTrav;


    //printf("Inserting [%c] as neighbour of [%c] \n",pTrav->next->key, pTrav->key);


    if(!(*key))
        return;

    key++;

    for(pTrav = pTrav->next; *key; pTrav = pTrav->children)
    {
        pTrav->children = createTrieNode(*key, "\0", 0xffffffff, 0xffffffff);
        pTrav->children->parent = pTrav;

        //printf("Inserting: [%c]\n",pTrav->children->key);

        key++;
    }

    pTrav->children = createTrieNode('\0', entry_name, lon, lat);
    pTrav->children->parent = pTrav;

    //printf("Inserting: [%c]\n",pTrav->children->key);

}

trieNode_t* TrieSearch(trieNode_t *root, const char *key)
{
    trieNode_t *level = root;
    trieNode_t *pPtr = NULL;

    while(1)
    {
        trieNode_t *found = NULL;
        trieNode_t *curr;

        for (curr = level; curr != NULL; curr = curr->next)
        {
            // printf("Comparing: [%c] with [%c]\n",curr->key, *key);

            if (curr->key == *key)
            {
                //  printf("Found!\n");
                found = curr;

                break;}
        }
        if (found == NULL)
            return NULL;

        if (*key == '\0')
        {
            pPtr = curr;
            return pPtr;
        }

        level = found->children;
        key++;
    }
}


trieNode_t *partialSearch(trieNode_t *root, const char *key){
    trieNode_t *level = root;
    trieNode_t *pPtr = NULL;
    while(1)
    {
        trieNode_t *found = NULL;
        trieNode_t *curr;

        for (curr = level; curr != NULL; curr = curr->next)
        {

            //printf("Comparing: [%c] with [%c]\n",curr->key, *key);
            if (curr->key == *key)
            {
                // printf("Found!\n");
                found = curr;
                //printf("%s", curr->entry);
                break; }
                /* else if will continue to travel down the trie in the case that a partial match with a trie entry is found */
            else if (*key == '\0')
            {
                //printf("Moving along\n");
                found = curr;
                key--;
                break;}
        }
        //printf("%s", curr->entry);
        if (found == NULL)
            return NULL;

        if (*key == '\0')
        {
            pPtr = curr;
            return pPtr;
        }

        level = found->children;
        key++;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                           TRIE DATA STRUCTURE ENDS                                                //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

trieNode_t *root;

struct place {
    char name[255];
    char state[2];
    float latitude;
    float longitude;
};

typedef struct place Place;

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

void verymain(){
    createNode(&root);
    FILE *placesFile;
    char line[255];

    printf("\n BEFORE READING FILE \n");
    placesFile = fopen("/home/st/mishrakanika/airportProject/places/places2k.txt", "r");
    printf("\n after FOPEN \n");

    if(placesFile != NULL){

        while(fgets(line, sizeof(line), placesFile) != NULL){

            char key[255];
            Place *p = parseLine(line);
            // printf("debug1");

            strcpy(key,p->state);
            strcat(key,p->name);

            int i;
            for(i=0; key[i]; i++)
                key[i] = tolower(key[i]);

            trieAdd(&root, key, p->longitude, p->latitude);
            free(p);
            //  printf("debug2");
        }
        fclose(placesFile);
    }

}

#endif //AIRPORTPROJECT_TRIES_H
