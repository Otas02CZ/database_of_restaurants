
#include "imports.h"
#include "database_of_restaurants.h"
#include "restaurant_list.h"
#include "review_list.h"
#include "menu_list.h"
#include "functions.h"
#include "work_with_all_lists.h"
#include "work_with_restaurants.h"
#include "work_with_reviews.h"
#include "work_with_menus.h"


int main(int argv, char* argc[]) {
    char restaurantDataFilePath[200] = "restaurant.txt";
    char reviewDataFilePath[200] = "review.txt";
    char menuDataFilePath[200] = "menu.txt";

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

    fixIdSequenceMenuList(menus);
    fixIdSequenceReviewList(reviews);
    fixRestaurantIdSequenceFixEveryLink(restaurants, reviews, menus);

    // TODO MENU
    unsigned int isRunning = 1, isAsking = 1, isReviewOfCurrentRestaurant = 0, isMenuOfCurrentRestaurant = 0; // declaring here because of the switch-case problem
    int revId, resId, menuId;
    int sortMethod = ID;
    while (isRunning) {
        system("cls");
        printf("--------------------------------------\n");
        printf("---------------BASE MENU--------------\n");
        printf("--------------------------------------\n");
        printf(" 1 - SHOW RESTAURANTS OVERVIEW\n");
        printf(" 2 - SHOW MENU OVERVIEW\n");
        printf(" 3 - APP INFO\n");
        printf(" 4 - SAVE AND EXIT\n");
        printf("--------------------------------------\n");
        printf("- Please choose from menu [1/2/3/4]: ");
        int choice = getNumericInput(); // input checking function
        switch (choice) {
        case 1:
            while (isRunning) {
                system("cls");
                printf("-----------------------------------------\n");
                printf("---------RESTAURANTS OVERVIEW------------\n");
                printf("-----------------------------------------\n\n");
                printTableOfRestaurants(restaurants, reviews);
                printf(" 1 - SELECT RESTAURANT FOR DETAILED VIEW AND MORE OPTIONS\n");
                printf(" 2 - ADD RESTAURANT\n");
                printf(" 3 - SORT\n");
                printf(" 4 - SEARCH\n");
                printf(" 5 - BACK TO BASE MENU\n");
                printf("-----------------------------------------\n");
                printf("- Please choose from menu [1/2/3/4/5]: ");
                choice = getNumericInput();
                switch (choice) {
                case 1:
                    while (isRunning) {
                        system("cls");
                        printf("-----------------------------------------\n");
                        printf("------------RESTAURANT LIST--------------\n");
                        printf("-----------------------------------------\n\n");
                        printTableOfRestaurants(restaurants, reviews);
                        if (restaurants->length == 0) {
                            printf("There are no restaurants to view.\n");
                            pressEnterToContinue();
                            isRunning = 0;
                            break;
                        }
                        printf("Please select restaurant from the list, by its id.\nOr input -1 to exit this input sequence: ");
                        resId = -2;
                        while (resId < 0 || resId > (int)(restaurants->length - 1)) {
                            if (resId == -1) {
                                isRunning = 0;
                                break;
                            }
                            resId = getNumericInput();
                        }
                        if (isRunning) {
                            while (isRunning) {
                                printAllInfoAboutRestaurant(restaurants, reviews, menus, (unsigned int)resId);
                                printf("-----------------------------------------\n");
                                printf(" 1 - EDIT RESTAURANT\n");
                                printf(" 2 - REMOVE RESTAURANT\n");
                                printf(" 3 - ADD REVIEW\n");
                                printf(" 4 - EDIT REVIEW\n");
                                printf(" 5 - REMOVE REVIEW\n");
                                printf(" 6 - ADD MEAL TO MENU\n");
                                printf(" 7 - EDIT MEAL\n");
                                printf(" 8 - REMOVE MEAL\n");
                                printf(" 9 - EXIT BACK TO RESTAURANTS OVERVIEW\n");
                                printf("-----------------------------------------\n");
                                printf(" - Please choose from menu [1/2/3/4/5/6/7/8/9]: ");
                                choice = getNumericInput();
                                switch (choice) {
                                case 1: // edit restaurant
                                    editRestaurant(restaurants, reviews, (unsigned int)resId);
                                    break;
                                case 2: // remove restaurant
                                    if (removeRestaurant(restaurants, reviews, menus, resId))
                                        isRunning = 0;
                                    break;
                                case 3: // add review
                                    addReview(reviews, restaurants, resId);
                                    break;
                                case 4: // edit review
                                    system("cls");
                                    printf("-----------------------------------------\n");
                                    printf("------------REVIEW LIST--------------\n");
                                    printf("-----------------------------------------\n\n");
                                    if (printTableOfAllReviewsOfSpecifiedRestaurant(reviews, resId) == 0) {
                                        //printf("There are no reviews for this restaurant.\n");
                                        printf("-----------------------------------------\n");
                                        pressEnterToContinue();
                                        break;
                                    }
                                    printf("-----------------------------------------\n");
                                    printf("In order to edit a review, please select it from the list, by its id.\nOr input -1 to exit this input sequence: ");
                                    revId = -2;
                                    isReviewOfCurrentRestaurant = 0;
                                    isAsking = 1;
                                    while (revId < 0 || !isReviewOfCurrentRestaurant) {
                                        if (revId == -1) {
                                            isAsking = 0;
                                            break;
                                        }
                                        revId = getNumericInput();
                                        isReviewOfCurrentRestaurant = isSpecifiedReviewUnderSpecifiedRestaurant(reviews, revId, resId);
                                    }
                                    if (isAsking) {
                                        editReview(reviews, restaurants, revId, resId);
                                        pressEnterToContinue();}
                                    break;
                                case 5: // remove review
                                    system("cls");
                                    printf("-----------------------------------------\n");
                                    printf("------------REVIEW LIST--------------\n");
                                    printf("-----------------------------------------\n\n");
                                    if (printTableOfAllReviewsOfSpecifiedRestaurant(reviews, resId) == 0) {
                                        //printf("There are no reviews for this restaurant.\n");
                                        printf("-----------------------------------------\n");
                                        pressEnterToContinue();
                                        break;
                                    }
                                    printf("-----------------------------------------\n");
                                    printf("In order to remove a review, please select it from the list, by its id.\nOr input -1 to exit this input sequence: ");
                                    revId = -2;
                                    isReviewOfCurrentRestaurant = 0;
                                    isAsking = 1;
                                    while (revId < 0 || !isReviewOfCurrentRestaurant) {
                                        if (revId == -1) {
                                            isAsking = 0;
                                            break;
                                        }
                                        revId = getNumericInput();
                                        isReviewOfCurrentRestaurant = isSpecifiedReviewUnderSpecifiedRestaurant(reviews, revId, resId);
                                    }
                                    if (isAsking) {
                                        removeReview(reviews, restaurants, revId, resId);
                                        pressEnterToContinue();}
                                    break;
                                case 6: // add meal to menu
                                    addMenu(menus, restaurants, reviews, resId);
                                    break;
                                case 7: // edit meal
                                    system("cls");
                                    printf("-----------------------------------------\n");
                                    printf("------------MEAL LIST--------------\n");
                                    printf("-----------------------------------------\n\n");
                                    if (printTableOfAllMenusOfSpecifiedRestaurant(menus, resId) == 0) {
                                        //printf("There is no menu for this restaurant.\n");
                                        printf("-----------------------------------------\n");
                                        pressEnterToContinue();
                                        break;
                                    }
                                    printf("-----------------------------------------\n");
                                    printf("In order to edit a meal, please select it from the list, by its id.\nOr input -1 to exit this input sequence: ");
                                    menuId = -2;
                                    isMenuOfCurrentRestaurant = 0;
                                    isAsking = 1;
                                    while (menuId < 0 || !isMenuOfCurrentRestaurant) {
                                        if (menuId == -1) {
                                            isAsking = 0;
                                            break;
                                        }
                                        menuId = getNumericInput();
                                        isMenuOfCurrentRestaurant = isSpecifiedMenuUnderSpecifiedRestaurant(menus, menuId, resId);
                                    }
                                    if (isAsking) {
                                        editMenu(menus, restaurants, reviews, menuId, resId);
                                        pressEnterToContinue();
                                    }
                                    break;
                                case 8: // remove meal
                                    system("cls");
                                    printf("-----------------------------------------\n");
                                    printf("------------MEAL LIST--------------\n");
                                    printf("-----------------------------------------\n\n");
                                    if (printTableOfAllMenusOfSpecifiedRestaurant(menus, resId) == 0) {
                                        //printf("There is no menu for this restaurant.\n");
                                        printf("-----------------------------------------\n");
                                        pressEnterToContinue();
                                        break;
                                    }
                                    printf("-----------------------------------------\n");
                                    printf("In order to remove a meal, please select it from the list, by its id.\nOr input -1 to exit this input sequence: ");
                                    menuId = -2;
                                    isMenuOfCurrentRestaurant = 0;
                                    isAsking = 1;
                                    while (menuId < 0 || !isMenuOfCurrentRestaurant) {
                                        if (menuId == -1) {
                                            isAsking = 0;
                                            break;
                                        }
                                        menuId = getNumericInput();
                                        isMenuOfCurrentRestaurant = isSpecifiedMenuUnderSpecifiedRestaurant(menus, menuId, resId);
                                    }
                                    if (isAsking) {
                                        removeMenu(menus, restaurants, reviews, menuId, resId);
                                        pressEnterToContinue();
                                    }
                                    break;
                                case 9:
                                    isRunning = 0;
                                    break;
                                }
                            }
                        }
                    }
                    isRunning = 1;
                    break;
                case 2:
                    addRestaurant(restaurants);
                    pressEnterToContinue();
                    break;
                case 3:
                    // sort by given key - name, rating
                    // when adding or removing res - sort back to sorting by id
                    // 
                    // after that sort it again
                    // 
                    // when closing app sort back to sorting by id
                    // 
                    // implement functions for sorting
                    // add a variable to determine current sorting method
                    // 
                    // add sorting option
                    break;
                case 4:
                    // add searching option
                    // maybe add new variable to the res struct - determining whether is shown or not
                    // then implement functions and variables to search by given key, and hold the state
                    //
                    break;
                case 5:
                    isRunning = 0;
                    break;
                default:
                    break;
                }
            }
            isRunning = 1;
            break;
        case 2:
            // show menu function
            // show all meals as menus of given restaurants, sort these by the res rating
            // show 
            break;
        case 3:
            printAppInfo(restaurants, reviews, menus);
            break;
        case 4:
            isRunning = 0;
            break;
        default:
            break;
        }
    }
    
    while (saveToFileAllLinkedLists(restaurants, reviews, menus, restaurantDataFilePath, reviewDataFilePath, menuDataFilePath) == ERR) {
        printf("The saving process has failed.\nWould you like to try it again or close the app without saving the data?\n[any/close]: ");
        char cmd[6] = "\0";
        scanf_s("%s", cmd, (unsigned int)sizeof(cmd));
        if (strcmp(cmd, "close") == 0) {
            printf("Not saving, app is closing.\n");
            break;}
        consumeInput();
    }
    eraseAllLinkedLists(restaurants, reviews, menus);
    return 0;
}

