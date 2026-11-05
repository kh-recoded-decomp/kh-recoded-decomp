#include "nitro/types.h"

extern void UpdateSceneGroupNodes(void);
extern void DrawModelSlots(u32 arg);

void UpdateSceneGroupsAndDrawModelSlots(u32 base)
{
    UpdateSceneGroupNodes();
    DrawModelSlots(base + 0x18c);
}
