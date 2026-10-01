#include "nitro/types.h"

typedef struct BufferItem {
    u8 data[0x30];
} BufferItem;

typedef struct BufferList {
    BufferItem *items;
    s8 count;
} BufferList;

extern int FreeBufferAndClearStatus_0206a918(BufferItem *item);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);

void FreeBufferList_0206c850(BufferList *list)
{
    int i;

    for (i = 0; i < list->count; i++) {
        FreeBufferAndClearStatus_0206a918(&list->items[i]);
    }
    NNSi_FndFreeFromDefaultHeap_0202a1c4(list->items);
}
