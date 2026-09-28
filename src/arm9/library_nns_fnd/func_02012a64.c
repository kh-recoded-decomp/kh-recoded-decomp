/* Walks a foundation list to the requested zero-based object index, returning null when the list ends first.
 * Uncertainty: This identifies a shared library operation; the particular scene, asset or gameplay caller using it is not established. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nns/fnd/calls/func_02010154.c.
 * Original routine: func_02010154. External references are
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
void * NNS_FndGetNextListObject(NNSFndList * list, void * object);
extern void * NNS_FndGetNextListObject (NNSFndList * list, void * object);

/* FND_GetListObjectByIndex_02012a64 -- NitroSystem list.c: NNS_FndGetNthListObject. */
void * FND_GetListObjectByIndex_02012a64 (NNSFndList * list, u16 index)
{
    int count = 0;
    NNSFndLink * object = NULL;


    while ((object = NNS_FndGetNextListObject(list, object)) != NULL)
    {
        if (index == count) {
            return object;
        }
        count++;
    }
    return NULL;
}
