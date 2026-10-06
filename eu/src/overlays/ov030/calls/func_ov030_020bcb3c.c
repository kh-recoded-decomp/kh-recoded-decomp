#include "nitro/types.h"

extern void UpdateSceneGroupNodes(void);
extern void DrawModelSlots(u32 arg);

void func_ov030_020bcb3c(u32 base)
{
    UpdateSceneGroupNodes();
    DrawModelSlots(base + 0x18c);
}
