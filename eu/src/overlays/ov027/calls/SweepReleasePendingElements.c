#include "nitro/types.h"

typedef struct ListElement {
    u8 pad_00[0x24];
    u8 active : 1;
    u8 loaded : 1;
    u8 pad_25[0xb];
} ListElement;

typedef struct ElementList {
    u8 pad_00[0x10];
    ListElement *items;
    u8 pad_14[0x20];
    int count;
} ElementList;

extern void ReleaseListElementBuffer(int list, int element, int elementOffset);

void SweepReleasePendingElements(int listAddress)
{
    ElementList *list = (ElementList *)listAddress;
    int i;

    for (i = 0; i < list->count; i++) {
        if (list->items[i].loaded == 1) {
            ReleaseListElementBuffer(
                listAddress,
                (int)&list->items[i],
                i * sizeof(ListElement));
        }
    }
}
