#include "restaurant_list.h"
#include "imports.h"

int main() {

    RESTAURANT_LIST* list = createRestaurantList();
    char restaurantDataFilePath[200] = "I:/Git/restaurant.txt";
    //RESTAURANT res;
    //char name[30] = "Primavera", address[40] = "Zamecka 100", description[200] = "Restauracia dobra";
    //addItemToEndRestaurantList(list, createRestaurant(0, name, address, 0, description));
    
    printf("%d", loadFromFileRestaurantList(list, restaurantDataFilePath));
    RESTAURANT res;
    res = getCurrentItemDataRestaurantList(list);
    printf("%s", res.description);
    printf("Hi");
    /*goToNextItemRestaurantList(list);
    res = getCurrentItemDataRestaurantList(list);
    printf("%s", res.description);
    printf("HI");
    */
    printf("%d", saveToFileRestaurantList(list, restaurantDataFilePath));
    printf("Hi");
    eraseRestaurantList(list);
    return 0;
}

