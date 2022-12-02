#include "imports.h"
#include "restaurant_list.h"
#include "review_list.h"
#include "menu_list.h"

int main() {
    printf("Ahoj");
    RESTAURANT_LIST* list = createRestaurantList();
    if (list == NULL)
        return 0;
    char restaurantDataFilePath[200] = "I:/Git/restaurant.txt";
    //RESTAURANT res;
    //char name[30] = "Primavera", address[40] = "Zamecka 100", description[200] = "Restauracia dobra";
    //addItemToEndRestaurantList(list, createRestaurant(0, name, address, 0, description));
    +
    printf("%d", loadFromFileRestaurantList(list, restaurantDataFilePath));
    RESTAURANT res;
    printf("%d", getCurrentItemDataRestaurantList(list, &res));
    printf("%s", res.description);
    printf("Hi");
    /*goToNextItemRestaurantList(list);
    res = getCurrentItemDataRestaurantList(list);
    printf("%s", res.description);
    printf("HI");
    */
    printf("%d", saveToFileRestaurantList(list, restaurantDataFilePath));
    printf("Hi");
    list->current = list->head;
    do {
        RESTAURANT res2;
        printf("%d", getCurrentItemDataRestaurantList(list, &res2));
        printf("%u %s %s %u %s\n", res2.id, res2.name, res2.address, res2.type, res2.description);
    } while (goToNextItemRestaurantList(list) == OK);

    if (moveCurrentToSearchedIdRestaurantList(list, 1) == OK) {
        RESTAURANT res2;
        printf("%d", getCurrentItemDataRestaurantList(list, &res2));
        printf("%u %s %s %u %s\n", res2.id, res2.name, res2.address, res2.type, res2.description);
    }
    else {
        printf("Not found index 1.");
    }

    eraseRestaurantList(list);
    return 0;
}

