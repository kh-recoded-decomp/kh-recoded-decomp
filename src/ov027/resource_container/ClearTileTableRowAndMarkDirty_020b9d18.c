#include "nitro/types.h"

typedef struct TileTable {
    int *ids;
    int count;
    u8 pad_08[0x10];
    u8 dirtyMask;
} TileTable;
extern int func_ov027_020b9cd8(TileTable *table, int id);

void ClearTileTableRowAndMarkDirty_020b9d18(TileTable *table, int id)
{
    int index = func_ov027_020b9cd8(table, id);

    if (index < 0) {
        return;
    }
    table->dirtyMask |= 1 << index;
}
