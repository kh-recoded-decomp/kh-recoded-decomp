#include "nitro/types.h"

typedef struct TileTable {
    int *ids;
    int count;
    u8 pad_08[4];
    u16 rowLength;
    u8 pad_0E[2];
    u16 *rows;
} TileTable;

extern int func_ov027_020b9920(TileTable *table, int id);

u16 *GetTileTableRow_020b9948(TileTable *table, int id, int *indexOut)
{
    int index = func_ov027_020b9920(table, id);
    u16 *row;

    if (index < 0) {
        return NULL;
    }
    row = &table->rows[table->rowLength * index];
    if (indexOut != NULL) {
        *indexOut = index;
    }
    return row;
}

