#include "src/overlays/ov001/FieldUiPatterns.h"

/* Keep these byte-sized tables in one input section: two start at odd addresses. */
const u8 gShortLayoutRowsA[5][5] = {
    {6, 6, 5, 4, 3},
    {15, 15, 15, 15, 15},
    {0, 0, 0, 0, 0},
    {7, 7, 7, 7, 7},
    {8, 8, 8, 8, 8},
};

const u8 gShortLayoutRowsB[6][5] = {
    {6, 6, 5, 4, 3},
    {11, 11, 11, 11, 11},
    {11, 11, 12, 13, 14},
    {7, 7, 7, 7, 7},
    {8, 8, 8, 8, 8},
    {0, 0, 0, 0, 0},
};

const u8 gShortLabelRows[6][7] = {
    {1, 6, 6, 5, 4, 3, 1},
    {1, 15, 15, 15, 15, 15, 1},
    {1, 1, 1, 1, 1, 1, 1},
    {0, 1, 1, 1, 1, 1, 0},
    {1, 7, 7, 7, 7, 7, 1},
    {1, 8, 8, 8, 8, 8, 1},
};

const u8 gShortLabelRowAlignment = 0;
