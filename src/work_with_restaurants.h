//Author        : Otakar Koci @Otas02CZ 247555
//Description   : BUT - BPC-PC1T - semestral project
//YEAR          : 2022

#pragma once

#include "imports.h"
#include "restaurant_list.h"
#include "menu_list.h"
#include "review_list.h"
#include "functions.h"
#include "work_with_reviews.h"
#include "work_with_menus.h"


void addRestaurant(RESTAURANT_LIST* resList);
void editRestaurant(RESTAURANT_LIST* resList, REVIEW_LIST* revList, unsigned int id);
void printBaseInfoCurrentRestaurant(RESTAURANT_LIST* resList, REVIEW_LIST* revList);
int removeRestaurant(RESTAURANT_LIST* resList, REVIEW_LIST* revList, MENU_LIST* menuList, unsigned int id);
void fixRestaurantIdSequenceFixEveryLink(RESTAURANT_LIST* resList, REVIEW_LIST* revList, MENU_LIST* menuList);
void printTableOfRestaurants(RESTAURANT_LIST* resList, REVIEW_LIST* revList);
void printSpecialInfoCurrentRestaurant(RESTAURANT_LIST* resList, REVIEW_LIST* revList, MENU_LIST* menuList, unsigned int id);
void printAllInfoAboutRestaurant(RESTAURANT_LIST* resList, REVIEW_LIST* revList, MENU_LIST* menuList, unsigned int id);
void searchByNameInRestaurants(RESTAURANT_LIST* resList, char* searchQuery);
void turnAllRestaurantsVisibility(RESTAURANT_LIST* resList, bool value);
void swapRestaurants(RESTAURANT_ITEM* res1, RESTAURANT_ITEM* res2);
void sortRestaurantListByGivenSpecifier(RESTAURANT_LIST* resList, REVIEW_LIST* revList, unsigned int specifier);
void printMenuOverviewForAllRestaurantsWithSearch(RESTAURANT_LIST* resList, REVIEW_LIST* revList, MENU_LIST* menuList, char* searchQuery);