#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef void (*PoolCallback)(void);

typedef struct PanelEntryPool {
    PoolCallback callbacks[16];
    u8 pad_40[4];
    fx32 range;
    int active;
    VecFx32 extent;
    u8 mode;
    u8 pad_59;
    u8 kind;
} PanelEntryPool;

extern PanelEntryPool *CreateEntryPool_02086258(int headerSize, int entrySize, int count);
extern void func_ov020_020a2904(void);
extern void func_ov020_020a3150(void);
extern void ReleaseAndFreeResource_020a2abc(void);
extern void ActivatePanel_020a2ad8(void);
extern void TryGetFieldHandle_020a2e98(void);
extern void TryCollideWithCollider_020a2c98(void);
extern void func_ov020_020a2e58(void);
extern void ApplyTypeCapabilityFlag_020a3138(void);
extern void func_ov020_020a2830(void);
extern void func_ov020_020a2ebc(void);

PanelEntryPool *CreatePanelEntryPool_020a31f4(int count)
{
    PanelEntryPool *pool = CreateEntryPool_02086258(0x60, 0x70, count);

    pool->active = 0;
    pool->mode = 3;
    pool->extent.x = 0x1800;
    pool->extent.y = 0x1800;
    pool->extent.z = 0x1800;
    pool->range = 0x3000;
    pool->callbacks[0] = func_ov020_020a2904;
    pool->callbacks[1] = func_ov020_020a3150;
    pool->callbacks[2] = NULL;
    pool->callbacks[4] = ReleaseAndFreeResource_020a2abc;
    pool->callbacks[5] = NULL;
    pool->callbacks[6] = NULL;
    pool->callbacks[7] = ActivatePanel_020a2ad8;
    pool->callbacks[8] = TryGetFieldHandle_020a2e98;
    pool->callbacks[9] = TryCollideWithCollider_020a2c98;
    pool->callbacks[10] = func_ov020_020a2e58;
    pool->callbacks[3] = ApplyTypeCapabilityFlag_020a3138;
    pool->callbacks[12] = func_ov020_020a2830;
    pool->callbacks[14] = func_ov020_020a2ebc;
    pool->kind = 1;
    return pool;
}
