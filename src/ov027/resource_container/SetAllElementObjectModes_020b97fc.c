#include "nitro/types.h"

typedef struct NNSFndList {
    void *headObject;
    void *tailObject;
    u16 numObjects;
    u16 offset;
} NNSFndList;

typedef struct ResourceContainer {
    u8 objManager[0x6434];
    NNSFndList elementList;
} ResourceContainer;

extern void *NNS_FndGetNextListObject_02012a38(NNSFndList *list, void *object);
extern void func_ov027_020b97b8(ResourceContainer *container, void *element, int mode);

void SetAllElementObjectModes_020b97fc(ResourceContainer *container, int mode) {
    void *element;

    element = NNS_FndGetNextListObject_02012a38(&container->elementList, NULL);
    while (element != NULL) {
        func_ov027_020b97b8(container, element, mode);
        element = NNS_FndGetNextListObject_02012a38(&container->elementList, element);
    }
}
