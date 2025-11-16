#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "headers\user.h"
#include "headers\map.h"
#include "headers\heap.h"
#include "headers\movie.h"
#include "headers\utilities.h"

#define DEFAULT_K 10


void login(User **user) {
    if (*user != NULL) {
        free(*user);
        user = NULL;
    }
    *user = getUserData();
    if (*user == NULL) {
        return;
    }
    else {
        printf("User Logged Successfully\n");
    }
}

void userCheck(User **user) {
    if (*user == NULL) {
        printf("Login Before Adding\n");
        login(user);
        if (*user == NULL) return;
    }
}

void addWatchedMovies(User **user) {
    userCheck(user);
    addWatched(*user);
}

void displayRecommendation(User *user) {
    Pref *pref = getPreferences(user);
    if (pref == NULL) return;
    getUserPreferences(user, pref);
    storeUser(user);
    Heap *scoreList = initialiseHeap(100);
    scoreMovies(user, scoreList);
    topK(scoreList, DEFAULT_K);
    delete(pref);
}

void deleteUser(User **user) {
    if (*user == NULL) {
        printf("No User Logged In\nLogin To Proceed\n");
        return;
    }
    char str[20];
    printf("Do You Want to Delete User [ID: %d] (Enter yes/no): ", (*user)->id);
    scanf("%s", str);
    getchar();
    if (!strcmpi(str, "no")) return;
    printf("Enter Password: ");
    scanf("%8[^\n]", str);
    getchar();
    if (strcmp((*user)->password, str)) {
        printf("Wrong Password\n");
        return;
    }
    sprintf(str, "data\\%d.dat", (*user)->id);
    if (!remove(str)) {
        printf("Deleted User [ID: %d]\n", (*user)->id);
        *user = NULL;
    }
    else {
        printf("Error Deleting User\n");
    }
}

int main() {
    int choice;
    srand(time(0));
    User *user = NULL;
    do {
        system("cls");
        printf("--------------MENU--------------\n");
        printf("1.Register New User\n");
        printf("2.Login User\n");
        printf("3.Logout Current User\n");
        printf("4.Delete User\n");
        printf("5.Add New Movies\n");
        printf("6.Show User Movies\n");
        printf("7.Recommendation Generation\n");
        printf("0.Exit\n");
        printf("Enter Your Choice: ");
        scanf("%d", &choice);
        printf("\n");

        switch (choice) {
            case 1:
                user = newUser();
                if (user != NULL) storeUser(user);
                break;
            case 2:
                login(&user);
                break;
            case 3:
                free(user);
                user = NULL;
                break;
            case 4:
                int id = user->id;
                deleteUser(&user);
                break;
            case 5:
                addWatchedMovies(&user); 
                break;
            case 6:
                userCheck(&user);
                if (user != NULL) printUserMovies(user);
                getchar();
                break;
            case 7:
                userCheck(&user);
                if (user != NULL) displayRecommendation(user);
                else printf("Error Generating Recommendations\n");
                getchar();
                break;
            case 0:
                getchar();
                break;
            default:
                printf("Invalid Choice!\nEnter Again\n");
        }
        if (choice == 0) {
            printf("Exiting...\n");
        }
        printf("\nPress Enter to Continue....");
        getchar();
    } while (choice != 0); 

    free(user);
    return 0;
}