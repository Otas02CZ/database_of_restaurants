#pragma once

#include "imports.h"

typedef struct REVIEW {
    unsigned int        id;
    unsigned int        res_id;
    char                title[31];
    unsigned int        score;
    char                comment[401];
}REVIEW;

typedef struct REVIEW_ITEM REVIEW_ITEM;

struct REVIEW_ITEM {
    REVIEW_ITEM*    previous;
    REVIEW          data;
    REVIEW_ITEM*    next;
};

typedef struct REVIEW_LIST REVIEW_LIST;

struct REVIEW_LIST {
    REVIEW_ITEM*    head;
    REVIEW_ITEM*    current;
    REVIEW_ITEM*    tail;
    unsigned int    length;
};

REVIEW_LIST* createReviewList();
REVIEW createReview(unsigned int id, unsigned int res_id, char *title, unsigned int score, char *comment);
void eraseReviewList(REVIEW_LIST* list); 
int addItemToEndReviewList(REVIEW_LIST* list, REVIEW data);
int goToNextItemReviewList(REVIEW_LIST* list);
int getCurrentItemDataReviewList(REVIEW_LIST* list, REVIEW* rev);
int editCurrentItemReviewList(REVIEW_LIST* list, REVIEW data);
void removeCurrentItemReviewList(REVIEW_LIST* list);
int moveCurrentToSearchedIdReviewList(REVIEW_LIST* list, unsigned int searchedValue);
int loadFromFileReviewList(REVIEW_LIST* list, char *inputFilePath);
int saveToFileReviewList(REVIEW_LIST* list, char *outputFilePath);
void removeAllItemsWithResIdReviewList(REVIEW_LIST* list, unsigned int resId);
void fixIdSequenceReviewList(REVIEW_LIST* list);

// other search / view / sort methods ?