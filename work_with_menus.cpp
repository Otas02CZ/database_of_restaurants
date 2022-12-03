#include "work_with_menus.h"

void addMenu(MENU_LIST* menuList, RESTAURANT_LIST* resList, unsigned int resId) {
	unsigned int id = menuList->length;
	char name[31], description[201];
	printf("--------------------------------------\n");
	printf("------------ADDING A MEAL-------------\n");
	printf("--------------------------------------\n");

	if (moveCurrentToSearchedIdRestaurantList(resList, resId) == OK) {
		printf("-ADDING A MEAL FOR RESTAURANT-\n");
		printBaseInfoCurrentRestaurant(resList);
		printf("Specify the meal name please:\nInput 30 chars max: ");
		getStringInputUntilNewline(name, sizeof(name));
		printf("Please write a short description of the meal:\nInput 200 chars max newlines are allowed: ");
		getStringInputUntilEOF(description, sizeof(description));
		MENU menu = createMenu(id, resId, name, description);
		printf("-----------------------------------\n");
		if (addItemToEndMenuList(menuList, menu) == OK)
			printf("Meal successfully added to the database.\n");
		else {
			printf("Error while adding the meal to the database.\n");}
	}
	else {
		printf("The associated restauant for the meal can not be found.\n");}
}

void editMenu(MENU_LIST* menuList, RESTAURANT_LIST* resList, unsigned int id, unsigned int resId) {
	printf("---------------------------------------\n");
	printf("------------EDITING A MEAL-------------\n");
	printf("---------------------------------------\n");

	if (moveCurrentToSearchedIdRestaurantList(resList, resId) == OK) {
		printf("-EDITING A MEAL FOR RESTAURANT-\n");
		printBaseInfoCurrentRestaurant(resList);
		if (moveCurrentToSearchedIdMenuList(menuList, id) == OK) {
			printf("-EDITED REVIEW-\n");
			printBaseInfoCurrentMenu(menuList);
			char name[31], description[201];
			printf("Specify the new meal name please:\nInput 30 chars max: ");
			getStringInputUntilNewline(name, sizeof(name));
			printf("Please write a short description of the meal:\nInput 200 chars max newlines are allowed: ");
			getStringInputUntilEOF(description, sizeof(description));
			MENU menu = createMenu(id, resId, name, description);
			printf("-----------------------------------\n");
			if (editCurrentItemMenuList(menuList, menu) == OK)
				printf("Meal successfully edited.\n");
			else
				printf("Error while editing the meal.\n");
		}
		else {
			printf("The meal selected can not be found.\n");}
	}
	else {
		printf("The restaraunt associated with the meal can not be found.\n");}
}

void removeMenu(MENU_LIST* menuList, RESTAURANT_LIST* resList, unsigned int id, unsigned int resId) {
	printf("-----------------------------------------\n");
	printf("-------------DELETING A MEAL-------------\n");
	printf("-----------------------------------------\n");

	if (moveCurrentToSearchedIdRestaurantList(resList, resId) == OK) {
		printf("-REMOVING A MEAL FOR RESTAURANT-\n");
		printBaseInfoCurrentRestaurant(resList);
		if (moveCurrentToSearchedIdMenuList(menuList, id) == OK) {
			printf("-REVIEW TO BE REMOVED-\n");
			printBaseInfoCurrentMenu(menuList);
			printf("This meal will be deleted.\n");
			if (acceptOperation()) {
				printf("Deleting.\n");
				removeCurrentItemMenuList(menuList); // CHECK WORKING
				fixIdSequenceMenuList(menuList); // CHECK WORKING
			}
		}
		else {
			printf("Thre selected meal can not be found.\n");
		}
	}
	else {
		printf("The restaurant associated with the meal can not be found.\n");
	}
}

void printBaseInfoCurrentMenu(MENU_LIST* menuList) {
	MENU menu;
	if (getCurrentItemDataMenuList(menuList, &menu) == OK) {
		printf("----------------------------------\n");
		printf("NAME - %s\nDESCRIPTION -\n%s\n", menu.name, menu.description);
		printf("----------------------------------\n");
	}
	else {
		printf("Error while printing specified menu base info.\n");
	}
}