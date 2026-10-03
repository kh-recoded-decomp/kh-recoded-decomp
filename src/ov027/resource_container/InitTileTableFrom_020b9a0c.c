#include "nitro/types.h"

typedef struct TileTable {
    int *ids;
    int count;
    u16 width;
    u16 height;
    u16 rowLength;
    u8 pad_0E[2];
    u16 *rows;
    u8 pad_14[4];
    u8 dirtyMask;
    u8 pad_19[3];
} TileTable;

extern void func_01ff8830(void *dst, u8 value, u32 size);
extern void func_01ff89a8(const void *src, void *dst, u32 size);
extern void func_01ff8684(u32 value, void *dst, u32 size);
extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);

void InitTileTableFrom_020b9a0c(TileTable *table, const TileTable *source)
{
    int *ids;
    u16 *rows;
    int count;
    u16 width;
    u16 height;
    u32 size;

    func_01ff8830(table, 0, sizeof(TileTable));
    ids = NNSi_FndAllocFromDefaultHeap_0202a178(source->count * sizeof(int));
    table->ids = ids;
    func_01ff89a8(source->ids, ids, source->count * sizeof(int));
    count = source->count;
    table->count = count;
    width = source->width;
    table->width = width;
    height = source->height;
    table->height = height;
    table->rowLength = width * height;
    size = table->rowLength * 2 * count;
    rows = NNSi_FndAllocFromDefaultHeap_0202a178(size);
    table->rows = rows;
    func_01ff8684(0, rows, size);
    table->dirtyMask = 0xFF;
}
