#pragma once

#include "imports.h"

typedef struct RESTAURANT {
    unsigned int        id;
    char                name[31];
    char                address[41];
    char                type[21];
    char                description[201];
}RESTAURANT;

typedef struct RESTAURANT_ITEM RESTAURANT_ITEM;

struct RESTAURANT_ITEM {
    RESTAURANT_ITEM*    previous;
    RESTAURANT          data;
    RESTAURANT_ITEM*    next;
};

typedef struct RESTAURANT_LIST RESTAURANT_LIST;

struct RESTAURANT_LIST {
    RESTAURANT_ITEM*    head;
    RESTAURANT_ITEM*    current;
    RESTAURANT_ITEM*    tail;
    unsigned int        length;
};

RESTAURANT_LIST* createRestaurantList();
RESTAURANT createRestaurant(unsigned int id, char *name, char *address, char *type, char *description);
void eraseRestaurantList(RESTAURANT_LIST* list);
int addItemToEndRestaurantList(RESTAURANT_LIST* list, RESTAURANT data);
int goToNextItemRestaurantList(RESTAURANT_LIST* list);
int getCurrentItemDataRestaurantList(RESTAURANT_LIST* list, RESTAURANT* res);
int editCurrentItemRestaurantList(RESTAURANT_LIST* list, RESTAURANT data);
void removeCurrentItemRestaurantList(RESTAURANT_LIST* list);
int moveCurrentToSearchedIdRestaurantList(RESTAURANT_LIST* list, unsigned int searchedValue);
int loadFromFileRestaurantList(RESTAURANT_LIST* list, char *inputFilePath);
int saveToFileRestaurantList(RESTAURANT_LIST* list, char *outputFilePath);

// other search / view / sort methods ?