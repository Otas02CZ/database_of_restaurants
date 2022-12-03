#include "menu_list.h"


// Creates a menu struct and gives it the given data, then the struct is returned
MENU createMenu(unsigned int id, unsigned int res_id, char* name, char* description) {
    MENU menu;
    menu.id = id;
    menu.res_id = res_id;
    strcpy_s(menu.name, sizeof(menu.name), name);
    strcpy_s(menu.description, sizeof(menu.description), description);
    return menu;
}

// Initializes the menu linked list by allocating a struct with links to head, current and tail of the list, this struct is returned
MENU_LIST* createMenuList() {
    MENU_LIST* list = (MENU_LIST*)malloc(sizeof(MENU_LIST));
    if (list == NULL)
        return NULL;
    list->current = list->head = list->tail = NULL;
    list->length = 0;
    return list;
}
// Completely erases and deallocates the menu linked list, with all its nodes, deallocates the list root as well
void eraseMenuList(MENU_LIST* list) {
    if (list == NULL)
        return;
    while (list->length != 0) {
        removeCurrentItemMenuList(list);
    }
    free(list);
}
// Adds the given menu struct at the end of the list and sets the current pointer to it, returns OK or ERR_ALLOC depending on the state
int addItemToEndMenuList(MENU_LIST* list, MENU data) {
    MENU_ITEM* item = (MENU_ITEM*)malloc(sizeof(MENU_ITEM));
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
int goToNextItemMenuList(MENU_LIST* list) {
    if (list->current != list->tail) {
        list->current = list->current->next;
        return OK;
    }
    else
        return ERR_NO_NEXT;
}
// Returns the data of the node at current pointer (by placing it into the menu param), returns OK or ERR depending on the state
int getCurrentItemDataMenuList(MENU_LIST* list, MENU* menu) {
    if (list->current != NULL) {
        *menu = list->current->data;
        return OK;
    }
    else
        return ERR;
}
// Edits the current item by the given data, returns OK or ERR depending on the state
int editCurrentItemMenuList(MENU_LIST* list, MENU data) {
    if (list->current != NULL) {
        list->current->data = data;
        return OK;
    }
    else
        return ERR;
}
// Removes the current item from the linked list if possible
void removeCurrentItemMenuList(MENU_LIST* list) {
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
    MENU_ITEM* temp;
    if (list->current->next != NULL)
        temp = list->current->next;
    else
        temp = list->tail;
    free(list->current);
    list->current = temp;
    list->length--;
}
// Searches for the id in the linked list and moves the current pointer to it, returns OK or ERR_NOT_FOUND
int moveCurrentToSearchedIdMenuList(MENU_LIST* list, unsigned int searchedValue) {
    if (searchedValue == list->tail->data.id) {
        list->current = list->tail;
        return OK;
    }
    if (searchedValue == list->current->data.id)
        return OK;
    MENU_ITEM* item = list->head;
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
int readStringFromFileMenu(FILE* input, char* output, unsigned int maxLength) {
    char symbol;
    int index = 0;
    while ((symbol = fgetc(input)) != EOF) {
        if (index == maxLength - 1)
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
// Loads menu database from file to a memory linked list, returns ERR_LOAD, OK or ERR_ALLOC depending on the outcome
int loadFromFileMenuList(MENU_LIST* list, char* inputFilePath) {
    FILE* input;
    if (fopen_s(&input, inputFilePath, "r") != 0)
        return ERR_LOAD;

    MENU menu;

    while (1) {

        if (fscanf_s(input, "%u;\n", &menu.id) != 1) {
            break;
        }
        if (fscanf_s(input, "%u;\n", &menu.res_id) != 1) {
            fclose(input);
            return ERR_LOAD;
        }
        if ((readStringFromFileMenu(input, menu.name, sizeof(menu.name)) == ERR_LOAD)) {
            fclose(input);
            return ERR_LOAD;
        }
        if ((readStringFromFileMenu(input, menu.description, sizeof(menu.description)) == ERR_LOAD)) {
            fclose(input);
            return ERR_LOAD;
        }
        printf("%u %u %s %s\n", menu.id, menu.res_id, menu.name, menu.description);
        if (addItemToEndMenuList(list, menu) == ERR_ALLOC) {
            fclose(input);
            return ERR_ALLOC;
        }
    }
    fclose(input);
    return OK;
}
// Saves the menu linked list to file, returns ERR_SAVE or OK depending on the state
int saveToFileMenuList(MENU_LIST* list, char* outputFilePath) {
    FILE* output;
    if (fopen_s(&output, outputFilePath, "w") != 0)
        return ERR_SAVE;

    list->current = list->head;
    do {
        fprintf_s(output, "%u;\n%u;\n%s;\n%s;\n", list->current->data.id, list->current->data.res_id, list->current->data.name, list->current->data.description);
    } while (goToNextItemMenuList(list) != ERR_NO_NEXT);

    fclose(output);
    return OK;
}
// CHECK WORKING
void removeAllItemsWithResIdMenuList(MENU_LIST* list, unsigned int resId) {
    list->current = list->head;
    while (list->length != 0) {
        if (list->current->data.res_id == resId) {
            removeCurrentItemMenuList(list);
        }
        else {
            if (goToNextItemMenuList(list) != ERR_NO_NEXT) {
                continue;}
            else {
                break;}
        }
    }
}
// CHECK WORKING
void fixIdSequenceMenuList(MENU_LIST* list) {
    if (list->length == 0)
        return;
    list->current = list->head;
    unsigned int index = 0;
    do {
        if (list->current->data.id != index) {
            list->current->data.id = index;
        }
        index++;
    } while (goToNextItemMenuList(list) != ERR_NO_NEXT);
}