#pragma once

#include "imports.h"

// code functions
// create list, add restaurant, remove, get list, get_ids?, get_restaurant?, delete

enum {
    OK = 0,
    ERR = 1,
    ERR_ALLOC = 2,
    ERR_LOAD = 3,
    ERR_SAVE = 4,
    ERR_NOT_FOUND = 5,
    ERR_NO_NEXT = 6
};

typedef struct RESTAURANT {
    unsigned int        id;
    char                name[30];
    char                address[40];
    unsigned int        type;
    char                description[200];

}RESTAURANT;

typedef struct RESTAURANT_ITEM RESTAURANT_ITEM;

struct RESTAURANT_ITEM {
    //unsigned int        id;
    RESTAURANT_ITEM* previous;
    RESTAURANT     data;
    RESTAURANT_ITEM* next;
};

typedef struct RESTAURANT_LIST RESTAURANT_LIST;

struct RESTAURANT_LIST {
    RESTAURANT_ITEM* head;
    RESTAURANT_ITEM* current;
    RESTAURANT_ITEM* tail;
    unsigned int        length;
};

RESTAURANT_LIST* createRestaurantList();
RESTAURANT createRestaurant(unsigned int id, char name[30], char address[40], unsigned int type, char description[200]);
void eraseRestaurantList(RESTAURANT_LIST* list); //TODO 
int addItemToEndRestaurantList(RESTAURANT_LIST* list, RESTAURANT data);
int goToNextItemRestaurantList(RESTAURANT_LIST* list);
RESTAURANT getCurrentItemDataRestaurantList(RESTAURANT_LIST* list);
void editCurrentItemRestaurantList(RESTAURANT_LIST* list, RESTAURANT data); //TODO
void removeCurrentItemRestaurantList(RESTAURANT_LIST* list); //TODO
int moveCurrentToSearchedIdRestaurantList(RESTAURANT_LIST* list, unsigned int searchedValue);
int loadFromFileRestaurantList(RESTAURANT_LIST* list, char inputFilePath[200]);
int saveToFileRestaurantList(RESTAURANT_LIST* list, char outputFilePath[200]);

// other search / view / sort methods ?