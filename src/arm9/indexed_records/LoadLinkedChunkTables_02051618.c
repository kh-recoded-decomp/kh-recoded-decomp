#include "nitro/types.h"

typedef struct Chunk {
    u32 size;
    u16 id;
    u16 count;
    struct Chunk *items[1];
} Chunk;

typedef struct {
    u32 pad_00;
    u32 keyA;
    u32 keyB;
    u32 pad_0c;
} Record;

typedef struct {
    u32 baseA;
    u32 pad_04[9];
    Record *records;
    u32 *blob;
} State;

extern State *data_020613d0;
extern u32 func_0202c478(u32 fileId, u32 param2);
extern u32 func_0202c48c(u32 fileId, u32 param2);

void LoadLinkedChunkTables_02051618(int useAlt)
{
    Record *record;
    Chunk *chunk;
    int i;
    int k;
    int j;
    int countA;
    u32 offsetB;
    u32 offsetA;
    int countB;
    u32 key;
    u32 *blob;
    u8 *listB;
    u8 *listA;
    State *state = data_020613d0;
    int recordCount;

    if (useAlt != 0) {
        state->blob = (u32 *)func_0202c48c(((state->baseA + 0x8000) & 0xfffffc) << 7 | 0x80000002, 0x11);
    } else {
        state->blob = (u32 *)func_0202c478(((state->baseA + 0x8000) & 0xfffffc) << 7 | 0x80000002, 0x11);
    }
    blob = state->blob;
    offsetA = blob[1];
    offsetB = blob[2];
    recordCount = *(int *)((u8 *)blob + *blob);
    countA = *(int *)((u8 *)blob + offsetA);
    countB = *(int *)((u8 *)blob + offsetB);
    state->records = (Record *)((u8 *)blob + *blob + 4);
    listA = (u8 *)state->blob + offsetA;
    listB = (u8 *)state->blob + offsetB;
    for (i = 0; i < recordCount; i++) {
        record = &state->records[i];
        chunk = (Chunk *)(listA + 4);
        key = record->keyA;

        for (j = 0; j < countA; j++) {
            if (chunk->id == key) {
                record->keyA = (u32)chunk;
                break;
            }
            chunk = (Chunk *)((u8 *)chunk + chunk->size);
        }
        key = record->keyB;
        chunk = (Chunk *)(listB + 4);
        for (j = 0; j < countB; j++) {
            if (chunk->id == key) {
                Chunk *item;
                record->keyB = (u32)chunk;
                item = (Chunk *)&chunk->items[chunk->count];
                for (k = 0; k < chunk->count; k++) {
                    chunk->items[k] = item;
                    item = (Chunk *)((u8 *)item + item->size);
                }
                break;
            }
            chunk = (Chunk *)((u8 *)chunk + chunk->size);
        }
    }
}
