/* Implementation of Map abstract data type */

#include "Map.h"
#include <string.h>
#include <stdlib.h>


struct map {
   // you must define this struct
   //list of streets
   StreetList theList;
   //name of map
   char mapName[16];
};

Map createMap(const char *name) {
    //create new map
    Map m = (Map) malloc(sizeof(Map));
    if(!m) return NULL;
    //check if name too long
    if(strlen(name) > 15) return NULL;
    //create streetList
    m->theList.head = NULL;
    m->theList.tail = NULL;
    //copy name
    strcpy(m->mapName, name);
    return m;
}

const char *mapName(Map m) {
    return m->mapName;
}

/* add a new street to Map */
/* return 1 to acknowledge that street has been added */
/* return 0 if error (see spec) */
int mapAddStreet(Map m, Street * s) {
    //create new street node
    StreetNode *new = malloc(sizeof(StreetNode));
    new->street = s;
    new->next = NULL;
    //create street node pointer
    StreetNode *p = m->theList.head;
    //check if list is empty
    if(!p){
        m->theList.head = new;
        m->theList.tail = new;
        return 1;
    }
    while(p != NULL){
        //check if street name already exists
        if(strcmp(p->street->name, s->name) == 0){
            return 0;
        }
        //check if overlaps
        if(streetDirection(p->street) == streetDirection(s)){
            //check if north to south
            if(streetDirection(p->street)){
                //check if overlap
                //if same east coordinate
                if(p->street->start.east == s->start.east){
                    //determine which street is more north to check which start/ends of streets overlap
                    //street p is more north than street s
                    if(p->street->start.north > s->start.north){
                        //check if overlap
                        if(p->street->end.north < s->start.north)
                            return 0;
                    }
                    //street s is more north than street p
                    else{
                        //check if overlap
                        if(p->street->start.north > s->end.north)
                            return 0;
                    }
                }
            }
            //check if west to east
            else{
                //check if overlap
                if(p->street->start.north == s->start.north){
                    //determine which street is more west to check which start/ends of streets overlap
                    //street p is more west than street s
                    if(p->street->start.east < s->start.east){
                        //check if overlap
                        if(p->street->end.east > s->start.east)
                            return 0;
                    }
                    //street s is more west than street p
                    else{
                        //check if overlap
                        if(p->street->start.east < s->end.east)
                            return 0;
                    }

                }
            }
        }
        p = p->next;
    }
    //append to end of list
    StreetNode *tail = m->theList.tail;
    if(tail) tail->next = new;
    else {
        m->theList.head = new;
    }
    m->theList.tail = new;
    return 1;
}

/* create and return a list of all streets in the map */
/* must be sorted alphabetically by name */
/* must create a new list -- may be deallocated by caller */
StreetList * mapAllStreets(Map m) {
    //create new list
    StreetList *newList = malloc(sizeof(StreetList));
    newList->head = NULL;
    newList->tail = NULL;
    StreetNode *p = m->theList.head;
    int count = 0;
    while(p != NULL){
        count++;
        p = p->next;
    }
    //reset pointer
    p = m->theList.head;
    //create array of street nodes
    StreetNode arrayList[count];
    for(int i = 0; i < count; i++){
        arrayList[i] = *p;
        p = p->next;
    }
    //selection sort to sort alphabetically
    for(int i = 0; i < count; i++){
        int current = i;
        int smallest = i;
        for(int j = i + 1; j < count; j++){
            if(strcmp(arrayList[j].street->name, arrayList[smallest].street->name) < 0){
                smallest = j;
            }
        }
        //swap
        if(current != smallest){
            //swap street nodes
            StreetNode temp = arrayList[current];
            arrayList[current] = arrayList[smallest];
            arrayList[smallest] = temp;
        }

    }
    //append to new list
    for(int i = 0; i < count; i++){
        StreetNode *newNode = malloc(sizeof(StreetNode));
        newNode->street = arrayList[i].street;
        newNode->next = NULL;
        StreetNode *t = newList->tail;
        //appending to new street
        if(t) t->next = newNode;
        //if appending first node
        else newList->head = newNode;
        newList->tail = newNode;
    }
    return newList;
}

