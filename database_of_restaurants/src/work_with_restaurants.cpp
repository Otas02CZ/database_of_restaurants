//Author        : Otakar Koci @Otas02CZ 247555
//Description   : BUT - BPC-PC1T - semestral project
//YEAR          : 2022

#include "work_with_restaurants.h"


// gets input from the user and adds restaurant at the end of the list
void addRestaurant(RESTAURANT_LIST* resList) {
	unsigned int id = resList->length;
	char name[31], address[41], type[21], description[201];
	clearScreen();
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
	clearScreen();
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
	clearScreen();
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
				if (!res.visible)
					continue;
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
	clearScreen();
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

// function to search by name in restaurants, by given searchQuery
void searchByNameInRestaurants(RESTAURANT_LIST* resList, char* searchQuery) {
	if (resList->length == 0)
		return;
	resList->current = resList->head;
	char currentName[31];
	convertStringToLowerCase(searchQuery);


	do {
		strcpy(currentName, resList->current->data.name);
		convertStringToLowerCase(currentName);
		if (strstr(currentName, searchQuery) != NULL)
			resList->current->data.visible = true;
		else
			resList->current->data.visible = false;
	} while (goToNextItemRestaurantList(resList) != ERR_NO_NEXT);
}

// Makes all restaurants visible - removes the effect of searching
void turnAllRestaurantsVisibility(RESTAURANT_LIST* resList, bool value) {
	if (resList->length == 0)
		return;
	resList->current = resList->head;

	do {
		resList->current->data.visible = value;
	} while (goToNextItemRestaurantList(resList) != ERR_NO_NEXT);
}

// Swap the data of two given restaurant items
void swapRestaurants(RESTAURANT_ITEM* res1, RESTAURANT_ITEM* res2) {
	RESTAURANT temp = res1->data;
	res1->data = res2->data;
	res2->data = temp;
}

// Sort restaurants by given specifier (ID, NAME, RATING), the data of the linked nodes are swaped, not the nodes themselves
void sortRestaurantListByGivenSpecifier(RESTAURANT_LIST* resList, REVIEW_LIST* revList, unsigned int specifier) {
	if (resList->length == 0)
		return;
	resList->current = resList->head;
	RESTAURANT_ITEM *i, *j;
	i = resList->head;
	j = resList->head;
	while (i != NULL) {
		while (j->next != NULL) {
			switch (specifier) {
			case ID:
				if (j->data.id > j->next->data.id) {
					swapRestaurants(j, j->next);}
				break;
			case NAME:
				if (strcmp(j->data.name, j->next->data.name) > 0) {
					swapRestaurants(j, j->next);}
				break;
			case RATING:
				if (getOverallScoreForRestaurant(revList, j->data.id) < getOverallScoreForRestaurant(revList, j->next->data.id)) {
					swapRestaurants(j, j->next);}
				break;
			}
			j = j->next;
		}
		j = resList->head;
		i = i->next;
	}
}

// Prints overview of all menu items of all restaurants also applies searchQuery for meal name if requiered
void printMenuOverviewForAllRestaurantsWithSearch(RESTAURANT_LIST* resList, REVIEW_LIST* revList, MENU_LIST* menuList, char* searchQuery) {
	clearScreen();
	printf("-------------------------------\n");
	printf("---------MENU OVERVIEW---------\n");
	printf("-------------------------------\n");

	if (resList->length == 0) {
		printf("THERE ARE NO RESTAURANTS.\n");
		printf("-------------------------------\n");
		return;
	}
	if (menuList->length == 0) {
		printf("THERE ARE NO MENUS.\n");
		printf("-------------------------------\n");
		return;
	}

	resList->current = resList->head;
	convertStringToLowerCase(searchQuery);
	do {
		menuList->current = menuList->head;
		printf("\n==========================================\n");
		printf("--RESTAURANT\n");
		printBaseInfoCurrentRestaurant(resList, revList);
		printf("-MENU-\n");
		unsigned int menuCount = 0;
		do {
			if (resList->current->data.id == menuList->current->data.res_id) {
				if (searchQuery == ";" || strlen(searchQuery) == 0) {
					printBaseInfoCurrentMenu(menuList);
					menuCount++;
				}
				else {
					char mealName[31];
					strcpy(mealName, menuList->current->data.name);
					convertStringToLowerCase(mealName);
					if (strstr(mealName, searchQuery) != NULL) {
						printBaseInfoCurrentMenu(menuList);
						menuCount++;}
				}
			}
		} while (goToNextItemMenuList(menuList) != ERR_NO_NEXT);
		if (menuCount == 0)
			printf("This restaurant has no menu, or there isn't a meal that would satisfy the search query.\n");
		else {
			printf("Meals in menu %u.\n", menuCount);
		}
		printf("==========================================\n");

	} while (goToNextItemRestaurantList(resList) != ERR_NO_NEXT);

	printf("-------------------------------\n");
}