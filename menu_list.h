#pragma once

#include "imports.h"

typedef struct MENU {
    unsigned int        id;
    unsigned int        res_id;
    char                name[31];
    char                description[201];
}MENU;

typedef struct MENU_ITEM MENU_ITEM;

struct MENU_ITEM {
    MENU_ITEM*  previous;
    MENU        data;
    MENU_ITEM*  next;
};

typedef struct MENU_LIST MENU_LIST;

struct MENU_LIST {
    MENU_ITEM*      head;
    MENU_ITEM*      current;
    MENU_ITEM*      tail;
    unsigned int    length;
};

MENU_LIST* createMenuList();
MENU createMenu(unsigned int id, unsigned int res_id, char* name, char* description);
void eraseMenuList(MENU_LIST* list);
int addItemToEndMenuList(MENU_LIST* list, MENU data);
int goToNextItemMenuList(MENU_LIST* list);
int getCurrentItemDataMenuList(MENU_LIST* list, MENU* menu);
int editCurrentItemMenuList(MENU_LIST* list, MENU data);
void removeCurrentItemMenuList(MENU_LIST* list);
int moveCurrentToSearchedIdMenuList(MENU_LIST* list, unsigned int searchedValue);
int loadFromFileMenuList(MENU_LIST* list, char* inputFilePath);
int saveToFileMenuList(MENU_LIST* list, char* outputFilePath);
void removeAllItemsWithResIdMenuList(MENU_LIST* list, unsigned int resId);
void fixIdSequenceMenuList(MENU_LIST* list);

// other search / view / sort methods ?