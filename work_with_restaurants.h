#pragma once

#include "imports.h"
#include "restaurant_list.h"
#include "menu_list.h"
#include "review_list.h"
#include "functions.h"
#include "work_with_reviews.h"
#include "work_with_menus.h"


void addRestaurant(RESTAURANT_LIST* resList);
void editRestaurant(RESTAURANT_LIST* resList, unsigned int id);
void printBaseInfoCurrentRestaurant(RESTAURANT_LIST* resList);
void removeRestaurant(RESTAURANT_LIST* resList, REVIEW_LIST* revList, MENU_LIST* menuList, unsigned int id);
void fixRestaurantIdSequenceFixEveryLink(RESTAURANT_LIST* resList, REVIEW_LIST* revList, MENU_LIST* menuList);

// PRINT INFO BY RESTAURANT ID AND PRINT SPECIAL RESTAURANT INFO (ADDITIONAL)