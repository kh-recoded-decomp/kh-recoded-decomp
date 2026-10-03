#include "nitro/types.h"

typedef struct TileTable {
    int *ids;
    int count;
    u8 pad_08[0x10];
    u8 dirtyMask;
} TileTable;
extern int FindTileTableIndex_020b9920(TileTable *table, int id);

void MarkTileTableRowDirty_020b9e00(TileTable *table, int id)
{
    int index = FindTileTableIndex_020b9920(table, id);

    if (index < 0) {
        return;
    }
    table->dirtyMask |= 1 << index;
}
