#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x5c];
    s8 group;
    u8 pad_5d[3];
} EntryDesc;

typedef void (*EntryCallback)(void);

typedef struct {
    u8 pad_00[8];
    void *slots;
    EntryDesc *descs;
    int descCount;
    u8 slotCount;
    u8 freeCount;
    u8 pad_16[2];
    EntryCallback spawn;
    EntryCallback dispatch;
    EntryCallback process;
    EntryCallback release;
    EntryCallback advance;
    EntryCallback move;
    EntryCallback animate;
} EntryPool;

extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern void func_01ff89a8(const void *src, void *dst, u32 size);
extern void SpawnUnitFromDesc_020aad8c(void);
extern void DispatchEntryKindHandlers_020aaea8(void);
extern void ProcessActiveEntries_020aaee0(void);
extern void ReleaseEntryGroup_020aaf10(void);
extern void AdvanceAnimationCounter_020ab468(void);
extern void UpdateEffectMovePhase_020ab4ac(void);
extern void UpdateEffectAnimationPhase_020ab564(void);

void InitEntryPool_020aa9c4(EntryPool *pool, EntryDesc *descs, int descCount, int slotCount)
{
    int i;

    pool->descCount = descCount;
    pool->descs = NNSi_FndAllocFromDefaultHeap_0202a178(descCount * sizeof(EntryDesc));
    for (i = 0; i < descCount; i++) {
        func_01ff89a8(&descs[i], &pool->descs[i], sizeof(EntryDesc));
        if (pool->descs[i].group == 0) {
            pool->descs[i].group = slotCount;
        }
    }
    pool->slots = NNSi_FndAllocFromDefaultHeap_0202a178(slotCount * 0x154);
    pool->slotCount = slotCount;
    pool->freeCount = slotCount;
    pool->spawn = SpawnUnitFromDesc_020aad8c;
    pool->dispatch = DispatchEntryKindHandlers_020aaea8;
    pool->process = ProcessActiveEntries_020aaee0;
    pool->release = ReleaseEntryGroup_020aaf10;
    pool->advance = AdvanceAnimationCounter_020ab468;
    pool->move = UpdateEffectMovePhase_020ab4ac;
    pool->animate = UpdateEffectAnimationPhase_020ab564;
}
