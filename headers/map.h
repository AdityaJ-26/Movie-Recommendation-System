#ifndef MAP_H
#define MAP_H

typedef struct Pair {
    char key[100];
    int value;
}Pair;

typedef struct HashMap {
    Pair **list;
    int capacity, length;
}HashMap;

Pair *newPair(char *);
HashMap *initialiseMap();
void insert(HashMap *, char *);
void sortMap(HashMap *, int);   //1 = ascending | 0 = descending
void printMap(HashMap *);
int medianValue(HashMap *);
int getKeyValue(HashMap *, char *);

#endif //MAP_H