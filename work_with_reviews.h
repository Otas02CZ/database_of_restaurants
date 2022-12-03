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
