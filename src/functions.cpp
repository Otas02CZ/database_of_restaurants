//Author        : Otakar Koci @Otas02CZ 247555
//Description   : BUT - BPC-PC1T - semestral project
//YEAR          : 2022

#include "functions.h"

// prints info about expected files with dbs, called when problems with db loading are present
void printInfoExpectedFiles(char* resPath, char* revPath, char* menuPath) {
    printf("The application expected to find DB files at this location:\n  %s\n  %s\n  %s\nPlease check the files are there and create them mannualy.\n", resPath, revPath, menuPath);
    printf("If the locations of the files are specified only by their respective names, then it means that these should be in the folder with the executable.\n");
    printf("You can also force the app to try to recreate empty files by running the app with argument '--forceEmptyDBCreation'.\n");
}

// forces empty db creation - all db files are recreated as empty files
int forceEmptyDBCreation(char* resPath, char* revPath, char* menuPath) {
    FILE* creator = fopen(resPath, "w");
    if (creator == NULL)
        return ERR;
    fclose(creator);
    if ((creator = fopen(revPath, "w")) == NULL)
        return ERR;
    fclose(creator);
    if ((creator = fopen(menuPath, "w")) == NULL)
        return ERR;
    fclose(creator);
    printf("Empty DBs for all the data types were successfully recreated.\n");
    pressEnterToContinue();
    return OK;
}

// check whether to recreate the db files as empty files, based on given arguments from command line
int checkForceEmpyDBCreation(char** argc, int argv, char* resPath, char* revPath, char* menuPath) {
    if (argv == 2) {
        if (strcmp(argc[1], "--forceEmptyDBCreation") == 0) {
            return forceEmptyDBCreation(resPath, revPath, menuPath);
        }
    }
    return OK;
}

// wait until user presses enter
void pressEnterToContinue() {
    printf("Press enter to continue: ");
    char symbol = 0;
    while (symbol != '\r' && symbol != '\n') {
        symbol = getchar();
    }
}

// consumes remaining input, used only once, in most of the cases, the functions handle excesive input on their own
void consumeInput() {
    char symbol;
    while (symbol = getchar()) {
        if (symbol == EOF || symbol == '\0' || symbol == '\n')
            break;
    }
}


// waits for numeric input, as long as the user inputs something else than an integer
int getNumericInput() {
    int number;
    while (scanf("%d", &number) != 1)
        while (getchar() != '\n');
    while (getchar() != '\n');
    return number;
}

// checks whether a given character is on the allowed chars list -> input checking
bool isCharacterAllowed(char symbol) {
    if (isdigit(symbol))
        return true;
    if (isalpha(symbol))
        return true;
    char allowedChar[] = "/*-+,.!=%()[]{}<>: ";
    for (int i = 0; i < strlen(allowedChar); i++) {
        if (symbol == allowedChar[i])
            return 1;
    }
    if (symbol == '\n')
        return 1;
    return false;
}

// function to read users input until ; or EOF is given
void getStringInputUntilEOF(char* output, unsigned int maxSize) {
    unsigned int index = 0;
    char symbol;

    while (symbol = getchar()) {
        if (symbol == EOF || symbol == ';')
            break;
        if (index == maxSize - 2) {
            while (symbol = getchar()) {
                if (symbol == EOF || symbol == '\0' || symbol == ';')
                    break;
            }
            break;
        }
        if (isCharacterAllowed(symbol)) {
            output[index] = symbol;
            index++;
        }   
    }
    while (symbol = getchar()) {
        if (symbol == '\n' || symbol == ';' || symbol == '\0' || symbol == EOF)
            break;
    }
    output[index] = '\0';
}

// function to read users input until \n is given
void getStringInputUntilNewline(char* output, unsigned int maxSize) {
    unsigned int index = 0;
    char symbol;

    while (symbol = getchar()) {
        if (symbol == EOF || symbol == '\n' || symbol == '\0')
            break;
        if (index == maxSize - 2) {
            while (symbol = getchar()) {
                if (symbol == EOF || symbol == '\n' || symbol == '\0')
                    break;}
            break;
        }
        if (isCharacterAllowed(symbol)) {
            output[index] = symbol;
            index++;
        }
    }
    output[index] = '\0';
}

// function which waits for the users approval or disapproval of a previous operation
bool acceptOperation() {
    printf("Do you want to continue or abort? [y/any]: ");
    char symbol, other;
    scanf("%c", &symbol);
    while (other = getchar()) {
        if (other == EOF || other == '\n' || other == '\0')
            break;
    }
    switch (tolower(symbol)) {
    case 'y':
        printf("Operation confirmed.\n");
        return true;
    default:
        printf("Operation aborted.\n");
        return false;
    }
}

// prints basic app info
void printAppInfo(RESTAURANT_LIST* res, REVIEW_LIST* rev, MENU_LIST* menu) {
    clearScreen();
    printf("--------------------------------\n");
    printf("-----------APP OVERVIEW---------\n");
    printf("--------------------------------\n");
    printf("-AUTHOR - Otakar Koci @Otas02CZ\n");
    printf("-BUT Student - ID - 247555\n");
    printf("-DATE- 2022\n");
    printf("-VERSION - %s\n", VERSION);
    printf("-COMPILED FOR - %s\n", OS);
    printf("-OVERVIEW -\n");
    printf("A simple database application for managing a DB\nof restaurants, menus with meals and reviews.\n");
    printf("---------------------------------\n");
    printf("-TOTAL RESTAURANTS- %u\n-RESTAURANTS IN MEMORY- %zd B\n", res->length, (res->length * sizeof(RESTAURANT_ITEM) + sizeof(RESTAURANT_LIST)));
    printf("---------------------------------\n");
    printf("-TOTAL REVIEWS- %u\n-REVIEWS IN MEMORY- %zd B\n", rev->length, (rev->length * sizeof(REVIEW_ITEM) + sizeof(REVIEW_LIST)));
    printf("---------------------------------\n");
    printf("-TOTAL MEALS- %u\n-MEALS IN MEMORY- %zd B\n", menu->length, (menu->length * sizeof(MENU_ITEM) + sizeof(MENU_LIST)));
    printf("---------------------------------\n");
    printf("Allowed inputs are letters, digits, /*-+,.!=%%()[]{}:<>space and sometimes new lines.\nAll other inputs are ignored.\n");
    printf("---------------------------------\n");
    pressEnterToContinue();
}

// converts string to lower case
void convertStringToLowerCase(char* text) {
    for (unsigned int i = 0; i < strlen(text); i++)
        text[i] = tolower(text[i]);
}

// prints a text representation of the current sort method
void printLineAboutCurrentSortMethod(unsigned int sortMethod) {
    switch (sortMethod) {
    case ID:
        printf("Currently sorting by restaurant ID.\n");
        break;
    case NAME:
        printf("Currently sorting by restaurant NAME.\n");
        break;
    case RATING:
        printf("Currently sorting by restaurant RATING.\n");
        break;
    }
}

void printLineAboutSearching(bool usingSearch, char* searchQuery) {
    if (usingSearch) {
        printf("Currently only restaurants that follow the search query \"%s\" are shown.\n", searchQuery);}
    else {
        printf("All restaurants are shown. No search is enabled.\n");}
}

void clearScreen() {
    system(CLEAR);
}
