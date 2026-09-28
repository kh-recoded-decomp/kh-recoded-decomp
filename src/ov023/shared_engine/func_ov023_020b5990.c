#include "nitro/types.h"

typedef struct {
    u32 handle;
    u8 pad_04[8];
    u8 fndList[0x34];
} ResourceCacheState;

extern ResourceCacheState *g_resourceCache_020b6f60;
extern u32 g_resourceCacheInitData_020b6f0c;
extern void *NNSi_FndGetCurrentRootHeap_0202a764(void);
extern void func_01ff8830(void *dst, u32 val, u32 size);
extern void func_ov023_020b589c(void);
extern u32 func_0202a47c(void *arg0, u32 arg1);
extern u32 func_ov001_02071214(u32 arg0);
extern void func_ov027_020ba114(u32 arg0, u32 arg1, u32 arg2, u32 arg3);
extern u32 func_ov001_0207b200(u32 arg0);

u32 func_ov023_020b5990(void)
{
    ResourceCacheState *state;
    u32 value;

    func_ov001_0207b200(0x20b589d);
    state = (ResourceCacheState *)NNSi_FndGetCurrentRootHeap_0202a764();
    g_resourceCache_020b6f60 = state;
    func_01ff8830(state, 0, 0x40);
    func_ov023_020b589c();
    value = func_0202a47c(&g_resourceCacheInitData_020b6f0c, 0);
    state->handle = value;
    value = func_ov001_02071214(9);
    func_ov027_020ba114(value, 1, 0x20b5801, 0);
    return 0x20b59e1;
}
