# CMakeList.txt : CMake project for database_of_restaurants, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("database_of_restaurants")

# Add source to this project's executable.
add_executable (database_of_restaurants "database_of_restaurants.cpp" "database_of_restaurants.h"       "imports.h" "restaurant_list.h" "restaurant_list.cpp" "review_list.h" "review_list.cpp"    "menu_list.cpp" "menu_list.h" "functions.cpp" "functions.h"   "work_with_all_lists.h" "work_with_all_lists.cpp" "work_with_restaurants.cpp" "work_with_restaurants.h" "work_with_reviews.h" "work_with_reviews.cpp" "work_with_menus.cpp" "work_with_menus.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET database_of_restaurants PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
