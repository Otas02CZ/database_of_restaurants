#ifndef HEADER_FILE
#define HEADER_FILE

typedef struct RESTAURANT{
    unsigned int        id;
    char                name[30];
    char                address[40];
    unsigned short int  type;
    char                description[200];

}RESTAURANT;

typedef struct REVIEW{
    unsigned int    restaurantId;
    unsigned int    id;
    short int       score;
    char    comment[200];
}REVIEW;

typedef struct FOOD{
    unsigned int    restaurantId;
    unsigned int    id;
    char        name[40];
    char        definition[180];
}FOOD;

#endif