#include "nitro/types.h"

typedef struct FieldManager {
    u8 pad_000[0x2d8];
    int chunkTable[3];
} FieldManager;

typedef struct FieldManagerHandle {
    u32 unk_00;
    FieldManager *manager;
} FieldManagerHandle;

extern FieldManagerHandle data_ov001_020a04a4;
extern void *func_ov027_020ba2a8(int *table, int index);

void *GetFieldChunkEntry_02072dd4(int index)
{
    return func_ov027_020ba2a8(data_ov001_020a04a4.manager->chunkTable, index);
}
