#pragma once

#include "imports.h"
#include "restaurant_list.h"
#include "menu_list.h"
#include "review_list.h"
#include "work_with_restaurants.h"
#include "work_with_reviews.h"


void addMenu(MENU_LIST* menuList, RESTAURANT_LIST* resList, REVIEW_LIST* revList, unsigned int resId);
void editMenu(MENU_LIST* menuList, RESTAURANT_LIST* resList, REVIEW_LIST* revList, unsigned int id, unsigned int resId);
void removeMenu(MENU_LIST* menuList, RESTAURANT_LIST* resList, REVIEW_LIST* revList, unsigned int id, unsigned int resId);
void printBaseInfoCurrentMenu(MENU_LIST* menuList);
unsigned int printTableOfAllMenusOfSpecifiedRestaurant(MENU_LIST* menuList, unsigned int resId);
unsigned int isSpecifiedMenuUnderSpecifiedRestaurant(MENU_LIST* menuList, unsigned int id, unsigned int resId);

// add menu
// edit menu
// remove menu