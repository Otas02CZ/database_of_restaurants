#pragma once

#include "imports.h"
#include "restaurant_list.h"
#include "menu_list.h"
#include "review_list.h"

void printInfoExpectedFiles(char* resPath, char* revPath, char* menuPath);
int checkForceEmpyDBCreation(char** argc, int argv, char* resPath, char* revPath, char* menuPath);
void pressEnterToContinue();
void consumeInput();
int getNumericInput();
void getStringInputUntilEOF(char* output, unsigned int maxSize);
void getStringInputUntilNewline(char* output, unsigned int maxSize);
int acceptOperation();