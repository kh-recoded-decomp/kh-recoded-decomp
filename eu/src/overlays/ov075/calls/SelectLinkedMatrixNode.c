#include "nitro/types.h"

typedef struct MatrixNode {
    u16 cell;
    u8 kind;
    s8 linkId;
    u8 unknown04[8];
    s16 links[4];
} MatrixNode;

typedef struct MatrixMap {
    u8 unknown0000[0x18];
    MatrixNode *linked[(0x98 - 0x18) / 4];
    u8 *width;
    MatrixNode *cells[(0x2be8 - 0x9c) / 4];
    u8 cellLevels[1];
} MatrixMap;

typedef struct SaveData {
    u8 unknown0000[0x2c5c];
    u8 linkFlags[0x2c67 - 0x2c5c];
    u8 level;
} SaveData;

typedef struct MatrixMenu {
    u8 unknown00000[0x28];
    s16 cursorX;
    s16 cursorY;
    u8 unknown0002c[0x12dd0 - 0x2c];
    MatrixMap *map;
    MatrixNode *current;
} MatrixMenu;

#define CHECK_MATRIX_OFFSET(type, member, offset, label) \
    typedef char label[(u32)&((type *)0)->member == (offset) ? 1 : -1]
typedef char MatrixNodeIsTwentyBytes[sizeof(MatrixNode) == 20 ? 1 : -1];
CHECK_MATRIX_OFFSET(MatrixNode, links, 0xc, MatrixNodeLinksOffset);
CHECK_MATRIX_OFFSET(MatrixMap, linked, 0x18, MatrixLinkedNodesOffset);
CHECK_MATRIX_OFFSET(MatrixMap, width, 0x98, MatrixWidthOffset);
CHECK_MATRIX_OFFSET(MatrixMap, cells, 0x9c, MatrixCellsOffset);
CHECK_MATRIX_OFFSET(MatrixMap, cellLevels, 0x2be8, MatrixCellLevelsOffset);
CHECK_MATRIX_OFFSET(SaveData, level, 0x2c67, MatrixSaveLevelOffset);
CHECK_MATRIX_OFFSET(MatrixMenu, cursorX, 0x28, MatrixCursorXOffset);
CHECK_MATRIX_OFFSET(MatrixMenu, map, 0x12dd0, MatrixMapOffset);
CHECK_MATRIX_OFFSET(MatrixMenu, current, 0x12dd4, MatrixCurrentNodeOffset);
#undef CHECK_MATRIX_OFFSET

extern SaveData *data_0205fe0c;
extern int GetPackedBitMask(const void *bits, int index);

static inline int GetLinkedNodeIndex(MatrixNode *node, MatrixNode *base)
{
    if (node >= base) {
        return node - base;
    }
    return -1;
}

static inline BOOL IsMatrixLinkUnlocked(SaveData *save, int index)
{
    return GetPackedBitMask(save->linkFlags, index) ? TRUE : FALSE;
}

MatrixNode *SelectLinkedMatrixNode(MatrixMenu *menu, int direction)
{
    MatrixNode *current = menu->current;
    int neighbor = current->links[direction];
    s16 width = *menu->map->width;
    MatrixMap *map = menu->map;
    MatrixNode *result = current;
    MatrixNode *selected;
    int linkIndex;
    BOOL withinLevel;

    if (neighbor >= 0) {
        result = map->cells[neighbor];
        if (result->kind == 0x19) {
            return current;
        }
        selected = result;
        linkIndex = GetLinkedNodeIndex(result, map->linked[0]);
        withinLevel = map->cellLevels[result->cell] <= data_0205fe0c->level;
        if (linkIndex < 0) {
            linkIndex = result->linkId;
        }
        if (linkIndex >= 0 && !IsMatrixLinkUnlocked(data_0205fe0c, linkIndex) && withinLevel) {
            result = NULL;
            selected = menu->map->linked[linkIndex];
        }
        if (withinLevel) {
            menu->cursorX = selected->cell % width;
            menu->cursorY = selected->cell / width;
            menu->current = selected;
        } else {
            result = menu->current;
        }
    }
    return result;
}
