#include "nitro/types.h"

typedef struct TileTable {
    int *ids;
    int count;
    u16 width;
    u16 height;
    u16 rowLength;
    u8 pad_0E[2];
    u16 *rows;
    int loadImmediately;
    u8 dirtyMask;
    u8 pad_19[3];
} TileTable;

typedef int (*TileLoadFunc)(int id, int offset, void *src, int size);

extern int LoadBgScreenData_020b989c(int id, int offset, void *src, int size);
extern int GFXi_EnqueueCommand_02014090(int id, int offset, void *src, int size);

void FlushDirtyTileTableRows_020b9e60(TileTable *table)
{
    int i;
    int size = table->width * table->height * 2;
    TileLoadFunc load = LoadBgScreenData_020b989c;

    if (table->loadImmediately == 0) {
        load = GFXi_EnqueueCommand_02014090;
    }
    for (i = 0; i < table->count; i++) {
        if (table->dirtyMask & (1 << i)) {
            load(table->ids[i], 0, &table->rows[table->rowLength * i], size);
        }
    }
    table->dirtyMask = 0;
}

