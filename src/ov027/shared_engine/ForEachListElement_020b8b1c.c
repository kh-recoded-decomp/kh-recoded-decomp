#include "nitro/types.h"

struct NNSFndList {
    void *head_object;
    void *tail_object;
    u16 num_objects;
    u16 offset;
};

extern void *NNS_FndGetNextListObject_02012a38(void *list, void *obj);
extern void func_ov027_020b8ac8(void *owner, void *element);

struct Owner {
    u8 pad_0000[0x6434];
    struct NNSFndList elementList;
};

void ForEachListElement_020b8b1c(struct Owner *owner) {
    void *element;

    for (element = NNS_FndGetNextListObject_02012a38(&owner->elementList, 0);
         element != 0;
         element = NNS_FndGetNextListObject_02012a38(&owner->elementList, element)) {
        func_ov027_020b8ac8(owner, element);
    }
}
