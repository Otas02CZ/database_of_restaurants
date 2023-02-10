//Author        : Otakar Koci @Otas02CZ 247555
//Description   : BUT - BPC-PC1T - semestral project
//YEAR          : 2022

#pragma once

#include "imports.h"
#include "restaurant_list.h"
#include "menu_list.h"
#include "review_list.h"


int initializeAllLinkedLists(RESTAURANT_LIST** res, REVIEW_LIST** rev, MENU_LIST** menu);
void eraseAllLinkedLists(RESTAURANT_LIST* res, REVIEW_LIST* rev, MENU_LIST* menu);
int loadFromFileAllLinkedLists(RESTAURANT_LIST* res, REVIEW_LIST* rev, MENU_LIST* menu, char* resPath, char* revPath, char* menuPath);
int saveToFileAllLinkedLists(RESTAURANT_LIST* res, REVIEW_LIST* rev, MENU_LIST* menu, char* resPath, char* revPath, char* menuPath);