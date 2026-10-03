#include "nitro/types.h"

typedef struct GridPos {
    s16 x;
    s16 y;
} __attribute__((aligned(4))) GridPos;

typedef struct {
    u16 id;
    u8 kind;
    s8 linkedIndex;
    u8 pad_04[0x10];
} GridEntry;

typedef struct {
    u8 pad_0000[0x18];
    GridEntry *linked[0x20];
    u8 *columnCount;
} GridMap;

typedef struct {
    u8 pad_0000[0x2c5c];
    int flags[1];
} SaveData;

typedef struct {
    u8 pad_00000[0x28];
    GridPos cursor;
    u8 pad_0002c[0x12dd0 - 0x2c];
    GridMap *map;
    GridEntry *current;
} MatrixMenu;

extern SaveData *data_0205fe0c;
extern int GetPackedBitMask(int *bitWords, int bitIndex);
extern GridPos FindNearestReachableNode_020c8eac(GridMap *grid, GridPos pos, GridEntry **outNode, BOOL skipCurrent);
extern void ShowEntryHeaderMessage_020cad14(MatrixMenu *menu, GridEntry *entry);
extern BOOL ShowNextUnlockNotice_020cc9fc(MatrixMenu *menu, BOOL eventMode, BOOL queryOnly);

static inline int GetEntryIndex(GridMap *map, GridEntry *entry)
{
    if (entry >= map->linked[0]) {
        return entry - map->linked[0];
    }
    return -1;
}

void JumpCursorToEntry_020cae58(MatrixMenu *menu, GridEntry *entry, BOOL skipCurrent)
{
    GridMap *map = menu->map;
    int width = *map->columnCount;
    s16 index;
    BOOL reachable;

    index = GetEntryIndex(map, entry);
    if (index < 0 && entry->linkedIndex >= 0 &&
        !(GetPackedBitMask(data_0205fe0c->flags, entry->linkedIndex) ? TRUE : FALSE)) {
        index = entry->linkedIndex;
        entry = menu->map->linked[index];
    }
    reachable = FALSE;
    if (index >= 0 && !(GetPackedBitMask(data_0205fe0c->flags, index) ? TRUE : FALSE)) {
        reachable = TRUE;
    }
    menu->cursor.x = entry->id % width;
    menu->cursor.y = entry->id / width;
    menu->current = entry;
    if (!reachable) {
        menu->cursor = FindNearestReachableNode_020c8eac(menu->map, menu->cursor, &menu->current, skipCurrent);
    }
    ShowEntryHeaderMessage_020cad14(menu, menu->current);
    ShowNextUnlockNotice_020cc9fc(menu, TRUE, FALSE);
}
