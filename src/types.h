typedef struct RESTAURANT{
    unsigned int        id;
    char                name[30];
    char                address[40];
    unsigned short int  type;
    char                description[200];

}RESTAURANT;

typedef struct REVIEW{
    unsigned int restaurantId;
    unsigned int id;
    float
}