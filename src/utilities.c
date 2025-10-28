#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "..\headers\utilities.h"

Pref *initialisePrefMap() {
    Pref *map = malloc(sizeof(Pref));
    map->actors = initialiseMap();
    map->directors = initialiseMap();
    map->genres = initialiseMap();
    return map;
}

void addTokens(HashMap *map, char *string) {
    char *saveptr;
    char *tok = strtok_r(string, ",", &saveptr);
    while (tok) {
        insert(map, tok);
        tok = strtok_r(NULL, ",", &saveptr);
    }
}

Pref *getPreferences(User *currUser) {
    Pref *preference = initialisePrefMap();
    FILE *file = fopen(FILENAME, "rb");
    if (!file) {
        printf("Error Opening File");
        return NULL;
    }
    char userList[1000];
    strcpy(userList, currUser->movieList);
    Movies *movie = malloc(sizeof(Movies));
    char *saveptr;
    char *tok = strtok_r(userList, ",", &saveptr);
    while (tok) {
        rewind(file);
        while (fread(movie, sizeof(Movies), 1, file)) {
            if (!strcmpi(movie->name, tok)) {
                addTokens(preference->genres, movie->genre);
                addTokens(preference->actors, movie->actors);
                addTokens(preference->directors, movie->directors);
                break;
            }
        }
        tok = strtok_r(NULL, ",", &saveptr);
    }
    fclose(file);
    free(movie);
    return preference;
}

void makePreferences(char *pref, HashMap *map) {
    int len, maxValue, median;
    median = medianValue(map);
    len = map->length;
    if (len == 0) return;
    maxValue = map->list[len-1]->value;
    for (int i=len-1; i>=0; i--) {
        if (maxValue - map->list[i]->value < median) {
            strcat(pref, map->list[i]->key);
            strcat(pref, ",");
        }
    }
}

void getUserPreferences(User *currUser, Pref *preference) {
    currUser->preferences[0] = '\0';
    makePreferences(currUser->preferences, preference->genres);
    makePreferences(currUser->preferences, preference->actors);
    makePreferences(currUser->preferences, preference->directors);
}

float getScore(char *preference, char *attributes) {
    int nPref = 1, nAtt = 1, intersection = 0, Union, i = 0; 
    while (preference[i] != '\0') {
        if (preference[i] == ',') {
            nPref++;
        }
        i++;
    }i=0;
    while (attributes[i] != '\0') {
        if (attributes[i] == ',') {
            nAtt++;
        }
        i++;
    }
    char tempAtt[500];
    
    char *savePref;
    char *tokPref, *tokAtt;
    tokPref = strtok_r(preference, ",", &savePref);
    while (tokPref) {
        char *saveAtt;
        strcpy(tempAtt, attributes);
        tokAtt = strtok_r(tempAtt, ",", &saveAtt);
        while (tokAtt) {
            if (!strcmp(tokPref, tokAtt)) intersection++;
            tokAtt = strtok_r(NULL, ",", &saveAtt);
        }
        tokPref = strtok_r(NULL, ",", &savePref); 
    }
    
    Union = nPref + nAtt - intersection;
    return ((float)intersection/Union);
}

int insertScore(Score *scoreList, char *name, float score) {
    int i=0;
    while (strcmp(scoreList[i].name, "END")) {
        i++;
    }
    if (i > MAX_SCORES-2) return 0;
    strcpy(scoreList[i].name, name);
    scoreList[i].score = score;
    strcpy(scoreList[i+1].name, "END");
    return 1;
}

void scoreMovies(User *currUser, Score *scoreList) {
    FILE *file = fopen(FILENAME, "rb");
    if (!file) {
        printf("Error Opening File\n");
        return;
    }
    
    char attributes[500];
    char tempPref[500];
    
    Movies *movie = malloc(sizeof(Movies));
    while (fread(movie, sizeof(Movies), 1, file)) {
        strcpy(tempPref, currUser->preferences);
        strcat(tempPref, "\0");
        attributes[0] = '\0';
        strcat(attributes, movie->genre);
        strcat(attributes, ",");
        strcat(attributes, movie->actors);
        strcat(attributes, ",");
        strcat(attributes, movie->directors);
        strcat(attributes, "\0");
        if (!insertScore(scoreList, movie->name, getScore(tempPref, attributes))) break;
    }
}

void printScoreList(Score *scoreList) {
    for (int i=0; strcmp(scoreList[i].name, "END"); i++) {
        printf("%s - %f\n", scoreList[i].name, scoreList[i].score);
    }
}

// int main() {
//     User *user = getUserData();
//     Pref *preference = getPreferences(user);
//     Score *scoreList = malloc(sizeof(Score)*MAX_SCORES);
//     strcpy(scoreList[0].name, "END");
//     scoreMovies(user, scoreList);
//     // getUserPreferences(user, preference);
//     // storeUser(user);
//     printUser(user);
//     printScoreList(scoreList);

    
//     free(user);
//     free(preference->genres);
//     free(preference->actors);
//     free(preference->directors);
//     free(preference);
//     return 0;
// }