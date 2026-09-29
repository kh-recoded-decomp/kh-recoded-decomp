#include "nitro/types.h"

typedef struct ModeTriple {
    u16 first;
    u16 second;
    u16 third;
} ModeTriple;

typedef struct ResourceCache {
    u8 pad_000[0x1B8];
    int idCount;
    u16 *ids;
    int tripleCount;
    ModeTriple *triples;
} ResourceCache;

extern ResourceCache *g_resourceCache_020a04dc;
extern s8 GetCtxModeByte_02068084(void);
extern int AcquireRecordSlot_02051d3c(int slot, int param);
extern BOOL ReleaseRecordSlot_02051dfc(s32 slot);
extern int ModeTable_GetIdCount_0205213c(int mode);
extern int ModeTable_GetTripleCount_02052188(int mode);
extern u16 *ModeTable_GetId_0205215c(int mode, int index);
extern ModeTriple *ModeTable_GetTriple_020521ac(int mode, int index);
extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);

void ResourceCache_LoadModeTables_02087348(void)
{
    int idCount;
    int i;
    int mode;
    int tripleCount;
    int j;

    mode = GetCtxModeByte_02068084();

    AcquireRecordSlot_02051d3c(6, 1);
    idCount = ModeTable_GetIdCount_0205213c(mode);
    tripleCount = ModeTable_GetTripleCount_02052188(mode);
    if (idCount != 0) {
        g_resourceCache_020a04dc->ids = NNSi_FndAllocFromDefaultHeap_0202a178(idCount * 2);
    }
    g_resourceCache_020a04dc->idCount = idCount;
    if (tripleCount != 0) {
        g_resourceCache_020a04dc->triples = NNSi_FndAllocFromDefaultHeap_0202a178(tripleCount * 6);
    }
    g_resourceCache_020a04dc->tripleCount = tripleCount;
    for (i = 0; i < idCount; i++) {
        u16 *entry = &g_resourceCache_020a04dc->ids[i];
        *entry = *ModeTable_GetId_0205215c(mode, i);
    }
    for (j = 0; j < tripleCount; j++) {
        ModeTriple *entry = &g_resourceCache_020a04dc->triples[j];
        ModeTriple *source = ModeTable_GetTriple_020521ac(mode, j);
        entry->first = source->first;
        entry->second = source->second;
        entry->third = source->third;
    }
    ReleaseRecordSlot_02051dfc(6);
}
