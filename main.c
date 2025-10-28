#include <stdio.h>
#include <stdlib.h>
#include "headers\user.h"
#include "headers\map.h"

int main() {
    User *newUser = newUserSet();
    addWatched(newUser);
    store(newUser);
    free(newUser);
    User *temp = getUserData();
    printf("%s", temp->movieList);
}