#include "nitro/types.h"

typedef struct ListElement {
    u8 pad_00[0x24];
    u8 active : 1;
    u8 loaded : 1;
    u8 pad_25[7];
    void *buffer;
} ListElement;

extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);

void ReleaseListElementBuffer_020b808c(void *list, ListElement *element)
{
    element->loaded = 0;
    if (element->buffer != NULL) {
        NNSi_FndFreeFromDefaultHeap_0202a1c4(element->buffer);
        element->buffer = NULL;
    }
}
