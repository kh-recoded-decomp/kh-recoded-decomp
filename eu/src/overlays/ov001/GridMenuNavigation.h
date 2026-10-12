#ifndef KH_RECODED_GRID_MENU_NAVIGATION_H
#define KH_RECODED_GRID_MENU_NAVIGATION_H

#include "nitro/types.h"

typedef struct GridNavigation {
    s32 lastIndex;
    u8 reserved04[0xc];
    void *windows;
    u16 cellWidth, cellHeight;
    u16 pageRows, rowCount, columnCount;
    u16 x, y, width, height;
    u16 selectedCell, firstRow;
} GridNavigation;

/* Partial view of the mode-menu context; the embedded menu starts at +4. */
typedef struct GridMenu {
    u8 reserved00[8];
    s32 mode;
    u8 reserved0c[0x54 - 0xc];
    GridNavigation grid;
} GridMenu;

typedef struct GridMenuRoot {
    u8 reserved00[4];
    GridMenu menu;
} GridMenuRoot;

typedef enum GridRowDirection {
    GRID_ROW_UP,
    GRID_ROW_DOWN,
    GRID_PAGE_UP,
    GRID_PAGE_DOWN
} GridRowDirection;

#endif
