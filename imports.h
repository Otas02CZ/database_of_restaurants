#pragma once

#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

enum {
    OK = 0,
    ERR = 1,
    ERR_ALLOC = 2,
    ERR_LOAD = 3,
    ERR_SAVE = 4,
    ERR_NOT_FOUND = 5,
    ERR_NO_NEXT = 6
};