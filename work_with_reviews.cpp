#include "work_with_reviews.h"

void addReview(REVIEW_LIST* revList, RESTAURANT_LIST* resList, unsigned int resId) {
	unsigned int id = revList->length;
	unsigned int score = -1;
	char title[31], comment[201];
	printf("--------------------------------------\n");
	printf("-----------ADDING A REVIEW------------\n");
	printf("--------------------------------------\n");

	if (moveCurrentToSearchedIdRestaurantList(resList, resId) == OK) {
		printf("-ADDING REVIEW FOR RESTAURANT-\n");
		printBaseInfoCurrentRestaurant(resList);
		printf("Specify the review title please:\nInput 30 chars max: ");
		getStringInputUntilNewline(title, sizeof(title));
		printf("How would you rate the restaurant?\nInput a whole number [1-10]: ");
		while (score < 1 or score > 10) {
			scanf_s("%u", &score);
		}
		printf("Please write a short comment:\nInput 200 chars max newlines are allowed: ");
		getStringInputUntilEOF(comment, sizeof(comment));
		REVIEW rev = createReview(id, resId, title, score, comment);
		printf("-----------------------------------\n");
		if (addItemToEndReviewList(revList, rev) == OK)
			printf("Review successfully added to the database.\n");
		else
			printf("Error while adding the review to the database.\n");
	}
	else {
		printf("The associated restauant for the review can not be found.\n");
	}
}

void editReview(REVIEW_LIST* revList, RESTAURANT_LIST* resList, unsigned int id, unsigned int resId) {
	printf("---------------------------------------\n");
	printf("-----------EDITING A REVIEW------------\n");
	printf("---------------------------------------\n");

	if (moveCurrentToSearchedIdRestaurantList(resList, resId) == OK) {
		printf("-EDITING REVIEW FOR RESTAURANT-\n");
		printBaseInfoCurrentRestaurant(resList);
		if (moveCurrentToSearchedIdReviewList(revList, id) == OK) {
			printf("-EDITED REVIEW-\n");
			printBaseInfoCurrentReview(revList);
			unsigned int score = -1;
			char title[31], comment[201];
			printf("Specify the new review title please:\nInput 30 chars max: ");
			getStringInputUntilNewline(title, sizeof(title));
			printf("How would you rate the restaurant?\nInput a whole number [1-10]: ");
			while (score < 1 or score > 10) {
				scanf_s("%u", &score);
			}
			printf("Please write a short comment:\nInput 200 chars max newlines are allowed: ");
			getStringInputUntilEOF(comment, sizeof(comment));
			REVIEW rev = createReview(id, resId, title, score, comment);
			printf("-----------------------------------\n");
			if (editCurrentItemReviewList(revList, rev) == OK)
				printf("Review successfully edited.\n");
			else
				printf("Error while editing the review.\n");
		}
		else {
			printf("The review selected can not be found.\n");}
	}
	else {
		printf("The restaraunt associated with the review can not be found.\n");}
}

void removeReview(REVIEW_LIST* revList, RESTAURANT_LIST* resList, unsigned int id, unsigned int resId) {
	printf("-----------------------------------------\n");
	printf("------------DELETING A REVIEW------------\n");
	printf("-----------------------------------------\n");

	if (moveCurrentToSearchedIdRestaurantList(resList, resId) == OK) {
		printf("-REMOVING REVIEW FOR RESTAURANT-\n");
		printBaseInfoCurrentRestaurant(resList);
		if (moveCurrentToSearchedIdReviewList(revList, id) == OK) {
			printf("-REVIEW TO BE REMOVED-\n");
			printBaseInfoCurrentReview(revList);
			printf("This review will be deleted.\n");
			if (acceptOperation()) {
				printf("Deleting.\n");
				removeCurrentItemReviewList(revList); // CHECK WORKING
				fixIdSequenceReviewList(revList); // CHECK WORKING
			}
		}
		else {
			printf("Thre selected review can not be found.\n");
		}
	}
	else {
		printf("The restaurant associated with the review can not be found.\n");}
}

void printBaseInfoCurrentReview(REVIEW_LIST* revList) {
	REVIEW rev;
	if (getCurrentItemDataReviewList(revList, &rev) == OK) {
		printf("----------------------------------\n");
		printf("TITLE - %s\nSCORE - %u/10\nCOMMENT -\n%s\n", rev.title, rev.score, rev.comment);
		printf("----------------------------------\n");
	}
	else {
		printf("Error while printing specified review base info.\n");
	}
}