#ifndef UTILITIES_H
#define UTILITIES_H

#include "user.h"
#include "movie.h"
#include "map.h"
#include "heap.h"

typedef struct Pref {
    HashMap *actors, *directors, *genres;
}Pref;

Pref *initialisePrefMap();
void addTokens(HashMap *, char *);
Pref *getPreferences(User *);
void makePreferences(char *, HashMap *);
void getUserPreferences(User *, Pref *);
int getScore(char *, char *, int);
void scoreMovies(User *, Heap *);
void delete(Pref *);
void topK(Heap *, int);

#endif //UTILITIES_H