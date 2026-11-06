#include "nitro/types.h"

extern u32 NNSi_FndAllocFromDefaultHeap(u32 size);
extern void InitMessageLoaders(void);

extern u32 gFieldMessageSpriteManager;

void EnsureFieldMessageLoaderManager(void)
{
    if (gFieldMessageSpriteManager == 0) {
        gFieldMessageSpriteManager = NNSi_FndAllocFromDefaultHeap(0xa4);
        InitMessageLoaders();
    }
}
