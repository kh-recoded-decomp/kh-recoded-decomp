#include "nitro/types.h"

extern void DestroyFndObjectList(u32 context);

void ReleaseSceneTextWindow4D8(u32 context)
{
    DestroyFndObjectList(context + 0x4d8);
}
