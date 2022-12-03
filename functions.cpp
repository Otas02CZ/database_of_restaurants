#include "functions.h"


void printInfoExpectedFiles(char* resPath, char* revPath, char* menuPath) {
    printf("The application expected to find DB files at this location:\n  %s\n  %s\n  %s\nPlease check the files are there and create them mannualy.\n", resPath, revPath, menuPath);
    printf("You can also force the app to try to recreate empty files by running the app with argument '--forceEmptyDBCreation'.\n");
}

int checkForceEmpyDBCreation(char** argc, int argv, char* resPath, char* revPath, char* menuPath) {
    if (argv == 2) {
        if (strcmp(argc[1], "--forceEmptyDBCreation") == 0) {
            FILE* creator;
            if (fopen_s(&creator, resPath, "w") != 0)
                return ERR;
            fclose(creator);
            if (fopen_s(&creator, revPath, "w") != 0)
                return ERR;
            fclose(creator);
            if (fopen_s(&creator, menuPath, "w") != 0)
                return ERR;
            fclose(creator);
            printf("Empty DBs for all the data types were successfully recreated.\n");
            pressEnterToContinue();
        }
    }
    return OK;
}

void pressEnterToContinue() {
    while (getchar() != '\n')
        printf("Press enter to continue: ");
}

void consumeInput() {
    while (getchar() != '\n');
}

int getNumericInput() {
    int number;
    while (scanf_s("%d", &number) != 1)
        while (getchar() != '\n');
    while (getchar() != '\n');
    return number;
}

void getStringInputUntilEOF(char* output, unsigned int maxSize) {
    unsigned int index = 0;
    char symbol;
    while ((symbol = getchar()) != EOF) {
        if (index == maxSize - 2) {
            while (getchar() != EOF);
            break;
        }
        output[index] = symbol;
        index++;
    }
    output[index] = '\0';
}

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
        output[index] = symbol;
        index++;
    }
    output[index] = '\0';
}

int acceptOperation() {
    printf("Do you want to continue or abort? [y/any]: ");
    char symbol;
    scanf_s("%c", &symbol);
    while (getchar() != EOF);
    switch (tolower(symbol)) {
    case 'y':
        printf("Operation confirmed.\n");
        return 1;
    default:
        printf("Operation aborted.\n");
        return 0;
    }
}
