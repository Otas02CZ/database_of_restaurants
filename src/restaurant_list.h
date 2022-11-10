#ifndef HEADER_FILE
#define HEADER_FILE

// code functions
// create list, add restaurant, remove, get list, get_ids?, get_restaurant?, delete

typedef struct RESTAURANT{
    unsigned int        id;
    char                name[30];
    char                address[40];
    unsigned short int  type;
    char                description[200];

}RESTAURANT;

#endif