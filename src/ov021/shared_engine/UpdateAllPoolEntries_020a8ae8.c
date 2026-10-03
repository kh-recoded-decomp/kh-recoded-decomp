#include "nitro/types.h"

extern void *NNS_FndGetNextListObject_02012a38(void *list, void *obj);
extern void func_ov021_020a8240(void *entry, int a, int b);

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

void UpdateAllPoolEntries_020a8ae8(int a, int b)
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
            func_ov021_020a8240(pool->entries + i * 0x138, a, b);
        }
        pool = next;
    }
}
