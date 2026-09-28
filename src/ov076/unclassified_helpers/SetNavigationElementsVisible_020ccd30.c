#include "nitro/types.h"

extern BOOL IsGlobalPackedBitSet_02027304(int bitIndex);
extern void SetContainerElementVisible_020ccce8(void *container, int elementId, BOOL visible);

void SetNavigationElementsVisible_020ccd30(void *container, BOOL visible)
{
    if (!IsGlobalPackedBitSet_02027304(0xf5b)) {
        visible = FALSE;
    }
    SetContainerElementVisible_020ccce8(container, 3, visible);
    SetContainerElementVisible_020ccce8(container, 5, visible);
    SetContainerElementVisible_020ccce8(container, 4, visible);
}
