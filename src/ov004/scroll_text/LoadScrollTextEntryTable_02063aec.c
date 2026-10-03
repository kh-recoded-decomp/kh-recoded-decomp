#include "nitro/types.h"

typedef struct {
    u8 typeId;
    u8 flags;
    u16 length;
} PackedEntry;

typedef struct {
    u32 count;
    PackedEntry entries[1];
} PackedFile;

typedef struct {
    u8 typeId;
    u8 flags;
    u16 pad_02;
    const u16 *data;
} EntryTableItem;

typedef struct {
    u32 count;
    EntryTableItem entries[1];
} EntryTable;

typedef struct {
    u8 pad_00[0x3033c];
    EntryTable *table;
    PackedFile *file;
} ScrollTextWork;

typedef struct {
    u32 frameCount;
    ScrollTextWork *work;
} ScrollTextGlobals;

extern ScrollTextGlobals g_scrollText_020645a0;
extern u32 data_ov004_02064580[];

extern void *func_0202c478(u32 fileId, u32 heapId);
extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);

void LoadScrollTextEntryTable_02063aec(void)
{
    PackedFile *file = func_0202c478((u32)data_ov004_02064580, 0xe);
    EntryTable *table = NNSi_FndAllocFromDefaultHeap_0202a178(file->count * 8 + 4);
    const u16 *cursor;
    u32 i;

    table->count = file->count;
    i = 0;
    cursor = (const u16 *)&file->entries[file->count];
    while (i < file->count) {
        table->entries[i].typeId = file->entries[i].typeId;
        table->entries[i].flags = file->entries[i].flags;
        table->entries[i].data = file->entries[i].length == 0 ? 0 : cursor;
        cursor += file->entries[i].length;
        i++;
    }
    g_scrollText_020645a0.work->file = file;
    g_scrollText_020645a0.work->table = table;
}
