#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "..\headers\heap.h"

void swap(Score *a, Score *b) {
    Score temp = *a;
    *a = *b;
    *b = temp;
}

Heap *initialiseHeap(int capacity) {
    Heap *new = malloc(sizeof(Heap));
    new->size = 0;
    new->capacity = capacity;
    new->list = calloc(capacity, sizeof(Score));
    return new;
}

void insertHeap(Heap *h, char *name, int score) {
    Score temp;
    temp.score = score;
    strcpy(temp.name, name);
    if (h->size >= h->capacity) {
        return;
    }
    int i = h->size;
    while (i != 0 && score < h->list[(i-1)/2].score) {
        h->list[i] = h->list[(i-1)/2];
        i = (i-1)/2;
    }
    h->list[i] = temp;
    h->size++;
}

void heapify(Heap *h, int i) {
    while (1) {
        int minIndex = i, left = i*2+1, right = i*2+2;
        if (left < h->size && h->list[left].score < h->list[minIndex].score) {
            minIndex = left;
        }
        if (right < h->size && h->list[right].score < h->list[minIndex].score) {
            minIndex = (right);
        }
        if (minIndex != i) {
            swap(h->list+minIndex, h->list+i);
        }
        else {
            break;
        }
        i = minIndex;
    }
}

void deleteHeap(Heap *h) {
    if (h == NULL || h->size == 0) return;
    h->size--;
    swap(h->list, h->list+h->size);
    heapify(h, 0);
}

// int main() {
//     Heap *h = initialiseHeap(20);
//     insertHeap(h, "The Dark Knight", 95);
//     insertHeap(h, "Hera Pheri", 100);
//     insertHeap(h, "Phir Hera Pheri", 100);
//     insertHeap(h, "3 Idiots", 90);
//     insertHeap(h, "Sardar Udham", 97);
//     printf("\n");
//     int i = h->size;
//     while (h->size) {
//         deleteHeap(h);
//     }
//     for (int j=0; j<i; j++) {
//         printf("%s %d", h->list[j].name, h->list[j].score);
//     }
//     return 0;
// }