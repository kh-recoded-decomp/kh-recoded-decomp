#include "nitro/types.h"

extern u32 GetBoundedEntryField(u32 index);
extern void CameraPath_Start(u32 panel);
extern void ActivateSlotModelGroup(u32 entry, u32 index);

/* Resets an entry and refreshes its panel. */
u32 func_ov065_020d8120(int context, int params, u32 *outStatus)
{
    u32 entry;

    entry = GetBoundedEntryField(*(u32 *)(context + 0x14));
    *(u8 *)(entry + 0xa51) = 0;
    CameraPath_Start(*(u32 *)(params + 0x9c));
    ActivateSlotModelGroup(entry, 0);
    *outStatus = 0x18;
    return *(u32 *)(params + 0x3c);
}
