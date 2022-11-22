#ifndef HEADER_FILE
#define HEADER_FILE

#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// code functions
// create list, add restaurant, remove, get list, get_ids?, get_restaurant?, delete

enum {
    EOK=0,
    ERR=1,
    ERR_ALLOC=2
}STATUS;

typedef struct RESTAURANT{
    //unsigned int        id;
    char                name[30];
    char                address[40];
    unsigned short int  type;
    char                description[200];

}RESTAURANT;

typedef struct RESTAURANT_ITEM{
    unsigned int    id;
    RESTAURANT     data;
}RESTAURANT_ITEM;

typedef struct RESTAURANT_LIST{
    RESTAURANT_ITEM*    head;
    RESTAURANT_ITEM*    current;
    RESTAURANT_ITEM*    tail;
}RESTAURANT_LIST;

RESTAURANT_LIST* createRestaurantList();
void deleteRestaurantList();
RESTAURANT_ITEM* getCurrentRestaurantItem();
int addRestaurantItem(RESTAURANT_LIST* list, RESTAURANT data);



#endif