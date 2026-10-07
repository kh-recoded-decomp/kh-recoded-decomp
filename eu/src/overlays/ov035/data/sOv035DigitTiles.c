#include "nitro/types.h"

typedef struct MovieDigitTiles {
    u8 rows[3][5];
    u8 padding;
} MovieDigitTiles;

const MovieDigitTiles sOv035DigitTiles = {
    {
        { 6, 6, 5, 4, 3 },
        { 15, 15, 15, 15, 15 },
        { 8, 8, 8, 8, 8 },
    },
    0,
};
