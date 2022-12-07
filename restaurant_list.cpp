//Author        : Otakar Koci @Otas02CZ 247555
//Description   : BUT - BPC-PC1T - semestral project
//YEAR          : 2022

#include "restaurant_list.h"


// Creates a restaurant struct and gives it the given data, then the struct is returned
RESTAURANT createRestaurant(unsigned int id, char *name, char *address, char *type, char *description) {
    RESTAURANT res;
    res.id = id;
    res.visible = true;
    strcpy_s(res.type, sizeof(res.type), type);
    strcpy_s(res.name, sizeof(res.name), name);
    strcpy_s(res.address, sizeof(res.address), address);
    strcpy_s(res.description, sizeof(res.description), description);
    return res;
}

// Initializes the restaurant linked list by allocating a struct with links to head, current and tail of the list, this struct is returned
RESTAURANT_LIST* createRestaurantList() {
    RESTAURANT_LIST* list = (RESTAURANT_LIST*)malloc(sizeof(RESTAURANT_LIST));
    if (list == NULL)
        return NULL;
    list->current = list->head = list->tail = NULL;
    list->length = 0;
    return list;
}

// Completely erases and deallocates the restaurant linked list, with all its nodes, deallocates the list root as well
void eraseRestaurantList(RESTAURANT_LIST* list) {
    if (list == NULL)
        return;
    while (list->length != 0) {
        removeCurrentItemRestaurantList(list);
    }
    free(list);
}

// Adds the given restaurant struct at the end of the list and sets the current pointer to it, returns OK or ERR_ALLOC depending on the state
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

// Moves the current pointer to the next node if possible, returns OK, otherwise returns ERR_NO_NEXT
int goToNextItemRestaurantList(RESTAURANT_LIST* list) {
    if (list->current != list->tail) {
        list->current = list->current->next;
        return OK;
    }
    else
        return ERR_NO_NEXT;
}

// Returns the data of the node at current pointer (by placing it into the res param), returns OK or ERR depending on the state
int getCurrentItemDataRestaurantList(RESTAURANT_LIST* list, RESTAURANT* res) {
    if (list->current != NULL) {
        *res = list->current->data;
        return OK;
    }
    else
        return ERR;
}

// Edits the current item by the given data, returns OK or ERR depending on the state
int editCurrentItemRestaurantList(RESTAURANT_LIST* list, RESTAURANT data) {
    if (list->current != NULL) {
        list->current->data = data;
        return OK;
    }
    else
        return ERR;
}

// Removes the current item from the linked list if possible
void removeCurrentItemRestaurantList(RESTAURANT_LIST* list) {
    if (list->current == NULL)
        return;
    if (list->current == list->head)
        list->head = list->current->next;
    if (list->current == list->tail)
        list->tail = list->current->previous;
    if (list->current->previous != NULL)
        list->current->previous->next = list->current->next;
    if (list->current->next != NULL)
        list->current->next->previous = list->current->previous;
    RESTAURANT_ITEM* temp;
    if (list->current->next != NULL)
        temp = list->current->next;
    else
        temp = list->tail;
    free(list->current);
    list->current = temp;
    list->length--;
}

// Searches for the id in the linked list and moves the current pointer to it, returns OK or ERR_NOT_FOUND
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

// Reads string from the file until it reaches ; or the maxLength, returns OK or ERR_LOAD depending on the state
int readStringFromFileRestaurant(FILE* input, char* output, unsigned int maxLength) {
    char symbol;
    int index = 0;
    while ((symbol = fgetc(input)) != EOF) {
        if (index == maxLength-1)
            return ERR_LOAD;
        if (symbol == ';')
            break;
        output[index] = symbol;
        index++;
    }
    symbol = fgetc(input);
    output[index] = '\0';
    return OK;
}

// Loads Restaurant database from file to a memory linked list, returns ERR_LOAD, OK or ERR_ALLOC depending on the outcome
int loadFromFileRestaurantList(RESTAURANT_LIST* list, char *inputFilePath) {
    FILE* input;
    if (fopen_s(&input, inputFilePath, "r") != 0)
        return ERR_LOAD;
    
    RESTAURANT res;

    while (1) {
        
        if (fscanf_s(input, "%u;\n", &res.id) != 1) {
            break;
        }
        if ((readStringFromFileRestaurant(input, res.name, sizeof(res.name)) == ERR_LOAD)) {
            fclose(input);
            return ERR_LOAD;}
        if ((readStringFromFileRestaurant(input, res.address, sizeof(res.address)) == ERR_LOAD)) {
            fclose(input);
            return ERR_LOAD;}
        if ((readStringFromFileRestaurant(input, res.type, sizeof(res.type)) == ERR_LOAD)) {
            fclose(input);
            return ERR_LOAD;}
        if ((readStringFromFileRestaurant(input, res.description, sizeof(res.description)) == ERR_LOAD)) {
            fclose(input);
            return ERR_LOAD;}
        res.visible = true;
        //printf("%u %s %s %s %s\n", res.id, res.name, res.address, res.type, res.description);
        if (addItemToEndRestaurantList(list, res) == ERR_ALLOC) {
            fclose(input);
            return ERR_ALLOC;}
    }
    fclose(input);
    return OK;
}

// Saves the restaurant linked list to file, returns ERR_SAVE or OK depending on the state
int saveToFileRestaurantList(RESTAURANT_LIST* list, char *outputFilePath) {
    FILE* output;
    if (fopen_s(&output, outputFilePath, "w") != 0)
        return ERR_SAVE;

    if (list->current == NULL) {
        fclose(output);
        return OK;
    }
        
    list->current = list->head;
    do {
        fprintf_s(output, "%u;\n%s;\n%s;\n%s;\n%s;\n", list->current->data.id, list->current->data.name, list->current->data.address, list->current->data.type, list->current->data.description);
    } while (goToNextItemRestaurantList(list) != ERR_NO_NEXT);
    
    fclose(output);
    return OK;
}