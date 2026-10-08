#include "nitro/types.h"

typedef struct {
    u32 handle;
    u8 pad_04[8];
    u8 fndList[0x34];
} ResourceCacheState;

extern ResourceCacheState *data_ov023_020b6f80;
extern u32 data_ov023_020b6f2c;
extern void *NNSi_FndGetCurrentRootHeap(void);
extern void MI_CpuFill8(void *dst, u32 val, u32 size);
extern void SetupMenuSubBgLayers(void);
extern u32 Obj_CreateWithTailWork(void *arg0, u32 arg1);
extern u32 MakePrimaryVramKey_02071214(u32 arg0);
extern void QueueFileLoadRequest(u32 arg0, u32 arg1, u32 arg2, u32 arg3);
extern u32 func_ov001_0207b228(u32 callback);
extern void LoadMenuBackground(void);
extern void EnterMenuScreenState(void);

u32 InitMenuResourceCache(void)
{
    ResourceCacheState *state;
    u32 value;

    func_ov001_0207b228((u32)SetupMenuSubBgLayers);
    state = (ResourceCacheState *)NNSi_FndGetCurrentRootHeap();
    data_ov023_020b6f80 = state;
    MI_CpuFill8(state, 0, 0x40);
    SetupMenuSubBgLayers();
    value = Obj_CreateWithTailWork(&data_ov023_020b6f2c, 0);
    state->handle = value;
    value = MakePrimaryVramKey_02071214(9);
    QueueFileLoadRequest(value, 1, (u32)LoadMenuBackground, 0);
    return (u32)EnterMenuScreenState;
}
