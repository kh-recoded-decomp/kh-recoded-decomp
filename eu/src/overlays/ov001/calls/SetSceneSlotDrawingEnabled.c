#include "nitro/types.h"

extern u32 gFieldSceneEntryContext;

void SetSceneSlotDrawingEnabled(s32 index, s32 enable)
{
    u8 *entry;

    entry = (u8 *)(gFieldSceneEntryContext + 0x18 + index * 0x108);
    if (enable != 0) {
        entry[0x104] = entry[0x104] | 1;
        return;
    }
    entry[0x104] = entry[0x104] & 0xfe;
}
