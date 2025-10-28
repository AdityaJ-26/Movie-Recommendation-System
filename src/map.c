#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "..\headers\map.h"

Pair *newPair(char *key) {
    Pair *this = malloc(sizeof(Pair));
    strcpy(this->key, key) ;
    this->value = 1;
    return this;
}

HashMap *initialiseMap() {
    HashMap *this = malloc(sizeof(HashMap));
    this->capacity = 100;
    this->length = 0;
    this->list = (Pair **)calloc(this->capacity, sizeof(Pair *));
    return this;
}

void insert(HashMap *map, char *key) {
    if (map->length == map->capacity) return;   
    for (int i=0; i<map->length; i++) {
        if (!strcmp(map->list[i]->key, key)) {
            map->list[i]->value++;
            return;
        }
    }
    map->list[map->length] = newPair(key);
    map->length++;
}

void sortMap(HashMap *map, int order) {
    if (map->length == 0 || map->length == 1) return;

    if (order == -1) {
        for (int i=0; i<map->length-1; i++) {
            for (int j=i+1; j<map->length; j++) {
                if (map->list[i]->value < map->list[j]->value) {
                    Pair *temp = map->list[i];
                    map->list[i] = map->list[j];
                    map->list[j] = temp;
                }
            }
        }
    }
    else if (order == 1) {
        for (int i=0; i<map->length-1; i++) {
            for (int j=i+1; j<map->length; j++) {
                if (map->list[i]->value > map->list[j]->value) {
                    Pair *temp = map->list[i];
                    map->list[i] = map->list[j];
                    map->list[j] = temp;
                }
            }
        }    
    }
    else {
        return;
    }
}

void printMap(HashMap *map) {
    for (int i=0; i<map->length; i++) {
        printf("[%s : %d]\n", map->list[i]->key, map->list[i]->value);
    }
}

int medianValue(HashMap *map) {
    sortMap(map, 1);
    int len = map->length, median;
    if (len%2 != 0) {
        median = map->list[(len)/2]->value;
    }  
    else {
        median = ((map->list[len/2]->value) + (map->list[len/2-1]->value)) / 2;
    }
    return median;
}

int getKeyValue(HashMap *map, char *k) {
    for (int i=0; i<map->length; i++) {
        if (!strcmp(map->list[i]->key, k)) {
            return map->list[i]->value;
        }
    }
    return 0;
}

// int main() {
//     HashMap *demo = initialiseMap();
//     insert(demo, "A");
//     insert(demo, "B");
//     insert(demo, "A");
//     insert(demo, "C");
//     insert(demo, "D");
//     insert(demo, "D");
//     insert(demo, "D");
//     insert(demo, "E");
//     insert(demo, "F");
//     insert(demo, "E");
//     insert(demo, "D");
//     sortMap(demo, 1);
//     printMap(demo);
//     printf("Median : %d", medianValue(demo));
// }
