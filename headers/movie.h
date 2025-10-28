#ifndef MOVIE_H
#define MOVIE_H

#define FILENAME "..\\data\\moviesData.dat"

typedef struct Movies {
    char name[100];
    float rating;
    char genre[100], actors[200], directors[100];
}Movies;

Movies *initialiseMovie();
void enter(Movies *);
void storeMovie(Movies *, FILE *);
Movies *retrieve(FILE *);
void printMovie(Movies *);

#endif //MOVIE_H