/* return a list of all north-south streets */
/* must be sorted west to east, then by name */
/* must create a new list -- may be deallocated by caller */
StreetList * mapNSStreets(Map m) {
    //create new list
    StreetList *newListNS = malloc(sizeof(StreetList));
    newListNS->head = NULL;
    newListNS->tail = NULL;
    //create pointer
    StreetNode *p = m->theList.head;
    int count = 0;
    //count number of north south streets
    while(p != NULL){
        if(streetDirection(p->street)){
            count++;
        }
        p = p->next;
    }
    //create array of street nodes
    //reset pointer
    p = m->theList.head;
    //create array of street nodes
    StreetNode arrayList[count];
    int i = 0;
    //add nodes ot arrayList
    while(p != NULL){
        if(streetDirection(p->street)){
            arrayList[i] = *p;
            i++;
        }
        p = p->next;
    }
    //sort list
    for(i = 0; i < count; i++){
        int current = i;
        int smallest = i;
        for(int j = i + 1; j < count; j++){
            if(arrayList[j].street->start.east < arrayList[smallest].street->start.east){
                smallest = j;
            }
            else if(arrayList[j].street->start.east == arrayList[smallest].street->start.east && strcmp(arrayList[j].street->name, arrayList[smallest].street->name) < 0){
                smallest = j;
            }
            else{
                continue;
            }
        }
        //swap
        if(current != smallest){
            //swap street nodes
            StreetNode temp = arrayList[current];
            arrayList[current] = arrayList[smallest];
            arrayList[smallest] = temp;
        }
    }
    //append to new list
    for(i = 0; i < count; i++){
        StreetNode *newNode = malloc(sizeof(StreetNode));
        newNode->street = arrayList[i].street;
        newNode->next = NULL;
        StreetNode *t = newListNS->tail;
        //appending to new street
        if(t) t->next = newNode;
            //if appending first node
        else newListNS->head = newNode;
        newListNS->tail = newNode;
    }
    return newListNS;
}

/* return a list of all east-west streets */
/* most be sorted from north to south, then by name */
/* must create a new list -- may be deallocated by caller */
StreetList * mapWEStreets(Map m) {
    //create new list
    StreetList *newListWE = malloc(sizeof(StreetList));
    newListWE->head = NULL;
    newListWE->tail = NULL;
    //create pointer
    StreetNode *p = m->theList.head;
    int count = 0;
    //count number of west east streets
    while(p != NULL){
        if(!streetDirection(p->street)){
            count++;
        }
        p = p->next;
    }
    //create array of street nodes
    //reset pointer
    p = m->theList.head;
    //create array of street nodes
    StreetNode arrayList[count];
    int i = 0;
    //add nodes ot arrayList
    while(p != NULL){
        if(!streetDirection(p->street)){
            arrayList[i] = *p;
            i++;
        }
        p = p->next;
    }
    //sort list
    for(i = 0; i < count; i++){
        int current = i;
        int smallest = i;
        for(int j = i + 1; j < count; j++){
            if(arrayList[j].street->start.north > arrayList[smallest].street->start.north){
                smallest = j;
            }
            else if(arrayList[j].street->start.north == arrayList[smallest].street->start.north && strcmp(arrayList[j].street->name, arrayList[smallest].street->name) < 0){
                smallest = j;
            }
            else{
                continue;
            }
        }
        //swap
        if(current != smallest){
            //swap street nodes
            StreetNode temp = arrayList[current];
            arrayList[current] = arrayList[smallest];
            arrayList[smallest] = temp;
        }
    }
    //append to new list
    for(i = 0; i < count; i++){
        StreetNode *newNode = malloc(sizeof(StreetNode));
        newNode->street = arrayList[i].street;
        newNode->next = NULL;
        StreetNode *t = newListWE->tail;
        //appending to new street
        if(t) t->next = newNode;
            //if appending first node
        else newListWE->head = newNode;
        newListWE->tail = newNode;
    }
    return newListWE;
}

/* find street by name */
/* does not create a new street, just returns a pointer */
/* returns NULL if street not in map */
Street * mapFindStreet(Map m, const char *name) {
    //create streetNode pointer
    StreetNode *p = m->theList.head;
    //go through streetList until street name is found
    while(p != NULL){
        if(strcmp(p->street->name, name) == 0){
            return p->street;
        }
        p = p->next;
    }

    return NULL;
}

