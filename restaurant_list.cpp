#include "restaurant_list.h"



RESTAURANT createRestaurant(unsigned int id, char name[30], char address[40], unsigned int type, char description[200]) {
    RESTAURANT res;
    res.id = id;
    res.type = type;
    strcpy(res.name, name);
    strcpy(res.address, address);
    strcpy(res.description, description);
    return res;
}


RESTAURANT_LIST* createRestaurantList() {
    RESTAURANT_LIST* list = (RESTAURANT_LIST*)malloc(sizeof(RESTAURANT_LIST));
    list->current = list->head = list->tail = NULL;
    list->length = 0;
    return list;
}

void eraseRestaurantList(RESTAURANT_LIST* list) {
    while (list->length != 0) {
        removeCurrentItemRestaurantList(list);
    }
    free(list);
}

int addItemToEndRestaurantList(RESTAURANT_LIST* list, RESTAURANT data) {
    RESTAURANT_ITEM* item = (RESTAURANT_ITEM*)malloc(sizeof(RESTAURANT_ITEM));
    if (item == NULL)
        return ERR_ALLOC;
    if (list->head == NULL) {
        list->head = list->current = list->tail = item;
        item->data = data;
        item->previous = item->next = NULL;
    }
    else {
        item->previous = list->tail;
        list->tail->next = item;
        list->tail = item;
        item->data = data;
        item->next = NULL;
        list->current = item;
    }
    list->length++;
    return OK;
}

int goToNextItemRestaurantList(RESTAURANT_LIST* list) {
    if (list->current != list->tail) {
        list->current = list->current->next;
        return OK;
    }
    else
        return ERR_NO_NEXT;
}

RESTAURANT getCurrentItemDataRestaurantList(RESTAURANT_LIST* list) {
    return list->current->data;
}

void editCurrentItemRestaurantList(RESTAURANT_LIST* list, RESTAURANT data) {
    list->current->data = data;
}

void removeCurrentItemRestaurantList(RESTAURANT_LIST* list) {
    if (list->current == list->head)
        list->head = list->current->next;
    if (list->current == list->tail)
        list->tail = list->current->previous;
    if (list->current->previous != NULL)
        list->current->previous->next = list->current->next;
    if (list->current->next != NULL)
        list->current->next->previous = list->current->previous;
    free(list->current);
    list->current = list->tail;
    list->length--;
}

int moveCurrentToSearchedIdRestaurantList(RESTAURANT_LIST* list, unsigned int searchedValue) {
    if (searchedValue == list->tail->data.id) {
        list->current = list->tail;
        return OK;
    }
    if (searchedValue == list->current->data.id)
        return OK;
    RESTAURANT_ITEM* item = list->head;
    while (item != NULL) {
        if (item->data.id == searchedValue) {
            list->current = item;
            return OK;
        }
        else
            item = item->next;
    }
    return ERR_NOT_FOUND;
}

int readStringFromFile(FILE* input, char *output) {
    char symbol;
    int index = 0;
    while ((symbol = fgetc(input)) != EOF) {
        if (index == 200)
            return ERR_LOAD;
        if (symbol == ';' && index == 0)
            continue;
        else {
            if (symbol == ';' && index != 0)
                break;
        }
        if (symbol == '\n')
            break;
        output[index] = symbol;
        index++;
    }
    output[index] = '\0';
    return OK;
}


int loadFromFileRestaurantList(RESTAURANT_LIST* list, char inputFilePath[200]) {
    FILE* input = fopen(inputFilePath, "r");
    if (input == NULL) {
        return ERR_LOAD;}
    
    RESTAURANT res;
    char temp[200];

    while (1) {
        if (fscanf(input, "%u\n", &res.id) != 1) {
            break;
        }
        if ((readStringFromFile(input, temp) == OK) && (strlen(temp) <= 30))
            strcpy(res.name, temp);
        else {
            fclose(input);
            return ERR_LOAD;
        }
        if ((readStringFromFile(input, temp) == OK) && (strlen(temp) <= 40))
            strcpy(res.address, temp);
        else {
            fclose(input);
            return ERR_LOAD;
        }
        if (fscanf(input, "%u\n", &res.type) != 1) {
            fclose(input);
            return ERR_LOAD;
        }
        if ((readStringFromFile(input, temp) == OK))
            strcpy(res.description, temp);
        else {
            fclose(input);
            return ERR_LOAD;
        }
        printf("%u %s %s %u %s\n", res.id, res.name, res.address, res.type, res.description);
        if (addItemToEndRestaurantList(list, res) == ERR_ALLOC) {
            fclose(input);
            return ERR_ALLOC;}
    }
    fclose(input);
    return OK;
}

int saveToFileRestaurantList(RESTAURANT_LIST* list, char outputFilePath[200]) {
    FILE* output = fopen(outputFilePath, "w");
    if (output == NULL) {
        return ERR_SAVE;}

    list->current = list->head;

    do {
        fprintf(output, "%u\n%s\n%s\n%u\n%s\n", list->current->data.id, list->current->data.name, list->current->data.address, list->current->data.type, list->current->data.description);
    } while (goToNextItemRestaurantList(list) != ERR_NO_NEXT);

    fclose(output);
    return OK;
}