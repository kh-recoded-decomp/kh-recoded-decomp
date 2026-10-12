#include "nitro/types.h"

/* Each unlocked-area bit has base, variant-1 and variant-2 archive IDs. */
const u8 gUnlockedAreaSoundArchiveIds[18][3] = {
    {3, 20, 34}, {4, 21, 35}, {9, 26, 40}, {12, 29, 43},
    {5, 22, 36}, {10, 27, 41}, {11, 28, 42}, {7, 24, 42},
    {8, 25, 39}, {6, 23, 37}, {13, 30, 44}, {15, 32, 46},
    {16, 33, 47}, {14, 31, 45},
    {17, 255, 255}, {18, 255, 255}, {19, 255, 255},
    /* Three alignment bytes, not an eighteenth unlocked-area entry. */
    {0, 0, 0}
};
