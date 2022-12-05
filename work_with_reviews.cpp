#include "work_with_reviews.h"

void addReview(REVIEW_LIST* revList, RESTAURANT_LIST* resList, unsigned int resId) {
	unsigned int id = revList->length;
	unsigned int score = -1;
	char title[31], comment[201];
	system("cls");
	printf("--------------------------------------\n");
	printf("-----------ADDING A REVIEW------------\n");
	printf("--------------------------------------\n");

	if (moveCurrentToSearchedIdRestaurantList(resList, resId) == OK) {
		printf("-ADDING REVIEW FOR RESTAURANT-\n");
		printBaseInfoCurrentRestaurant(resList, revList);
		printf("For information about allowed inputs please check the APP INFO\n");
		printf("Specify the review title please:\nInput 30 chars max: ");
		getStringInputUntilNewline(title, sizeof(title));
		printf("How would you rate the restaurant?\nInput a whole number [1-10]: ");
		while (score < 1 or score > 10) {
			scanf_s("%u", &score);
		}
		printf("Please write a short comment\nInput 400 chars max newlines are allowed\nTo end your input type ; or ctrl-Z on a new line:\n");
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
	system("cls");
	printf("---------------------------------------\n");
	printf("-----------EDITING A REVIEW------------\n");
	printf("---------------------------------------\n");

	if (moveCurrentToSearchedIdRestaurantList(resList, resId) == OK) {
		printf("-EDITING REVIEW FOR RESTAURANT-\n");
		printBaseInfoCurrentRestaurant(resList, revList);
		if (moveCurrentToSearchedIdReviewList(revList, id) == OK) {
			printf("-EDITED REVIEW-\n");
			printBaseInfoCurrentReview(revList);
			unsigned int score = -1;
			char title[31], comment[201];
			printf("For information about allowed inputs please check the APP INFO\n");
			printf("Specify the new review title please:\nInput 30 chars max: ");
			getStringInputUntilNewline(title, sizeof(title));
			printf("How would you rate the restaurant?\nInput a whole number [1-10]: ");
			while (score < 1 or score > 10) {
				scanf_s("%u", &score);
			}
			printf("Please write a short comment\nInput 400 chars max newlines are allowed\nTo end your input type ; or ctrl-Z on a new line:\n");
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
	system("cls");
	printf("-----------------------------------------\n");
	printf("------------DELETING A REVIEW------------\n");
	printf("-----------------------------------------\n");

	if (moveCurrentToSearchedIdRestaurantList(resList, resId) == OK) {
		printf("-REMOVING REVIEW FOR RESTAURANT-\n");
		printBaseInfoCurrentRestaurant(resList, revList);
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
		printf("- TITLE: %s\n- RATING: %u/10\n- COMMENT:\n%s\n", rev.title, rev.score, rev.comment);
		printf("----------------------------------\n");
	}
	else {
		printf("Error while printing specified review base info.\n");
	}
}

float getOverallScoreForRestaurant(REVIEW_LIST* revList, unsigned int resId) {
	if (revList->current == NULL)
		return -1;
	float score = 0;
	unsigned int reviewCount = 0;
	revList->current = revList->head;
	REVIEW rev;
	do {
		if (getCurrentItemDataReviewList(revList, &rev) == OK) {
			if (rev.res_id == resId) {
				score += rev.score;
				reviewCount++;
			}
		}
	} while (goToNextItemReviewList(revList) != ERR_NO_NEXT);
	if (reviewCount == 0)
		return -1;
	else
		return score / reviewCount;
}

unsigned int printTableOfAllReviewsOfSpecifiedRestaurant(REVIEW_LIST* revList, unsigned int resId) {
	printf("----------------------------------------------------\n");
	printf("----ID----|------------TITLE-------------|--RATING--\n");
	printf("----------------------------------------------------\n");
	unsigned int totalReviews = 0;
	if (revList->length == 0) {
		printf("THERE AREN'T ANY REVIEWS FOR THIS RESTAURANT\n");
		return 0;
	}
	else {
		revList->current = revList->head;
		do {
			REVIEW rev;
			if (getCurrentItemDataReviewList(revList, &rev) == OK) {
				if (rev.res_id == resId) {
					totalReviews++;
					printf("%u", rev.id);
					unsigned int digits = 0, number = rev.id;
					if (number == 0) number++;
					while (number > 0) {
						digits++;
						number /= 10;
					}
					for (int i = 0; i < (11 - (int)(digits)); i++) printf(" ");
					printf("%s", rev.title);
					for (int i = 0; i < (sizeof(rev.title) - strlen(rev.title)); i++) printf(" ");
					printf("%u/10\n", rev.score);
				}
			}
		} while (goToNextItemReviewList(revList) != ERR_NO_NEXT);
	}
	if (totalReviews == 0)
		printf("THERE AREN'T ANY REVIEWS FOR THIS RESTAURANT\n");
	printf("----------------------------------------------------\n");
	return totalReviews;
}

unsigned int isSpecifiedReviewUnderSpecifiedRestaurant(REVIEW_LIST* revList, unsigned int id, unsigned int resId) {
	if (revList->length == 0) {
		return false;
	}
	else {
		revList->current = revList->head;
		do {
			REVIEW rev;
			if (getCurrentItemDataReviewList(revList, &rev) == OK) {
				if (rev.id == id && rev.res_id == resId)
					return true;
			}
		} while (goToNextItemReviewList(revList) != ERR_NO_NEXT);
	}
	return false;
}