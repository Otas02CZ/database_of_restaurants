#include "review_list.h"


// Creates a review struct and gives it the given data, then the struct is returned
REVIEW createReview(unsigned int id, unsigned int res_id, char *title, unsigned int score, char *comment) {
    REVIEW rev;
    rev.id = id;
    rev.res_id = res_id;
    rev.score = score;
    strcpy_s(rev.title, sizeof(rev.title), title);
    strcpy_s(rev.comment, sizeof(rev.comment), comment);
    return rev;
}

// Initializes the review linked list by allocataing a struct with links to head, current and tail of the list, this struct is returned
REVIEW_LIST* createReviewList() {
    REVIEW_LIST* list = (REVIEW_LIST*)malloc(sizeof(REVIEW_LIST));
    if (list == NULL)
        return NULL;
    list->current = list->head = list->tail = NULL;
    list->length = 0;
    return list;
}
// Completely erases and deallocates the review linked list, with all its nodes, deallocates the list root as well
void eraseReviewList(REVIEW_LIST* list) {
    if (list == NULL)
        return;
    while (list->length != 0) {
        removeCurrentItemReviewList(list);
    }
    free(list);
}
// Adds the given review struct at the end of the list and sets the current pointer to it, returns OK or ERR_ALLOC depending on the state
int addItemToEndReviewList(REVIEW_LIST* list, REVIEW data) {
    REVIEW_ITEM* item = (REVIEW_ITEM*)malloc(sizeof(REVIEW_ITEM));
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
int goToNextItemReviewList(REVIEW_LIST* list) {
    if (list->current != list->tail) {
        list->current = list->current->next;
        return OK;
    }
    else
        return ERR_NO_NEXT;
}
// Returns the data of the node at current pointer (by placing it into the res param), returns OK or ERR depending on the state
int getCurrentItemDataReviewList(REVIEW_LIST* list, REVIEW* rev) {
    if (list->current != NULL) {
        *rev = list->current->data;
        return OK;
    }
    else
        return ERR;
}
// Edits the current item by the given data, returns OK or ERR depending on the state
int editCurrentItemReviewList(REVIEW_LIST* list, REVIEW data) {
    if (list->current != NULL) {
        list->current->data = data;
        return OK;
    }
    else
        return ERR;
}
// Removes the current item from the linked list if possible
void removeCurrentItemReviewList(REVIEW_LIST* list) {
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
    REVIEW_ITEM* temp;
    if (list->current->next != NULL)
        temp = list->current->next;
    else
        temp = list->tail;
    free(list->current);
    list->current = temp;
    list->length--;
}
// Searches for the id in the linked list and moves the current pointer to it, returns OK or ERR_NOT_FOUND
int moveCurrentToSearchedIdReviewList(REVIEW_LIST* list, unsigned int searchedValue) {
    if (searchedValue == list->tail->data.id) {
        list->current = list->tail;
        return OK;
    }
    if (searchedValue == list->current->data.id)
        return OK;
    REVIEW_ITEM* item = list->head;
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
int readStringFromFileReview(FILE* input, char* output, unsigned int maxLength) {
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
// Loads Review database from file to a memory linked list, returns ERR_LOAD, OK or ERR_ALLOC depending on the outcome
int loadFromFileReviewList(REVIEW_LIST* list, char *inputFilePath) {
    FILE* input;
    if (fopen_s(&input, inputFilePath, "r") != 0)
        return ERR_LOAD;

    REVIEW rev;

    while (1) {
        if (fscanf(input, "%u;\n", &rev.id) != 1) {
            break;
        }
        if (fscanf(input, "%u;\n", &rev.res_id) != 1) {
            fclose(input);
            return ERR_LOAD;}
        if ((readStringFromFileReview(input, rev.title, sizeof(rev.title)) == ERR_LOAD)) {
            fclose(input);
            return ERR_LOAD;}
        if (fscanf_s(input, "%u;\n", &rev.score) != 1) {
            fclose(input);
            return ERR_LOAD;}
        if ((readStringFromFileReview(input, rev.comment, sizeof(rev.title)) == ERR_LOAD)) {
            fclose(input);
            return ERR_LOAD;}
        printf("%u %u %s %u %s\n", rev.id, rev.res_id, rev.title, rev.score, rev.comment);
        if (addItemToEndReviewList(list, rev) == ERR_ALLOC) {
            fclose(input);
            return ERR_ALLOC;
        }
    }
    fclose(input);
    return OK;
}
// Saves the review linked list to file, returns ERR_SAVE or OK depending on the state
int saveToFileReviewList(REVIEW_LIST* list, char *outputFilePath) {
    FILE* output;
    if (fopen_s(&output, outputFilePath, "w") != 0)
        return ERR_SAVE;

    list->current = list->head;

    do {
        fprintf_s(output, "%u;\n%u;\n%s;\n%u;\n%s;\n", list->current->data.id, list->current->data.res_id, list->current->data.title, list->current->data.score, list->current->data.comment);
    } while (goToNextItemReviewList(list) != ERR_NO_NEXT);

    fclose(output);
    return OK;
}
// CHECK WORKING
void removeAllItemsWithResIdReviewList(REVIEW_LIST* list, unsigned int resId) {
    list->current = list->head;
    while (list->length != 0) {
        if (list->current->data.res_id == resId) {
            removeCurrentItemReviewList(list);
        }
        else {
            if (goToNextItemReviewList(list) != ERR_NO_NEXT) {
                continue;}
            else {
                break;}
        }
    }
}
// CHECK WORKING
void fixIdSequenceReviewList(REVIEW_LIST* list) {
    if (list->length == 0)
        return;
    list->current = list->head;
    unsigned int index = 0;
    do {
        if (list->current->data.id != index) {
            list->current->data.id = index;}
        index++;
    } while (goToNextItemReviewList(list) != ERR_NO_NEXT);
}