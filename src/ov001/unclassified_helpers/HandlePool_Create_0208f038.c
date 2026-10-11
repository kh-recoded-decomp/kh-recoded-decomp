#include "nitro/types.h"

typedef struct PoolNode {
    u32 flags;
    struct PoolNode *prev;
    struct PoolNode *next;
} PoolNode;

typedef void (*HandlePoolCallback)(int event, void *element);

typedef struct HandlePool {
    PoolNode *nodes;
    PoolNode *freeList;
    PoolNode *usedList;
    u8 *elements;
    u16 elementSize;
    u16 count;
    HandlePoolCallback callback;
} HandlePool;

extern void *NNSi_FndAllocFromDefaultHeapEx_0202a19c(u32 size, int alignment);
extern void ClearBuffer_0208f02c(void *dst, u32 size);

HandlePool *HandlePool_Create_0208f038(u8 *elements, u16 elementSize, u32 count, HandlePoolCallback callback)
{
    u32 i;
    u32 last;
    int size;
    HandlePool *pool;
    PoolNode *node;

    size = count * sizeof(PoolNode);
    size += sizeof(HandlePool);
    pool = NNSi_FndAllocFromDefaultHeapEx_0202a19c(size, 4);
    ClearBuffer_0208f02c(pool, size);
    node = (PoolNode *)(pool + 1);
    pool->freeList = node;
    pool->nodes = node;
    pool->elements = elements;
    pool->elementSize = elementSize;
    pool->count = count;
    pool->callback = callback;
    i = 0;
    if (i < count) {
        last = count - 1;
        do {
            node->flags = 0;
            if (i == 0) {
                node->prev = NULL;
                if (i != last) {
                    node->next = node + 1;
                } else {
                    node->next = NULL;
                }
            } else if (i == last) {
                node->prev = node - 1;
                node->next = NULL;
            } else {
                node->prev = node - 1;
                node->next = node + 1;
            }
            i++;
            node++;
        } while (i < count);
    }
    return pool;
}
