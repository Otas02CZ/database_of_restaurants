#include "work_with_restaurants.h"

void addRestaurant(RESTAURANT_LIST* resList) {
	unsigned int id = resList->length;
	char name[31], address[41], type[21], description[201];
	printf("--------------------------------------\n");
	printf("---------ADDING A RESTAURANT----------\n");
	printf("--------------------------------------\n");
	printf("Specify the name please:\nInput 30 chars max: ");
	getStringInputUntilNewline(name, sizeof(name));
	printf("Specify the address please:\nInput 40 chars max: ");
	getStringInputUntilNewline(address, sizeof(address));
	printf("Specify the restaurant type [ceska, .]:\nPlease input 20 chars max: ");
	getStringInputUntilNewline(type, sizeof(type));
	printf("Please write a brief description:\nUse 200 chars max, newlines are allowed: ");
	getStringInputUntilEOF(description, sizeof(description));
	RESTAURANT res = createRestaurant(id, name, address, type, description);
	printf("--------------------------------------\n");
	if (addItemToEndRestaurantList(resList, res) == OK)
		printf("Restaurant successfully added to the database.\n");
	else
		printf("Error while adding the restaurant to the database.\n");
}

void editRestaurant(RESTAURANT_LIST* resList, unsigned int id) {
	printf("---------------------------------------\n");
	printf("---------EDITING A RESTAURANT----------\n");
	printf("---------------------------------------\n");
	
	if (moveCurrentToSearchedIdRestaurantList(resList, id) == OK) {
		printf("-EDITED RESTAURANT-\n");
		printBaseInfoCurrentRestaurant(resList);
		unsigned int id = resList->length;
		char name[31], address[41], type[21], description[201];
		printf("Specify the new name please:\nInput 30 chars max: ");
		getStringInputUntilNewline(name, sizeof(name));
		printf("Specify the new address please:\nInput 40 chars max: ");
		getStringInputUntilNewline(address, sizeof(address));
		printf("Specify the new restaurant type [ceska, .]:\nPlease input 20 chars max: ");
		getStringInputUntilNewline(type, sizeof(type));
		printf("Please write a new brief description:\nUse 200 chars max, newlines are allowed: ");
		getStringInputUntilEOF(description, sizeof(description));
		RESTAURANT res = createRestaurant(id, name, address, type, description);
		printf("--------------------------------------\n");
		if (editCurrentItemRestaurantList(resList, res) == OK) {
			printf("Restaurant successfully edited.\n");
			printf("-RESULT-\n");
			printBaseInfoCurrentRestaurant(resList);}
		else {
			printf("Error while editing the specified restaurant.\n");}
	}
	else {
		printf("The restaurant selected can not be found.\n");}
}

void printBaseInfoCurrentRestaurant(RESTAURANT_LIST* resList) {
	RESTAURANT res;
	if (getCurrentItemDataRestaurantList(resList, &res) == OK) {
		printf("----------------------------------\n");
		printf("NAME - %s\nADDRESS - %s\nTYPE - %s\nDESCRIPTION -\n%s\n", res.name, res.address, res.type, res.description);
		printf("----------------------------------\n");}
	else {
		printf("Error while printing specified restaurant base info.\n");}
}

void removeRestaurant(RESTAURANT_LIST* resList, REVIEW_LIST* revList, MENU_LIST* menuList, unsigned int id) {
	printf("-----------------------------------------\n");
	printf("----------DELETING A RESTAURANT----------\n");
	printf("-----------------------------------------\n");
	if (moveCurrentToSearchedIdRestaurantList(resList, id) == OK) {
		printf("-RESTAURANT TO BE DELETED-\n");
		printBaseInfoCurrentRestaurant(resList);
		printf("This restaurant and all information associated with it\nacross all the DBs (menus/reviews) will be deleted.\n");
		if (acceptOperation()) {
			printf("Deleting.\n");
			removeCurrentItemRestaurantList(resList); // CHECK WORKING
			removeAllItemsWithResIdReviewList(revList, id); // CHECK WORKING
			removeAllItemsWithResIdMenuList(menuList, id); // CHECK WORKING
			fixIdSequenceMenuList(menuList); // CHECK WORKING
			fixIdSequenceReviewList(revList); // CHECK WORKING
			fixRestaurantIdSequenceFixEveryLink(resList, revList, menuList); // CHECK WORKING
		}
	}
	else {
		printf("The specified restaurant can not be found.\n");}
	
}
// CHECK WORKING
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

void printTableOfRestaurants(RESTAURANT_LIST* resList) {
	printf("--------------------------------------------------------------------------------------------------------\n");
	printf("----ID----|------------NAME--------------|------------------ADDRESS---------------|---------TYPE--------\n");
	printf("--------------------------------------------------------------------------------------------------------\n");
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
				for (int i = 0; i < (11 - digits); i++) printf(" ");
				printf("%s", res.name);
				for (int i = 0; i < (sizeof(res.name) - strlen(res.name)); i++) printf(" ");
				printf("%s", res.address);
				for (int i = 0; i < (sizeof(res.address) - strlen(res.address)); i++) printf(" ");
				printf("%s\n", res.type);}
		} while (goToNextItemRestaurantList(resList) != ERR_NO_NEXT);
	}
	printf("--------------------------------------------------------------------------------------------------------\n");
}

// printAllInfoAboutRestaurant
// printSpecialInfoCurrentRestaraunt