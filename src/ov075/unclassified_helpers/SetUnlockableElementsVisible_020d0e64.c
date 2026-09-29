#include "nitro/types.h"

typedef struct ResourceContainer ResourceContainer;

extern BOOL IsGlobalPackedBitSet_02027304(int bitIndex);
extern void SetLayoutElementVisible_020d0e4c(ResourceContainer *layout, s32 elementId, BOOL visible);

void SetUnlockableElementsVisible_020d0e64(ResourceContainer *layout, BOOL visible)
{
    if (!IsGlobalPackedBitSet_02027304(0xf5b)) {
        visible = FALSE;
    }
    SetLayoutElementVisible_020d0e4c(layout, 3, visible);
    SetLayoutElementVisible_020d0e4c(layout, 5, visible);
    SetLayoutElementVisible_020d0e4c(layout, 4, visible);
}
