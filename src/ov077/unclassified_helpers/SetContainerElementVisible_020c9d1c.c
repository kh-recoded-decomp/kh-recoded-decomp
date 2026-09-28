#include "nitro/types.h"

extern void *func_ov027_020b90a4(void *container, int elementId);
extern void func_ov027_020b9580(void *container, void *element, BOOL visible);

void SetContainerElementVisible_020c9d1c(void *container, int elementId, BOOL visible)
{
    void *element = func_ov027_020b90a4(container, elementId);
    func_ov027_020b9580(container, element, visible);
}
