#include "nitro/types.h"

typedef struct PoolNode {
    u32 flags;
    struct PoolNode *prev;
    struct PoolNode *next;
} PoolNode;

typedef struct HandlePool {
    PoolNode *nodes;
    PoolNode *freeList;
    PoolNode *usedList;
} HandlePool;

extern int func_ov001_0208f240(HandlePool *pool, PoolNode *node);
extern void HandlePool_ReleaseHandle_0208f1a8(HandlePool *pool, int handle);

void HandlePool_ReleaseAll_0208f21c(HandlePool *pool)
{
    PoolNode *node;
    PoolNode *next;

    if (pool != NULL) {
        node = pool->usedList;
        while (node != NULL) {
            next = node->next;
            HandlePool_ReleaseHandle_0208f1a8(pool, func_ov001_0208f240(pool, node));
            node = next;
        }
    }
}
