//Author        : Otakar Koci @Otas02CZ 247555
//Description   : BUT - BPC-PC1T - semestral project
//YEAR          : 2022

#include "database_of_restaurants.h"


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
        printf("Or you can force the app to recreate all the files as empty now. Would you like to do that?\n");
        if (acceptOperation()) {
            if (forceEmptyDBCreation(restaurantDataFilePath, reviewDataFilePath, menuDataFilePath) == ERR) {
                printf("Empty DB recreation failed, please create these files manually. Or move the program somewhere else.\n");
                return 0;}
            else {
                if (initializeAllLinkedLists(&restaurants, &reviews, &menus) == ERR)
                    return 0;
                if (loadFromFileAllLinkedLists(restaurants, reviews, menus, restaurantDataFilePath, reviewDataFilePath, menuDataFilePath) == ERR) {
                    printInfoExpectedFiles(restaurantDataFilePath, reviewDataFilePath, menuDataFilePath);
                    return 0;
                }
            }
        }
        else 
            return 0;
    }

    fixIdSequenceMenuList(menus);
    fixIdSequenceReviewList(reviews);
    fixRestaurantIdSequenceFixEveryLink(restaurants, reviews, menus);

    // declaring here - can not declare variables in switch
    bool isRunning = true, isAsking = true, isReviewOfCurrentRestaurant = false, isMenuOfCurrentRestaurant = false, usingSearch = false;
    int revId, resId, menuId;
    int sortMethod = ID;
    char searchQuery[31], mealSearchQuery[31];
    while (isRunning) {
        clearScreen();
        printf("--------------------------------------\n");
        printf("---------------BASE MENU--------------\n");
        printf("--------------------------------------\n");
        printf(" 1 - SHOW RESTAURANTS OVERVIEW\n");
        printf(" 2 - SHOW MENU OVERVIEW\n");
        printf(" 3 - APP INFO\n");
        printf(" 4 - SAVE AND EXIT\n");
        printf("--------------------------------------\n");
        printf("- Please choose from menu [1/2/3/4]: ");
        int choice = getNumericInput();
        switch (choice) {
        case 1: // restaurants overview
            while (isRunning) {
                clearScreen();
                printf("-----------------------------------------\n");
                printf("---------RESTAURANTS OVERVIEW------------\n");
                printf("-----------------------------------------\n\n");
                printTableOfRestaurants(restaurants, reviews);
                printLineAboutSearching(usingSearch, searchQuery);
                printLineAboutCurrentSortMethod(sortMethod);
                printf("-----------------------------------------\n");
                printf(" 1 - SELECT RESTAURANT FOR DETAILED VIEW AND MORE OPTIONS\n");
                printf(" 2 - ADD RESTAURANT\n");
                printf(" 3 - SORT\n");
                printf(" 4 - SEARCH\n");
                printf(" 5 - BACK TO BASE MENU\n");
                printf("-----------------------------------------\n");
                printf("- Please choose from menu [1/2/3/4/5]: ");
                choice = getNumericInput();
                switch (choice) {
                case 1: // restaurant selection and work with it
                    while (isRunning) {
                        clearScreen();
                        printf("-----------------------------------------\n");
                        printf("------------RESTAURANT LIST--------------\n");
                        printf("-----------------------------------------\n\n");
                        printTableOfRestaurants(restaurants, reviews);
                        if (restaurants->length == 0) {
                            printf("There are no restaurants to view.\n");
                            pressEnterToContinue();
                            isRunning = false;
                            break;
                        }
                        if (usingSearch) {
                            printf("Currently only restaurants that follow the search query \"%s\" are shown.\n", searchQuery);
                            printf("But you can open any restaurant if you input its id.\n");}
                        else {
                            printf("All restaurants are shown. No search is enabled.\n");}
                        printLineAboutCurrentSortMethod(sortMethod);
                        printf("Please select restaurant from the list, by its id.\nOr input -1 to exit this input sequence: ");
                        resId = -2;
                        while (resId < 0 || resId > (int)(restaurants->length - 1)) {
                            if (resId == -1) {
                                isRunning = false;
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
                                    if (sortMethod != ID)
                                        sortRestaurantListByGivenSpecifier(restaurants, reviews, ID);
                                    if (removeRestaurant(restaurants, reviews, menus, resId))
                                        isRunning = false;
                                    if (sortMethod != ID)
                                        sortRestaurantListByGivenSpecifier(restaurants, reviews, sortMethod);
                                    break;
                                case 3: // add review
                                    addReview(reviews, restaurants, resId);
                                    break;
                                case 4: // edit review
                                    clearScreen();
                                    printf("-----------------------------------------\n");
                                    printf("------------REVIEW LIST--------------\n");
                                    printf("-----------------------------------------\n\n");
                                    if (printTableOfAllReviewsOfSpecifiedRestaurant(reviews, resId) == 0) {
                                        printf("-----------------------------------------\n");
                                        pressEnterToContinue();
                                        break;
                                    }
                                    printf("-----------------------------------------\n");
                                    printf("In order to edit a review, please select it from the list, by its id.\nOr input -1 to exit this input sequence: ");
                                    revId = -2;
                                    isReviewOfCurrentRestaurant = false;
                                    isAsking = true;
                                    while (revId < 0 || !isReviewOfCurrentRestaurant) {
                                        if (revId == -1) {
                                            isAsking = false;
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
                                    clearScreen();
                                    printf("-----------------------------------------\n");
                                    printf("------------REVIEW LIST--------------\n");
                                    printf("-----------------------------------------\n\n");
                                    if (printTableOfAllReviewsOfSpecifiedRestaurant(reviews, resId) == 0) {
                                        printf("-----------------------------------------\n");
                                        pressEnterToContinue();
                                        break;
                                    }
                                    printf("-----------------------------------------\n");
                                    printf("In order to remove a review, please select it from the list, by its id.\nOr input -1 to exit this input sequence: ");
                                    revId = -2;
                                    isReviewOfCurrentRestaurant = false;
                                    isAsking = true;
                                    while (revId < 0 || !isReviewOfCurrentRestaurant) {
                                        if (revId == -1) {
                                            isAsking = false;
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
                                    clearScreen();
                                    printf("-----------------------------------------\n");
                                    printf("------------MEAL LIST--------------\n");
                                    printf("-----------------------------------------\n\n");
                                    if (printTableOfAllMenusOfSpecifiedRestaurant(menus, resId) == 0) {
                                        printf("-----------------------------------------\n");
                                        pressEnterToContinue();
                                        break;
                                    }
                                    printf("-----------------------------------------\n");
                                    printf("In order to edit a meal, please select it from the list, by its id.\nOr input -1 to exit this input sequence: ");
                                    menuId = -2;
                                    isMenuOfCurrentRestaurant = false;
                                    isAsking = true;
                                    while (menuId < 0 || !isMenuOfCurrentRestaurant) {
                                        if (menuId == -1) {
                                            isAsking = false;
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
                                    clearScreen();
                                    printf("-----------------------------------------\n");
                                    printf("------------MEAL LIST--------------\n");
                                    printf("-----------------------------------------\n\n");
                                    if (printTableOfAllMenusOfSpecifiedRestaurant(menus, resId) == 0) {
                                        printf("-----------------------------------------\n");
                                        pressEnterToContinue();
                                        break;
                                    }
                                    printf("-----------------------------------------\n");
                                    printf("In order to remove a meal, please select it from the list, by its id.\nOr input -1 to exit this input sequence: ");
                                    menuId = -2;
                                    isMenuOfCurrentRestaurant = false;
                                    isAsking = true;
                                    while (menuId < 0 || !isMenuOfCurrentRestaurant) {
                                        if (menuId == -1) {
                                            isAsking = false;
                                            break;
                                        }
                                        menuId = getNumericInput();
                                        isMenuOfCurrentRestaurant = isSpecifiedMenuUnderSpecifiedRestaurant(menus, menuId, resId);
                                    }
                                    if (isAsking) {
                                        removeMenu(menus, restaurants, reviews, menuId, resId);
                                        pressEnterToContinue();}
                                    break;
                                case 9:
                                    isRunning = false;
                                    break;
                                }
                            }
                        }
                    }
                    isRunning = true;
                    break;
                case 2: // add restaurant
                    if (sortMethod != ID)
                        sortRestaurantListByGivenSpecifier(restaurants, reviews, ID);
                    addRestaurant(restaurants);
                    if (sortMethod != ID)
                        sortRestaurantListByGivenSpecifier(restaurants, reviews, sortMethod);
                    pressEnterToContinue();
                    break;
                case 3: // sorting
                    while (isRunning) {
                        clearScreen();
                        printf("--------------------------------------\n");
                        printf("-----------SORTING CONFIG-------------\n");
                        printf("--------------------------------------\n");
                        printf(" 1 - SORT BY RESTAURANT ID\n");
                        printf(" 2 - SORT BY RESTAURANT NAME\n");
                        printf(" 3 - SORT BY RESTAURANT RATING\n");
                        printf(" 4 - EXIT BACK TO RESTAURANTS OVERVIEW\n");
                        printf("--------------------------------------\n");
                        printf(" - Please choose from menu [1/2/3/4]: ");
                        choice = getNumericInput();
                        switch (choice) {
                        case 1:
                            if (sortMethod != ID) {
                                sortMethod = ID;
                                sortRestaurantListByGivenSpecifier(restaurants, reviews, ID);
                            }
                            isRunning = false;
                            break;
                        case 2:
                            if (sortMethod != NAME) {
                                sortMethod = NAME;
                                sortRestaurantListByGivenSpecifier(restaurants, reviews, NAME);
                            }
                            isRunning = false;
                            break;
                        case 3:
                            if (sortMethod != RATING) {
                                sortMethod = RATING;
                                sortRestaurantListByGivenSpecifier(restaurants, reviews, RATING);
                            }
                            isRunning = false;
                            break;
                        case 4:
                            isRunning = false;
                            break;
                        default:
                            break;
                        }
                        
                    }
                    isRunning = 1;
                    break;
                case 4: // searching
                    clearScreen();
                    printf("-------------------------------\n");
                    printf("--------SEARCH BY NAME---------\n");
                    printf("-------------------------------\n");
                    printf("We are searching among restaurants by their names.\n");
                    printf("Please insert your search query or ; to view all restaurants: ");
                    getStringInputUntilNewline(searchQuery, sizeof(searchQuery));
                    if (strcmp(";", searchQuery) == 0 || strlen(searchQuery) == 0) {
                        usingSearch = false;
                        turnAllRestaurantsVisibility(restaurants, true);}
                    else {
                        usingSearch = true;
                        searchByNameInRestaurants(restaurants, searchQuery);}
                    break;
                case 5:
                    isRunning = false;
                    break;
                default:
                    break;
                }
            }
            isRunning = 1;
            break;
        case 2: // meals overview
            clearScreen();
            printf("-------------------------------\n");
            printf("--------MEALS OVERVIEW---------\n");
            printf("-------------------------------\n\n");
            printf("Would you like to search for certain meals, or show all the meals of all restaurants?\n");
            printf("Type ; to show all or insert the search query: ");
            getStringInputUntilNewline(mealSearchQuery, sizeof(mealSearchQuery));
            if (sortMethod != RATING)
                sortRestaurantListByGivenSpecifier(restaurants, reviews, RATING);
            printMenuOverviewForAllRestaurantsWithSearch(restaurants, reviews, menus, mealSearchQuery);
            if (sortMethod != RATING)
                sortRestaurantListByGivenSpecifier(restaurants, reviews, sortMethod);
            printf("You will be returned to base menu by hiting enter.\n");
            pressEnterToContinue(); 
            break;
        case 3: // app info
            printAppInfo(restaurants, reviews, menus);
            break;
        case 4: // close app
            isRunning = false;
            break;
        default:
            break;
        }
    }

    if (sortMethod != ID)
        sortRestaurantListByGivenSpecifier(restaurants, reviews, ID);
    while (saveToFileAllLinkedLists(restaurants, reviews, menus, restaurantDataFilePath, reviewDataFilePath, menuDataFilePath) == ERR) {
        printf("The saving process has failed.\nWould you like to try it again or close the app without saving the data?\n[any/close]: ");
        char cmd[6] = "\0";
        scanf("%s", cmd);
        if (strcmp(cmd, "close") == 0) {
            printf("Not saving, app is closing.\n");
            break;}
        consumeInput();
    }
    eraseAllLinkedLists(restaurants, reviews, menus);
    return 0;
}

