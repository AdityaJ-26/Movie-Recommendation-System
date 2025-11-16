#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "..\headers\movie.h"

Movies *initialiseMovie() {
    Movies *movie = (Movies *)malloc(sizeof(Movies));
    return movie;
}

void enter(Movies *movie){
    char str[200];

    printf("NAME: ");
    scanf("%99[^\n]", str);
    strcpy(movie->name, str);

    printf("RATING: ");
    scanf("%f", &(movie->rating));
    getchar();

    printf("GENRE: ");
    scanf("%99[^\n]", str);
    strcpy(movie->genre, str);
    getchar();

    printf("ACTORS: ");
    scanf("%200[^\n]", str);
    strcpy(movie->actors, str);
    getchar();
    
    printf("DIRECTORS: ");
    scanf("%100[^\n]", str);
    strcpy(movie->directors, str);
    getchar();
}

void storeMovie(Movies *movie) {
    FILE *file = fopen(FILENAME, "ab");
    if (!file) {
        printf("ERROR IN FILE");
        return;
    }
    if (fwrite(movie, sizeof(Movies), 1, file)) {
        printf("Added\n\n");
    }
    else printf("Not Added\n\n");
    fclose(file);
}

void printMovie(Movies *movie) {
    printf("NAME: %s\n", movie->name);
    printf("RATING: %1.1f\n", movie->rating);
    printf("GENRE: %s\n", movie->genre);
    printf("ACTORS: %s\n", movie->actors);
    printf("DIRECTORS: %s\n", movie->directors);
    printf("\n\n");
    return;
}

// int main() {
//     Movies *movie = initialiseMovie();
//     enter(movie);
//     storeMovie(movie);
//     system("cls");
//     file = fopen(FILENAME, "rb");
//     while (fread(movie, sizeof(Movies), 1, file)) {
//         printMovie(movie);
//     }
//     return 0;
// }