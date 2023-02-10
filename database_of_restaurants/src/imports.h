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
    OK,
    ERR,
    ERR_ALLOC,
    ERR_LOAD,
    ERR_SAVE,
    ERR_NOT_FOUND,
    ERR_NO_NEXT,
    ID,
    NAME,
    RATING,
    SYSTEM_WIN,
    SYSTEM_LINUX,
    SYSTEM_UNKNOWN,
};