//Author        : Otakar Koci @Otas02CZ 247555
//Description   : BUT - BPC-PC1T - semestral project
//YEAR          : 2022

#pragma once

#ifdef _WIN32
#define CLEAR "cls"
#define OS "windows"
#else
#define CLEAR "clear"
#define OS "linux"
#endif

#define VERSION "v1.1"

#include "imports.h"
#include "restaurant_list.h"
#include "menu_list.h"
#include "review_list.h"

void printInfoExpectedFiles(char* resPath, char* revPath, char* menuPath);
int forceEmptyDBCreation(char* resPath, char* revPath, char* menuPath);
int checkForceEmpyDBCreation(char** argc, int argv, char* resPath, char* revPath, char* menuPath);
void pressEnterToContinue();
void consumeInput();
int getNumericInput();
void getStringInputUntilEOF(char* output, unsigned int maxSize);
void getStringInputUntilNewline(char* output, unsigned int maxSize);
bool acceptOperation();
void printAppInfo(RESTAURANT_LIST* res, REVIEW_LIST* rev, MENU_LIST* menu);
void convertStringToLowerCase(char* text);
void printLineAboutCurrentSortMethod(unsigned int sortMethod);
void printLineAboutSearching(bool usingSearch, char* searchQuery);
void clearScreen();