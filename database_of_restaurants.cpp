
#include "imports.h"
#include "database_of_restaurants.h"
#include "restaurant_list.h"
#include "review_list.h"
#include "menu_list.h"
#include "functions.h"
#include "work_with_all_lists.h"


int main(char **argc, int argv) {
    char vstup[20];
    getStringInputUntilNewline(vstup, sizeof(vstup));
    printf("%s", vstup);
    scanf("%s", vstup);
    char restaurantDataFilePath[200] = "I:/Git/restaurant.txt";
    char reviewDataFilePath[200] = "I:/Git/review.txt";
    char menuDataFilePath[200] = "I:/Git/menu.txt";

    if (checkForceEmpyDBCreation(argc, argv, restaurantDataFilePath, reviewDataFilePath, menuDataFilePath) == ERR) {
        printf("Empty DB recreation failed, please create these files manually. Or move the program somewhere else.\n");
        printInfoExpectedFiles(restaurantDataFilePath, reviewDataFilePath, menuDataFilePath);
        return 0;}

    RESTAURANT_LIST* restaurants = NULL;
    REVIEW_LIST* reviews = NULL;
    MENU_LIST* menus = NULL;
    if (initializeAllLinkedLists(&restaurants, &reviews, &menus) == ERR)
        return 0;
    if (loadFromFileAllLinkedLists(restaurants, reviews, menus, restaurantDataFilePath, reviewDataFilePath, menuDataFilePath) == ERR) {
        printInfoExpectedFiles(restaurantDataFilePath, reviewDataFilePath, menuDataFilePath);
        return 0;}

    // TODO MENU
    bool isRunning = true;
    while (isRunning) {
        system("cls");
        printf("--------------------------------------\n");
        printf("---------------BASE MENU--------------\n");
        printf("--------------------------------------\n");
        printf(" 1 - SHOW RESTAURANTS OVERVIEW\n");
        printf(" 2 - ADD RESTAURANT\n");
        printf(" 3 - SHOW MENU OVERVIEW\n");
        printf(" 4 - APP INFO\n");
        printf(" 5 - SAVE AND EXIT\n");
        printf("--------------------------------------\n");
        printf("- Please choose from menu [1/2/3/4/5]: ");
        int choice = getNumericInput(); // input checking function
        switch (choice) {
        case 1:
            // show restaurants overview
            break;
        case 2:
            // add restaurant function
            break;
        case 3:
            //show menu overview
        case 4:
            //show app info
        case 5:
            isRunning = false;
            break;
        }
    }
    
    while (saveToFileAllLinkedLists(restaurants, reviews, menus, restaurantDataFilePath, reviewDataFilePath, menuDataFilePath) == ERR) {
        printf("The saving process has failed.\nWould you like to try it again or close the app without saving the data?\n[any/close]: ");
        char cmd[6] = "\0";
        scanf_s("%s", cmd, (unsigned int)sizeof(cmd));
        if (strcmp(cmd, "close") == 0) {
            printf("Not saving, app is closing.\n");
            break;
        }
        consumeInput();

    }
    eraseAllLinkedLists(restaurants, reviews, menus);
    return 0;
}

