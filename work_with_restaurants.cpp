#include "work_with_restaurants.h"


// gets input from the user and adds restaurant at the end of the list
void addRestaurant(RESTAURANT_LIST* resList) {
	unsigned int id = resList->length;
	char name[31], address[41], type[21], description[201];
	system("cls");
	printf("--------------------------------------\n");
	printf("---------ADDING A RESTAURANT----------\n");
	printf("--------------------------------------\n");
	printf("For information about allowed inputs please check the APP INFO\n");
	printf("Specify the name please:\nInput 30 chars max: ");
	getStringInputUntilNewline(name, sizeof(name));
	printf("Specify the address please:\nInput 40 chars max: ");
	getStringInputUntilNewline(address, sizeof(address));
	printf("Specify the restaurant type [ceska, .]:\nPlease input 20 chars max: ");
	getStringInputUntilNewline(type, sizeof(type));
	printf("Please write a brief description\nInput 400 chars max newlines are allowed\nTo end your input type ; or ctrl-Z on a new line:\n");
	getStringInputUntilEOF(description, sizeof(description));
	RESTAURANT res = createRestaurant(id, name, address, type, description);
	printf("--------------------------------------\n");
	if (addItemToEndRestaurantList(resList, res) == OK)
		printf("Restaurant successfully added to the database.\n");
	else
		printf("Error while adding the restaurant to the database.\n");
}

// gets input from the user and edits the given restaurant
void editRestaurant(RESTAURANT_LIST* resList, REVIEW_LIST* revList, unsigned int id) {
	system("cls");
	printf("---------------------------------------\n");
	printf("---------EDITING A RESTAURANT----------\n");
	printf("---------------------------------------\n");
	printf("running");
	if (moveCurrentToSearchedIdRestaurantList(resList, id) == OK) {
		printf("-EDITED RESTAURANT-\n");
		printBaseInfoCurrentRestaurant(resList, revList);
		char name[31], address[41], type[21], description[201];
		printf("For information about allowed inputs please check the APP INFO\n");
		printf("Specify the new name please:\nInput 30 chars max: ");
		getStringInputUntilNewline(name, sizeof(name));
		printf("Specify the new address please:\nInput 40 chars max: ");
		getStringInputUntilNewline(address, sizeof(address));
		printf("Specify the new restaurant type [ceska, .]:\nPlease input 20 chars max: ");
		getStringInputUntilNewline(type, sizeof(type));
		printf("Please write a new brief description\nInput 400 chars max newlines are allowed\nTo end your input type ; or ctrl-Z on a new line:\n");
		getStringInputUntilEOF(description, sizeof(description));
		RESTAURANT res = createRestaurant(id, name, address, type, description);
		printf("--------------------------------------\n");
		if (editCurrentItemRestaurantList(resList, res) == OK) {
			printf("Restaurant successfully edited.\n");
			printf("-RESULT-\n");
			printBaseInfoCurrentRestaurant(resList, revList);}
		else {
			printf("Error while editing the specified restaurant.\n");}
	}
	else {
		printf("The restaurant selected can not be found.\n");}
	pressEnterToContinue();
}

// prints base information about restaurant at the current index of restaurant list
void printBaseInfoCurrentRestaurant(RESTAURANT_LIST* resList, REVIEW_LIST* revList) {
	RESTAURANT res;
	if (getCurrentItemDataRestaurantList(resList, &res) == OK) {
		printf("-----------------------------------------\n");
		printf("- NAME:       %s\n- ADDRESS:    %s\n- TYPE:       %s\n", res.name, res.address, res.type);
		float score = getOverallScoreForRestaurant(revList, res.id);
		if (score == -1)
			printf("- RATING:     NONE\n");
		else
			printf("- RATING:     %g/10\n", score);
		printf("- DESCRIPTION:\n%s\n", res.description);
		printf("-----------------------------------------\n");}
	else {
		printf("Error while printing specified restaurant base info.\n");}
}

// removes restaurant by its id
int removeRestaurant(RESTAURANT_LIST* resList, REVIEW_LIST* revList, MENU_LIST* menuList, unsigned int id) {
	system("cls");
	printf("-----------------------------------------\n");
	printf("----------DELETING A RESTAURANT----------\n");
	printf("-----------------------------------------\n");
	if (moveCurrentToSearchedIdRestaurantList(resList, id) == OK) {
		printf("-RESTAURANT TO BE DELETED-\n");
		printBaseInfoCurrentRestaurant(resList, revList);
		printf("This restaurant and all information associated with it\nacross all the DBs (menus/reviews) will be deleted.\n");
		int status;
		if (status = acceptOperation()) {
			removeCurrentItemRestaurantList(resList); // CHECK WORKING
			removeAllItemsWithResIdReviewList(revList, id); // CHECK WORKING
			removeAllItemsWithResIdMenuList(menuList, id); // CHECK WORKING
			fixIdSequenceMenuList(menuList); // CHECK WORKING
			fixIdSequenceReviewList(revList); // CHECK WORKING
			fixRestaurantIdSequenceFixEveryLink(resList, revList, menuList); // CHECK WORKING
		}
		pressEnterToContinue();
		return status;
	}
	else {
		printf("The specified restaurant can not be found.\n");
		return 1;
	}
}
// fixes the ids of the restaurants in db and the links to the restaurant db from review and menu list
void fixRestaurantIdSequenceFixEveryLink(RESTAURANT_LIST* resList, REVIEW_LIST* revList, MENU_LIST* menuList) {
	if (resList->length == 0)
		return;
	resList->current = resList->head;
	unsigned int index = 0;
	do {
		unsigned int prevIndex = 0;
		if (resList->current->data.id != index) {
			prevIndex = resList->current->data.id;
			resList->current->data.id = index;

			// FIX EVERY LINK IN REVIEW
			if (revList->length != 0) {
				revList->current = revList->head;
				do {
					if (revList->current->data.res_id == prevIndex) {
						revList->current->data.res_id = index;}
				} while (goToNextItemReviewList(revList) != ERR_NO_NEXT);
			}

			// FIX EVERY LINK IN MENU
			if (menuList->length != 0) {
				menuList->current = menuList->head;
				do {
					if (menuList->current->data.res_id == prevIndex) {
						menuList->current->data.res_id = index;
					}
				} while (goToNextItemMenuList(menuList) != ERR_NO_NEXT);
			}
		}
		index++;
	} while (goToNextItemRestaurantList(resList) != ERR_NO_NEXT);
}

