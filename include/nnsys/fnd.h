/* NitroSystem foundation: lists, heaps, allocators, as the library sources declare them (the NitroSDK / NitroSystem names). */
#ifndef NNSYS_FND_H
#define NNSYS_FND_H

#include "nitro/types.h"

struct NNSFndAllocator;
struct NNSFndAllocatorFunc;
struct NNSFndLink;
struct NNSFndList;
struct NNSiFndExpHeapHead;
struct NNSiFndExpHeapMBlockHead;
struct NNSiFndExpMBlockList;
struct NNSiFndFrmHeapHead;
struct NNSiFndFrmHeapState;
struct NNSiFndHeapHead;
struct NNSiFndUntHeapHead;
struct NNSiFndUntHeapMBlockHead;
struct NNSiFndUntMBlockList;

struct NNSFndLink {
    void *prev_object;
    void *next_object;
};

struct NNSFndList {
    void *head_object;
    void *tail_object;
    u16 num_objects;
    u16 offset;
};

struct NNSiFndExpHeapMBlockHead {
    u16 signature;
    u16 attribute;
    u32 block_size;
    struct NNSiFndExpHeapMBlockHead *prev_block;
    struct NNSiFndExpHeapMBlockHead *next_block;
};

struct NNSiFndExpMBlockList {
    struct NNSiFndExpHeapMBlockHead *head;
    struct NNSiFndExpHeapMBlockHead *tail;
};

struct NNSiFndExpHeapHead {
    struct NNSiFndExpMBlockList free_list;
    struct NNSiFndExpMBlockList used_list;
    u16 group_id;
    u16 feature;
};

typedef struct {
    void * prevObject;
    void * nextObject;
} NNSFndLink;

typedef struct {
    void * headObject;
    void * tailObject;
    u16 numObjects;
    u16 offset;
} NNSFndList;

typedef struct NNSiFndHeapHead NNSiFndHeapHead;

struct NNSiFndHeapHead {
    u32 signature;
    NNSFndLink link;
    NNSFndList childList;
    void * heapStart;
    void * heapEnd;
    u32 attribute;
};

typedef NNSiFndHeapHead * NNSFndHeapHandle;

typedef struct NNSiFndFrmHeapState NNSiFndFrmHeapState;

struct NNSiFndFrmHeapState {
    u32 tagName;
    void * headAllocator;
    void * tailAllocator;
    NNSiFndFrmHeapState * pPrevState;
};

typedef struct NNSiFndFrmHeapHead NNSiFndFrmHeapHead;

struct NNSiFndFrmHeapHead {
    void * headAllocator;
    void * tailAllocator;
    NNSiFndFrmHeapState * pState;
};

typedef struct NNSiFndUntHeapMBlockHead NNSiFndUntHeapMBlockHead;

struct NNSiFndUntHeapMBlockHead {
    NNSiFndUntHeapMBlockHead * pMBlkHdNext;
};

typedef struct NNSiFndUntMBlockList NNSiFndUntMBlockList;

struct NNSiFndUntMBlockList {
    NNSiFndUntHeapMBlockHead * head;
};

typedef void (*NNSFndHeapVisitor)(void * memBlock, NNSFndHeapHandle heap, u32 userParam);

typedef struct NNSFndAllocator NNSFndAllocator;

typedef void * (*NNSFndFuncAllocatorAlloc)(NNSFndAllocator * pAllocator, u32 size);

typedef void (*NNSFndFuncAllocatorFree)(NNSFndAllocator * pAllocator, void * memBlock);

typedef struct NNSFndAllocatorFunc NNSFndAllocatorFunc;

struct NNSFndAllocatorFunc {
    NNSFndFuncAllocatorAlloc pfAlloc;
    NNSFndFuncAllocatorFree pfFree;
};

struct NNSFndAllocator {
    NNSFndAllocatorFunc const * pFunc;
    void * pHeap;
    u32 heapParam1;
    u32 heapParam2;
};

typedef struct NNSiFndUntHeapHead NNSiFndUntHeapHead;

#define NNS_FndGetMemBlockSizeForUnitHeap(heap) (((const NNSiFndUntHeapHead *)((const u8 *)((const void *)(heap)) + sizeof(NNSiFndHeapHead)))->mBlkSize)

struct NNSiFndUntHeapHead {
    NNSiFndUntMBlockList mbFreeList;
    u32 mBlkSize;
};

typedef struct NNSiFndExpHeapMBlockHead NNSiFndExpHeapMBlockHead;

typedef struct NNSiFndExpMBlockList NNSiFndExpMBlockList;

typedef struct NNSiFndExpHeapHead NNSiFndExpHeapHead;

#define NNS_FND_FRMHEAP_FREE_HEAD (1 << 0)

#define NNS_FND_FRMHEAP_FREE_TAIL (1 << 1)

#define NNS_FND_INIT_LIST(list, structName, linkName) NNS_FndInitList(list, offsetof(structName, linkName))

#define NNS_FND_HEAP_INVALID_HANDLE NULL

#define NNS_FND_FRMHEAP_FREE_ALL (NNS_FND_FRMHEAP_FREE_HEAD | NNS_FND_FRMHEAP_FREE_TAIL)

#define NNS_FND_HEAP_DEFAULT_ALIGNMENT 4

#define NNS_FndAllocFromFrmHeap(heap, size) NNS_FndAllocFromFrmHeapEx(heap, size, NNS_FND_HEAP_DEFAULT_ALIGNMENT)

#endif
