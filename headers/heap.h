#ifndef HEAP_H
#define HEAP_H

#define MAX_SCORES 50

typedef struct Score {
    char name[100];
    int score;
}Score;

typedef struct Heap {
    Score *list;
    int size, capacity;
}Heap;

Heap *initialiseHeap(int);
void swap(Score* , Score* );
void insertHeap(Heap *, char *, int);
void heapify(Heap *, int);
void deleteHeap(Heap *);

#endif //HEAP_H