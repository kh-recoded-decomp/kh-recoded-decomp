#include "nitro/types.h"

extern void DestroyFndObjectList_020014f0(void *list);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *ptr);

void DestroyOwnedObjectList_02079cd4(void **listRef)
{
    if (listRef != NULL && *listRef != NULL) {
        DestroyFndObjectList_020014f0(*listRef);
        if (*listRef != NULL) {
            NNSi_FndFreeFromDefaultHeap_0202a1c4(*listRef);
            *listRef = NULL;
        }
    }
}
