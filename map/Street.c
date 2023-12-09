
#include "Street.h"
#include <stdlib.h>
#include <string.h>

/* create a new street and initialize */
/* returns pointer to newly-allocated struct street */
/* returns null if error: (a) name too long, (b) points in wrong order */
Street * newStreet(const char *name, const Point * start, const Point *end) {
    Street *new = malloc(sizeof(Street));
    //check name length
    if (strlen(name) > 15) {
        return NULL;
    }
    strcpy(new->name, name);
    //check points if all positive
    if (start->east < 0 || start->north < 0 || end->east < 0 || end->north < 0) {
        return NULL;
    }
    //check points if in order
    if (start->east > end->east || start->north < end->north) {
        return NULL;
    }
    new->start = *start;
    new->end = *end;
    return new;
}

/* returns the distance from start to end */
int streetLength(const Street *s) {
    //check direction
    //North to South
    if(streetDirection(s)){
        return s->start.north - s->end.north;
    }
    //West to East
    else{
        return s->end.east - s->start.east;
    }
}

/* returns a literal string that gives the direction of a street */
/* 0 for west-to-east, 1 for north-to-south */
/* note: west-to-east is the same as east-to-west, and ditto for north-south */
int streetDirection(const Street *s) {
    //North to South
    if(s->start.east == s->end.east){
        return 1;
    }
    //West to East
    else{
        return 0;
    }
}

