#include "nitro/types.h"

typedef struct NNSFndList {
    void *headObject;
    void *tailObject;
    u16 numObjects;
    u16 offset;
} NNSFndList;

extern void *NNS_FndGetNextListObject(NNSFndList *list, void *object);
extern void func_0202a1c4(void *ptr);

BOOL DestroyFndObjectList_020014f0(int container) {
    NNSFndList *list;
    void *object;
    void *next;

    list = (NNSFndList *)(container + 4);
    object = NNS_FndGetNextListObject(list, 0);
    while (object != 0) {
        next = NNS_FndGetNextListObject(list, object);
        func_0202a1c4(*(void **)((u32)object + 0x24));
        func_0202a1c4(object);
        object = next;
    }
    return 1;
}
