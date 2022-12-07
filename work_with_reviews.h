//Author        : Otakar Koci @Otas02CZ 247555
//Description   : BUT - BPC-PC1T - semestral project
//YEAR          : 2022

#pragma once

#include "imports.h"
#include "restaurant_list.h"
#include "menu_list.h"
#include "review_list.h"
#include "work_with_restaurants.h"
#include "work_with_menus.h"


void addReview(REVIEW_LIST* revList, RESTAURANT_LIST* resList, unsigned int resId);
void editReview(REVIEW_LIST* revList, RESTAURANT_LIST* resList, unsigned int id, unsigned int resId);
void removeReview(REVIEW_LIST* revList, RESTAURANT_LIST* resList, unsigned int id, unsigned int resId);
void printBaseInfoCurrentReview(REVIEW_LIST* revList);
float getOverallScoreForRestaurant(REVIEW_LIST* revList, unsigned int resId);
unsigned int printTableOfAllReviewsOfSpecifiedRestaurant(REVIEW_LIST* revList, unsigned int resId);
unsigned int isSpecifiedReviewUnderSpecifiedRestaurant(REVIEW_LIST* revList, unsigned int id, unsigned int resId);