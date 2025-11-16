#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "..\headers\user.h"

User *newUser() {    
    int id = rand()%100;
    char pass[9];
    printf("Your User ID is : %d\n", id);
    printf("Enter Password(max 8 characters) :");
    getchar();
    scanf("%8[^\n]", pass);
    getchar();

    User *this = (User *)malloc(sizeof(User));
    if (this == NULL) {
        printf("Error Creating User\n");
        return NULL;
    }
    printf("New User Created Successfully\n");
    this->id = id;
    strcpy(this->password, pass);
    this->movieList[0] = '\0';
    this->preferences[0] = '\0';
    return this;
}

void addWatched(User *currUser) {
    char name[100];
    printf("Enter Movie Name: ");
    getchar();
    while (1) {

        scanf("%99[^\n]", name);
        getchar();
        if (!strcmpi(name, "exit")) {
            break;
        }

        strcat(currUser->movieList, name);
        strcat(currUser->movieList, ",");
        printf("Movie Added to Your List \n");
        printf("Enter Movie Name or 'exit' to Exit: ");
    }
    currUser->movieList[sizeof(currUser->movieList)-1] = '\0';
}

void storeUser(User *currUser) {
    char fileName[20];
    sprintf(fileName, "data\\%d.dat", currUser->id);

    FILE *file = fopen(fileName, "wb");
    if (!file) {
        printf("Error Opening File Data\n\n");
        return;
    }

    if (fwrite(currUser, sizeof(User), 1, file));
    else {
        printf("Error Storing User Data\n\n");
    }

    fclose(file);
}

User *getUserData() {
    int id;
    printf("Enter ID: ");
    scanf("%d", &id);

    char fileName[20];
    sprintf(fileName, "data\\%d.dat", id);

    FILE *file = fopen(fileName, "rb");
    if (!file) {
        printf("Error Accessing User Data\n\n");
        return NULL;
    }

    User *user = (User *)malloc(sizeof(User));
    fread(user, sizeof(User), 1, file);

    char pass[9];
    getchar();
    printf("Enter Password: ");
    scanf("%8[^\n]", pass);
    getchar();

    fclose(file);
    if (strcmp(pass, user->password)) {
        printf("Wrong Password\n\nExiting\n\n");
        free(user);
        return NULL;
    }
    else {
        return user;
    }
}

void printUserMovies(User *currUser) {
    int i=0;
    printf("Movie List: | ");
    while (currUser->movieList[i] != '\0') {
        if (currUser->movieList[i] == ',') {
            printf(" | ");
        }
        else {
            printf("%c", currUser->movieList[i]);
        }
        i++;
    }
    printf("\n");
}

void printUser(User *currUser) {
    int i=0;
    printf("User ID: %d\n", currUser->id);
    printf("Movie List: | ");
    while (currUser->movieList[i] != '\0') {
        if (currUser->movieList[i] == ',') {
            printf(" | ");
        }
        else {
            printf("%c", currUser->movieList[i]);
        }
        i++;
    }
    i=0;
    printf("\n");
    printf("User Preferences: | ");
    while (currUser->preferences[i] != '\0') {
        if (currUser->preferences[i] == ',') {
            printf(" | ");
        }
        else {
            printf("%c", currUser->preferences[i]);
        }
        i++;
    }
    printf("\n\n");
}

// int main() {
//     User *demo = newUser();
//     storeUser(demo);
//     free(demo);
//     demo = getUserData();
//     addWatched(demo);
//     storeUser(demo);
//     free(demo);
//     demo = getUserData();
//     printUser(demo);
// }