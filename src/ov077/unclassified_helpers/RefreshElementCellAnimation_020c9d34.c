#include "nitro/types.h"

typedef struct ContainerElement {
    u8 pad_00[0x14];
    int spriteIndices[2];
} ContainerElement;

extern ContainerElement *func_ov027_020b90a4(void *container, int elementId);
extern void func_0204f204(void *recordArray, int recordIndex, int frames);

void RefreshElementCellAnimation_020c9d34(void *container, int elementId)
{
    ContainerElement *element = func_ov027_020b90a4(container, elementId);
    func_0204f204(container, element->spriteIndices[0], 0);
}
