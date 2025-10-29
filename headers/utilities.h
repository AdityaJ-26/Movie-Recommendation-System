#ifndef UTILITIES_H
#define UTILITIES_H

#include "user.h"
#include "movie.h"
#include "map.h"

#define MAX_SCORES 50

typedef struct Pref {
    HashMap *actors, *directors, *genres;
}Pref;

typedef struct Score {
    char name[50];
    float score;
}Score;

Pref *initialisePrefMap();
void addTokens(HashMap *, char *);
Pref *getPreferences(User *);
void makePreferences(char *, HashMap *);
void getUserPreferences(User *, Pref *);
float getScore(char *, char *);
void scoreMovies(User *, Score *);
int insertScore(Score *, char *, float);
void printScoreList(Score *);

#endif //UTILITIES_H