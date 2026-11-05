#include "nitro/types.h"

extern void DestroyFndObjectList(u32 context);

void ReleaseSceneTextWindow51C(u32 context)
{
    DestroyFndObjectList(context + 0x51c);
}
