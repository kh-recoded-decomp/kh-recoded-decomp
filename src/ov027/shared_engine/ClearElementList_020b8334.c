#include "nitro/types.h"

struct NNSFndList {
    void *head_object;
    void *tail_object;
    u16 num_objects;
    u16 offset;
};

extern void *NNS_FndGetNextListObject_02012a38(void *list, void *obj);
extern void RemoveIntrusiveListObject_020129d8(struct NNSFndList *list, void *object);

struct ListElement {
    u8 pad_00[0x20];
    u32 flags;
};

void ClearElementList_020b8334(struct NNSFndList *list) {
    struct ListElement *element;
    struct ListElement *next;

    element = (struct ListElement *)NNS_FndGetNextListObject_02012a38(list, 0);
    while (element != 0) {
        next = (struct ListElement *)NNS_FndGetNextListObject_02012a38(list, element);
        element->flags = (element->flags & 0xfffffffe) | 1;
        RemoveIntrusiveListObject_020129d8(list, element);
        element = next;
    }
    *(u32 *)((u8 *)list + 0x18) = 0;
}
