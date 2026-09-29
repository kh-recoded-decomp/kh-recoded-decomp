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
    u8 *elements;
    u16 elementSize;
    u16 pad_12;
    void (*callback)(int event, void *element);
} HandlePool;

extern void *func_ov001_0208f258(HandlePool *pool, int handle);
extern u32 func_02023fc8(u32 dividend, u32 divisor);

u16 HandlePool_ClaimHandle_0208f128(HandlePool *pool, int handle)
{
    PoolNode *node;
    PoolNode *head;

    node = &pool->nodes[(u16)(handle - 1)];
    if (node->flags & 1) {
        return 0;
    }
    if (pool->freeList == node) {
        pool->freeList = pool->freeList->next;
    }
    if (node->prev != NULL) {
        node->prev->next = node->next;
    }
    if (node->next != NULL) {
        node->next->prev = node->prev;
    }
    node->prev = NULL;
    node->next = NULL;
    head = pool->usedList;
    pool->usedList = node;
    node->flags = 1;
    node->prev = NULL;
    node->next = head;
    if (head != NULL) {
        head->prev = node;
    }
    if (pool->callback != NULL) {
        pool->callback(0, func_ov001_0208f258(pool, handle));
    }
    return (u16)func_02023fc8((u8 *)node - (u8 *)pool->nodes, sizeof(PoolNode)) + 1;
}
