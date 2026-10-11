#ifndef KH_RECODED_HANDLE_POOL_H
#define KH_RECODED_HANDLE_POOL_H

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
    u16 capacity;
    HandlePoolCallback callback;
} HandlePool;

void *GetHandlePoolElement(HandlePool *pool, int handle);

#endif
