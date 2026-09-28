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
extern void DestroyContainerElement_020b8fc0(ResourceContainer *container, void *element);

void DestroyAllContainerElements_020b900c(ResourceContainer *container) {
    void *element;
    void *next;

    element = NNS_FndGetNextListObject_02012a38(&container->elementList, NULL);
    while (element != NULL) {
        next = NNS_FndGetNextListObject_02012a38(&container->elementList, element);
        DestroyContainerElement_020b8fc0(container, element);
        element = next;
    }
}
