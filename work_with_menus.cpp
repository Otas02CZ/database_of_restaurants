//Author        : Otakar Koci @Otas02CZ 247555
//Description   : BUT - BPC-PC1T - semestral project
//YEAR          : 2022

#include "work_with_menus.h"


// Code to get users inputs for adding a new meal and add it to the linked list at the end of it
void addMenu(MENU_LIST* menuList, RESTAURANT_LIST* resList, REVIEW_LIST* revList, unsigned int resId) {
	unsigned int id = menuList->length;
	char name[31], description[201];
	system("cls");
	printf("--------------------------------------\n");
	printf("------------ADDING A MEAL-------------\n");
	printf("--------------------------------------\n");

	if (moveCurrentToSearchedIdRestaurantList(resList, resId) == OK) {
		printf("-ADDING A MEAL FOR RESTAURANT-\n");
		printf("For information about allowed inputs please check the APP INFO\n");
		printBaseInfoCurrentRestaurant(resList, revList);
		printf("Specify the meal name please:\nInput 30 chars max: ");
		getStringInputUntilNewline(name, sizeof(name));
		printf("Please write a short description of the meal\nInput 400 chars max newlines are allowed\nTo end your input type ; or ctrl-Z on a new line:\n");
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

// Code to get users input and edit specified meal
void editMenu(MENU_LIST* menuList, RESTAURANT_LIST* resList, REVIEW_LIST* revList, unsigned int id, unsigned int resId) {
	system("cls");
	printf("---------------------------------------\n");
	printf("------------EDITING A MEAL-------------\n");
	printf("---------------------------------------\n");

	if (moveCurrentToSearchedIdRestaurantList(resList, resId) == OK) {
		printf("-EDITING A MEAL FOR RESTAURANT-\n");
		printBaseInfoCurrentRestaurant(resList, revList);
		if (moveCurrentToSearchedIdMenuList(menuList, id) == OK) {
			printf("-EDITED REVIEW-\n");
			printBaseInfoCurrentMenu(menuList);
			char name[31], description[201];
			printf("For information about allowed inputs please check the APP INFO\n");
			printf("Specify the new meal name please:\nInput 30 chars max: ");
			getStringInputUntilNewline(name, sizeof(name));
			printf("Please write a short description of the meal\nInput 400 chars max newlines are allowed\nTo end your input type ; or ctrl-Z on a new line:\n");
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

// Code to remove the specified meal from the linked list, check users approval
void removeMenu(MENU_LIST* menuList, RESTAURANT_LIST* resList, REVIEW_LIST* revList, unsigned int id, unsigned int resId) {
	system("cls");
	printf("-----------------------------------------\n");
	printf("-------------DELETING A MEAL-------------\n");
	printf("-----------------------------------------\n");

	if (moveCurrentToSearchedIdRestaurantList(resList, resId) == OK) {
		printf("-REMOVING A MEAL FOR RESTAURANT-\n");
		printBaseInfoCurrentRestaurant(resList, revList);
		if (moveCurrentToSearchedIdMenuList(menuList, id) == OK) {
			printf("-REVIEW TO BE REMOVED-\n");
			printBaseInfoCurrentMenu(menuList);
			printf("This meal will be deleted.\n");
			if (acceptOperation()) {
				printf("Deleting.\n");
				removeCurrentItemMenuList(menuList);
				fixIdSequenceMenuList(menuList);
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

// Prints base information about the menu item at the current location of the linked list current pointer
void printBaseInfoCurrentMenu(MENU_LIST* menuList) {
	MENU menu;
	if (getCurrentItemDataMenuList(menuList, &menu) == OK) {
		printf("----------------------------------\n");
		printf("- NAME: %s\n- DESCRIPTION:\n%s\n", menu.name, menu.description);
		printf("----------------------------------\n");
	}
	else {
		printf("Error while printing specified menu base info.\n");
	}
}

// Print a table of all menus that are linked to given restaurant
unsigned int printTableOfAllMenusOfSpecifiedRestaurant(MENU_LIST* menuList, unsigned int resId) {
	printf("----------------------------------------\n");
	printf("----ID----|------------NAME-------------\n");
	printf("----------------------------------------\n");
	unsigned int totalMenus = 0;
	if (menuList->length == 0) {
		printf("THERE IS NO MENU FOR THIS RESTAURANT\n");
		return 0;
	}
	else {
		menuList->current = menuList->head;
		do {
			MENU menu;
			if (getCurrentItemDataMenuList(menuList, &menu) == OK) {
				if (menu.res_id == resId) {
					totalMenus++;
					printf("%u", menu.id);
					unsigned int digits = 0, number = menu.id;
					if (number == 0) number++;
					while (number > 0) {
						digits++;
						number /= 10;
					}
					for (int i = 0; i < (11 - (int)(digits)); i++) printf(" ");
					printf("%s\n", menu.name);
				}
			}
		} while (goToNextItemMenuList(menuList) != ERR_NO_NEXT);
	}
	if (totalMenus == 0)
		printf("THERE IS NO MENU FOR THIS RESTAURANT\n");
	printf("----------------------------------------------------\n");
	return totalMenus;
}

// Checks whether specified menu is linked to a given restaurant
unsigned int isSpecifiedMenuUnderSpecifiedRestaurant(MENU_LIST* menuList, unsigned int id, unsigned int resId) {
	if (menuList->length == 0) {
		return 0;
	}
	else {
		menuList->current = menuList->head;
		do {
			MENU menu;
			if (getCurrentItemDataMenuList(menuList, &menu) == OK) {
				if (menu.id == id && menu.res_id == resId)
					return 1;
			}
		} while (goToNextItemMenuList(menuList) != ERR_NO_NEXT);
	}
	return 0;
}

