#include "nitro/types.h"

typedef struct ParamEntry {
    u16 first;
    u16 second;
} ParamEntry;

typedef struct ParamTable {
    u32 header;
    ParamEntry entries[1];
} ParamTable;

typedef struct ObjectManager {
    u8 pad_000[0xc];
    u32 baseAddress;
    ParamTable *paramTable;
} ObjectManager;

extern ObjectManager *g_objectManager_020a04d8;

u32 ObjectManager_GetFirstEntryParam_0207ee14(int index)
{
    return 0x80000000 | (((g_objectManager_020a04d8->baseAddress + 0x8000) & 0xfffffc) << 7) |
           (g_objectManager_020a04d8->paramTable->entries[index].first & 0x1ff);
}
