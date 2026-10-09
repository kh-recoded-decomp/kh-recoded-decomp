#include "nitro/types.h"

#pragma opt_dead_assignments off

typedef struct ListElement {
    u8 pad_00[0x24];
    u8 active : 1;
    u8 loaded : 1;
    u8 pad_25[0xB];
} ListElement;

typedef struct ElementList {
    u8 pad_00[0x10];
    ListElement *items;
    u8 pad_14[0x20];
    int count;
} ElementList;

extern void ReleaseListElementBuffer_020b808c(ElementList *list, ListElement *element);

void ReleaseLoadedElementBuffers_020b80bc(ElementList *list)
{
    int i;

    for (i = 0; i < list->count; i++) {
        if (list->items[i].loaded == 1) {
            ReleaseListElementBuffer_020b808c(list, &list->items[i]);
        }
    }
}
