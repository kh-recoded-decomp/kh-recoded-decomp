#include "nitro/types.h"

extern BOOL IsGlobalPackedBitSet_02027304(int bitIndex);
extern void SetContainerElementVisible_020c9d1c(void *container, int elementId, BOOL visible);

void SetFlagGatedElementsVisible_020c9d7c(void *container, BOOL visible)
{
    if (!IsGlobalPackedBitSet_02027304(0xf5b)) {
        visible = FALSE;
    }
    SetContainerElementVisible_020c9d1c(container, 3, visible);
    SetContainerElementVisible_020c9d1c(container, 5, visible);
    SetContainerElementVisible_020c9d1c(container, 4, visible);
}
