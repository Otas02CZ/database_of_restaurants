//Author        : Otakar Koci @Otas02CZ 247555
//Description   : BUT - BPC-PC1T - semestral project
//YEAR          : 2022

#pragma once

#include "imports.h"
#include "restaurant_list.h"
#include "menu_list.h"
#include "review_list.h"
#include "work_with_restaurants.h"
#include "work_with_reviews.h"
#include "functions.h"


void addMenu(MENU_LIST* menuList, RESTAURANT_LIST* resList, REVIEW_LIST* revList, unsigned int resId);
void editMenu(MENU_LIST* menuList, RESTAURANT_LIST* resList, REVIEW_LIST* revList, unsigned int id, unsigned int resId);
void removeMenu(MENU_LIST* menuList, RESTAURANT_LIST* resList, REVIEW_LIST* revList, unsigned int id, unsigned int resId);
void printBaseInfoCurrentMenu(MENU_LIST* menuList);
unsigned int printTableOfAllMenusOfSpecifiedRestaurant(MENU_LIST* menuList, unsigned int resId);
bool isSpecifiedMenuUnderSpecifiedRestaurant(MENU_LIST* menuList, unsigned int id, unsigned int resId);