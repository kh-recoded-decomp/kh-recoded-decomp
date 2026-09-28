/* Checks frame-heap state and advances to a new sound-heap section or rolls back when section allocation cannot proceed.
 * Uncertainty: The underlying allocator policy is not inferred. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nns/snd/calls/func_0201ba08.c.
 * Original routine: func_0201ba08. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef short s16;
typedef int s32;
typedef unsigned long long u64;
typedef long long s64;
typedef int BOOL;
typedef int OSIntrMode;
typedef void *OSMessage;
typedef volatile unsigned short vu16;
typedef volatile unsigned int vu32;
typedef volatile unsigned char vu8;

#define NULL ((void *)0)
#define TRUE 1
#define FALSE 0
#define HW_MAIN_MEM 0x02000000

#define offsetof(type, member) ((u32)&(((type *)0)->member))



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
typedef void (*NNSFndHeapVisitor)(void * memBlock, NNSFndHeapHandle heap, u32 userParam);
BOOL func_02013568(NNSFndHeapHandle heap, u32 tagName);
BOOL func_020135b8(NNSFndHeapHandle heap, u32 tagName);
typedef int (*MIDeviceReadFunction)(void * userdata, void * buffer, u32 offset, u32 length);
typedef int (*MIDeviceWriteFunction)(void * userdata, const void * buffer, u32 offset, u32 length);
struct NNSSndHeap;
typedef struct NNSSndHeap * NNSSndHeapHandle;
typedef struct NNSSndHeap {
    NNSFndHeapHandle handle;
    NNSFndList sectionList;
} NNSSndHeap;
extern BOOL func_0201f2bc(NNSSndHeap * heap);
extern BOOL func_0201f2bc (NNSSndHeap * heap);

/* func_0201f154 -- NitroSystem heap.c: NNS_SndHeapSaveState. */
int func_0201f154 (NNSSndHeapHandle heap)
{
    BOOL result;


    if (!func_02013568(heap->handle, heap->sectionList.numObjects)) {
        return -1;
    }

    if (!func_0201f2bc(heap)) {
        result = func_020135b8(heap->handle, 0);
        return -1;
    }

    return heap->sectionList.numObjects - 1;
}
