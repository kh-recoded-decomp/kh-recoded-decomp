#ifndef RECODED_MENU_IMAGE_QUAD_H
#define RECODED_MENU_IMAGE_QUAD_H

#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct MenuImage {
    s16 width;
    s16 height;
    u32 texParams[2];
} MenuImage;

typedef struct {
    u8 columns;
    u8 rows;
    u8 column;
    u8 row;
} CellGrid;

typedef char CellGridIsFourBytes[sizeof(CellGrid) == 4 ? 1 : -1];

typedef struct ImageQuad {
    const MenuImage *image;
    s16 x;
    s16 y;
    fx32 depth;
    u16 texOffsetS;
    u16 texOffsetT;
    u16 width;
    u16 height;
    u16 color;
} ImageQuad;

#endif
