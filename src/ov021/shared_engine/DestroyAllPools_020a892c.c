#include "nitro/types.h"

extern void *NNS_FndGetNextListObject_02012a38(void *list, void *obj);
extern void RemoveIntrusiveListObject_020129d8(void *list, void *obj);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);
extern void UnpackExtendedData_020a8234(void *entry);
extern void RemoveTaggedListEntries_0206c720(void *tag);
extern void func_ov021_020a8f74(void);

typedef struct Pool {
    u8 *entries;
    int count;
} Pool;

typedef struct PoolList {
    int active;
    struct { void *head; void *tail; u16 count; u16 offset; } list;
} PoolList;

extern int PoolListEnabled_020b5608;
extern PoolList PoolState_020b5608;

void DestroyAllPools_020a892c(void)
{
    PoolList *state = &PoolState_020b5608;
    int i;
    Pool *pool;
    Pool *next;

    if (PoolListEnabled_020b5608 == 0) {
        return;
    }
    pool = NNS_FndGetNextListObject_02012a38(&state->list, NULL);
    while (pool != NULL) {
        next = NNS_FndGetNextListObject_02012a38(&state->list, pool);
        for (i = 0; i < pool->count; i++) {
            UnpackExtendedData_020a8234(pool->entries + i * 0x138);
        }
        NNSi_FndFreeFromDefaultHeap_0202a1c4(pool->entries);
        RemoveIntrusiveListObject_020129d8(&state->list, pool);
        NNSi_FndFreeFromDefaultHeap_0202a1c4(pool);
        pool = next;
    }
    state->active = 0;
    RemoveTaggedListEntries_0206c720(func_ov021_020a8f74);
}