/* return a list of streets that intersect with given street */
/* sorted by west-to-east or north-to-south, depending on direction of street */
/* must create a new list -- may be deallocated by caller */
StreetList * mapCrossStreets(Map m, const Street *s) {
    //create new list
    StreetList *newListCross = malloc(sizeof(StreetList));
    newListCross->head = NULL;
    newListCross->tail = NULL;
    //create pointer
    StreetNode *p = m->theList.head;
    //count number of cross streets though s
    int count = 0;
    //go through streetList
    while(p != NULL){
        //check if not same street name
        if(strcmp(s->name, p->street->name) != 0){
            //check if s is north south
            if (streetDirection(s)) {
                //check if street is west east
                if (!streetDirection(p->street)) {
                    //check if cross
                    //p north coordinate in between start and end of s
                    if (p->street->start.north <= s->start.north && p->street->start.north >= s->end.north) {
                            //check if s is between start and end of p
                           if(s->start.east >= p->street->start.east && s->start.east <= p->street->end.east){
                               count++;
                           }
                    }
                }
            }
            //check if s street is west east
            else {
                //check if street is north south
                if (streetDirection(p->street)) {
                    //check if cross
                    //p north coordinate in between start and end of s
                    if (p->street->start.east >= s->start.east && p->street->start.east <= s->end.east) {
                        if(s->start.north <= p->street->start.north && s->start.north >= p->street->end.north){
                            count++;
                        }
                    }
                }
            }
        }
        p = p->next;
    }
    //create array of street nodes
    //reset pointer
    p = m->theList.head;
    //create array of street nodes
    StreetNode arrayList[count];
    int i = 0;
    //add nodes to arrayList
    while(p != NULL){
        //s is north south
        if (streetDirection(s)) {
            //check if p is west east
            if (!streetDirection(p->street)) {
                //check if cross
                //p north coordinate in between start and end of s
                if (p->street->start.north <= s->start.north && p->street->start.north >= s->end.north) {
                    //check if s is between start and end of p
                    if(s->start.east >= p->street->start.east && s->start.east <= p->street->end.east){
                        arrayList[i] = *p;
                        i++;
                    }
                }
            }
        }
        //s is west east
        else {
            //check if p is north south
            if (streetDirection(p->street)) {
                //check if cross
                //p north coordinate in between start and end of s
                if (p->street->start.east >= s->start.east && p->street->start.east <= s->end.east) {
                    //check if s is between start and end of p
                    if(s->start.north <= p->street->start.north && s->start.north >= p->street->end.north){
                        arrayList[i] = *p;
                        i++;
                    }
                }
            }
        }
        p = p->next;
    }
    //sort list
    for(i = 0; i < count; i++){
        int current = i;
        int smallest = i;
        for(int j = i + 1; j < count; j++){
            //s is north south
            if(streetDirection(s)){
                if(arrayList[j].street->start.north > arrayList[smallest].street->start.north){
                    smallest = j;
                }
                else if(arrayList[j].street->start.north == arrayList[smallest].street->start.north && strcmp(arrayList[j].street->name, arrayList[smallest].street->name) < 0){
                    smallest = j;
                }
                else{
                    continue;
                }
            }
            //s is west east
            else{
                if(arrayList[j].street->start.east < arrayList[smallest].street->start.east){
                    smallest = j;
                }
                else if(arrayList[j].street->start.east == arrayList[smallest].street->start.east && strcmp(arrayList[j].street->name, arrayList[smallest].street->name) < 0){
                    smallest = j;
                }
                else{
                    continue;
                }
            }
        }
        //swap
        if(current != smallest){
            //swap street nodes
            StreetNode temp = arrayList[current];
            arrayList[current] = arrayList[smallest];
            arrayList[smallest] = temp;
        }
    }
    //append to new list
    for(i = 0; i < count; i++){
        StreetNode *newNode = malloc(sizeof(StreetNode));
        newNode->street = arrayList[i].street;
        newNode->next = NULL;
        StreetNode *t = newListCross->tail;
        //appending to new street
        if(t) t->next = newNode;
        //if appending first node
        else newListCross->head = newNode;
        newListCross->tail = newNode;
    }
    return newListCross;
}
