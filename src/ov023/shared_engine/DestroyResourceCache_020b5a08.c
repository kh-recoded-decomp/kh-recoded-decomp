#include "nitro/types.h"

typedef struct {
    u32 handle;
    u8 pad_04[8];
    u8 fndList[0x34];
} ResourceCacheState;

extern ResourceCacheState *g_resourceCache_020b6f60;
extern void func_0202a638(u32 arg0);
extern void func_ov001_0207b200(u32 arg0);
extern void DestroyFndListIfNonEmpty_020b5974(ResourceCacheState *state);

void DestroyResourceCache_020b5a08(void)
{
    ResourceCacheState *state;

    state = g_resourceCache_020b6f60;
    func_ov001_0207b200(0);
    DestroyFndListIfNonEmpty_020b5974(state);
    func_0202a638(state->handle);
    g_resourceCache_020b6f60 = (ResourceCacheState *)0x0;
}