// prints the database of restaurants as a table
void printTableOfRestaurants(RESTAURANT_LIST* resList, REVIEW_LIST* revList) {
	printf("------------------------------------------------------------------------------------------------------------------\n");
	printf("----ID----|------------NAME--------------|------------------ADDRESS---------------|---------TYPE-------|--RATING--\n");
	printf("------------------------------------------------------------------------------------------------------------------\n");
	if (resList->length == 0)
		printf("THERE AREN'T ANY RESTAURANTS IN THE DATABASE\n");
	else {
		resList->current = resList->head;
		do {
			RESTAURANT res;
			if (getCurrentItemDataRestaurantList(resList, &res) != OK)
				printf("Failed to retrieve data for this item.\n");
			else {
				printf("%u", res.id);
				unsigned int digits = 0, number = res.id;
				if (number == 0) number++;
				while (number > 0) {
					digits++;
					number /= 10;
				}
				float score = getOverallScoreForRestaurant(revList, res.id);
				for (int i = 0; i < (11 - (int)(digits)); i++) printf(" ");
				printf("%s", res.name);
				for (int i = 0; i < (sizeof(res.name) - strlen(res.name)); i++) printf(" ");
				printf("%s", res.address);
				for (int i = 0; i < (sizeof(res.address) - strlen(res.address)); i++) printf(" ");
				printf("%s", res.type);
				for (int i = 0; i < (sizeof(res.type) - strlen(res.type)); i++) printf(" ");
				if (score == -1)
					printf("NONE\n");
				else
					printf("%g/10\n", score);
			}
		} while (goToNextItemRestaurantList(resList) != ERR_NO_NEXT);
	}
	printf("------------------------------------------------------------------------------------------------------------------\n");
}

// prints info about meals and reviews of the current restaurant
void printSpecialInfoCurrentRestaurant(RESTAURANT_LIST* resList, REVIEW_LIST* revList, MENU_LIST* menuList, unsigned int id) {
	RESTAURANT res;
	if (getCurrentItemDataRestaurantList(resList, &res) == OK) {
		unsigned int totalReviews = 0, totalMeals = 0;
		printf("=========================================\n");
		printf("-RESTAURANT REVIEWS\n");
		if (revList->current != NULL) {
			revList->current = revList->head;
			do {
				if (revList->current->data.res_id == id) {
					printBaseInfoCurrentReview(revList);
					totalReviews++;
				}
			} while (goToNextItemReviewList(revList) != ERR_NO_NEXT);
			if (totalReviews > 0) {
				printf("There is a total of %u reviews.\n", totalReviews);
			}
			else {
				printf("There are no reviews for this restaurant.\n");
			}
		}
		else {
			printf("There are no reviews for this restaurant.\n");
		}
		
		printf("=========================================");
		printf("\n=========================================\n");
		printf("-RESTAURANT MENU\n");
		if (menuList->current != NULL) {
			menuList->current = menuList->head;
			do {
				if (menuList->current->data.res_id == id) {
					printBaseInfoCurrentMenu(menuList);
					totalMeals++;
				}
			} while (goToNextItemMenuList(menuList) != ERR_NO_NEXT);
			if (totalMeals > 0) {
				printf("There is a total of %u meals in this menu.\n", totalMeals);
			}
			else {
				printf("There is no menu for this restaurant.\n");
			}
		}
		else {
			printf("There is no menu for this restaurant.\n");
		}
		
		printf("=========================================\n");

	}
	else {
		printf("Error while printing specified restaurant extended info.\n");}
}

// prints both base and special info about current restaurant
void printAllInfoAboutRestaurant(RESTAURANT_LIST* resList, REVIEW_LIST* revList, MENU_LIST* menuList, unsigned int id) {
	system("cls");
	printf("-----------------------------------------\n");
	printf("------RESTAURANT DETAILED OVERVIEW-------\n");

	if (moveCurrentToSearchedIdRestaurantList(resList, id) == OK) {
		printBaseInfoCurrentRestaurant(resList, revList);
		printSpecialInfoCurrentRestaurant(resList, revList, menuList, id);
	}
	else {
		printf("Restaurant specified can not be found.\n");
	}
}