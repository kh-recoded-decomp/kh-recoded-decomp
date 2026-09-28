#include "nitro/types.h"

extern void *func_ov027_020b90a4(void *container, int elementId);
extern void func_ov027_020b9580(void *container, void *element, BOOL visible);

void SetContainerElementVisible_020ccce8(void *container, int elementId, BOOL visible)
{
    func_ov027_020b9580(container, func_ov027_020b90a4(container, elementId), visible);
}
