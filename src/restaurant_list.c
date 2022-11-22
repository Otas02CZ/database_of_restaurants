#include "restaurant_list.h"
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

RESTAURANT_LIST* createRestaurantList() {
    RESTAURANT_LIST * list = malloc(sizeof(RESTAURANT_LIST));
    list->current = list->head = list->tail = NULL;
    return list;
}

int addRestaurantItem(RESTAURANT_LIST* list, RESTAURANT data) {
    RESTAURANT_ITEM* item = malloc(sizeof(RESTAURANT_ITEM));
    if (item==NULL)
        return ERR_ALLOC;
    if (list->head == NULL) {
        list->head = list->current = list->tail = item;
        item->id = 0;
        item->data = data; }
    else {
        item->id = list->tail->id + 1;
        list->tail = item;
        item->data = data;
    }
    return EOK;   
}

RESTAURANT_ITEM* getCurrentRestaurantItem(RESTAURANT_LIST* list) {
    return list->current;
}
