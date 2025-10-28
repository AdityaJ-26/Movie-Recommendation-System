#ifndef USER_H
#define USER_H
#include "map.h"

typedef struct User {
    int id;
    char password[9];
    char movieList[1000];
    char preferences[1000];
}User;

User *newUser();
// int login();
void storeUser(User *);
void addWatched(User *);
User *getUserData();
void printUser(User *);

#endif //USER_H