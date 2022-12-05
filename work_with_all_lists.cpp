#include "work_with_all_lists.h"

int initializeAllLinkedLists(RESTAURANT_LIST** res, REVIEW_LIST** rev, MENU_LIST** menu) {
    *res = createRestaurantList();
    *rev = createReviewList();
    *menu = createMenuList();
    if ((*res == NULL) || (*rev == NULL) || (*menu == NULL)) {
        eraseAllLinkedLists(*res, *rev, *menu);
        printf("Error while allocating memory for linked lists, app is closing.\n");
        return ERR;
    }
    return OK;
}

void eraseAllLinkedLists(RESTAURANT_LIST* res, REVIEW_LIST* rev, MENU_LIST* menu) {
    eraseMenuList(menu);
    eraseRestaurantList(res);
    eraseReviewList(rev);
}

int loadFromFileAllLinkedLists(RESTAURANT_LIST* res, REVIEW_LIST* rev, MENU_LIST* menu, char* resPath, char* revPath, char* menuPath) {
    if (loadFromFileRestaurantList(res, resPath) != OK) {
        printf("Error while loading data from Restaurant DB, app is closing.\n");
        eraseAllLinkedLists(res, rev, menu);
        return ERR;
    }
    if (loadFromFileReviewList(rev, revPath) != OK) {
        printf("Error while loading data from Review DB, app is closing.\n");
        eraseAllLinkedLists(res, rev, menu);
        return ERR;
    }
    if (loadFromFileMenuList(menu, menuPath) != OK) {
        printf("Error while loading data from Menu DB, app is closing.\n");
        eraseAllLinkedLists(res, rev, menu);
        return ERR;
    }
    return OK;
}

int saveToFileAllLinkedLists(RESTAURANT_LIST* res, REVIEW_LIST* rev, MENU_LIST* menu, char* resPath, char* revPath, char* menuPath) {
    if (saveToFileRestaurantList(res, resPath) != OK) {
        printf("Error while saving restaurant data to file.\n");
        return ERR;
    }
    if (saveToFileReviewList(rev, revPath) != OK) {
        printf("Error while saving review data to file.\n");
        return ERR;
    }
    if (saveToFileMenuList(menu, menuPath) != OK) {
        printf("Error while saving menu data to file.\n");
        return ERR;
    }
    return OK;
}