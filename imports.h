//Author        : Otakar Koci @Otas02CZ 247555
//Description   : BUT - BPC-PC1T - semestral project
//YEAR          : 2022

#pragma once

#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

enum {
    OK = 0,
    ERR = 1,
    ERR_ALLOC = 2,
    ERR_LOAD = 3,
    ERR_SAVE = 4,
    ERR_NOT_FOUND = 5,
    ERR_NO_NEXT = 6,
    ID = 7,
    NAME = 8,
    RATING = 9
};