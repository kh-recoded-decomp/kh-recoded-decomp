#include "nitro/types.h"

extern void ReleaseChannelManagerResources(int obj);
extern void NNSi_FndFreeFromDefaultHeap(u32 obj);

extern u32 gFieldMessageSpriteManager;

void DestroyFieldMessageLoaderManager(void)
{
    if (gFieldMessageSpriteManager != 0) {
        ReleaseChannelManagerResources(gFieldMessageSpriteManager);
        NNSi_FndFreeFromDefaultHeap(gFieldMessageSpriteManager);
        gFieldMessageSpriteManager = 0;
    }
}
