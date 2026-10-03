#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct EffectGroupDesc {
    u32 baseId;
    u32 words[5];
} EffectGroupDesc;

typedef struct EffectParams {
    s32 field00;
    s32 field04;
    u16 field08;
    u8 pad_0a[2];
    s32 field0c;
    u8 pad_10[4];
    fx32 scaleX;
    s32 field18;
    s32 field1c;
    fx32 scaleY;
    fx32 scaleZ;
    s32 field28;
    u8 pad_2c[4];
    s32 field30;
    u8 pad_34[4];
    s32 field38;
    u8 pad_3c[4];
    VecFx32 position;
    s32 field4c;
    s32 field50;
    s32 field54;
    u8 pad_58[4];
    s8 count;
    u8 pad_5d[3];
} EffectParams;

typedef struct TrailSlot {
    s32 first;
    s32 second;
    VecFx32 position;
} TrailSlot;

typedef struct EffectGroup {
    u8 pad_00[0x15];
    u8 count;
    u8 pad_16[0x1c - 0x16];
    void *drawCallback;
    void *updateCallback;
    u8 pad_24[8];
    void *callback2c;
    void *callback30;
    u8 pad_34[8];
    void *entries;
    TrailSlot *slots;
    void *owner;
} EffectGroup;

extern const EffectGroupDesc data_ov059_020cfeb8;
extern const VecFx32 data_02053438;

extern void func_01ff86fc(u32 data, void *dest, u32 size);
extern void ResetMotionState_020ab04c(EffectParams *params);
extern void SetupOwnerAndEntries_020ab010(EffectGroup *group, u32 first, u32 second, EffectParams *params, int x, int y);
extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern void func_ov059_020cda14(void);
extern void func_ov059_020cdc5c(void);
extern void func_ov059_020cde6c(void);
extern void func_ov059_020cebd4(void);
extern void func_ov059_020cd780(EffectGroup *group, EffectGroupDesc *desc);

void EffectGroup_Init_020cedbc(u8 *owner, EffectGroup *group)
{
    EffectGroupDesc desc = data_ov059_020cfeb8;
    EffectParams params;
    VecFx32 zero;
    TrailSlot slot;
    u32 high;
    int i = 0;

    func_01ff86fc(0, group, 0x660);
    ResetMotionState_020ab04c(&params);
    params.field08 = 0;
    params.field0c = 0x8cd;
    zero = data_02053438;
    params.field00 = 0;
    params.field04 = 0;
    params.scaleX = FX32_ONE;
    params.field18 = 0;
    params.field1c = 0;
    params.scaleY = FX32_ONE;
    params.scaleZ = FX32_ONE;
    params.field28 = 0;
    params.field50 = 0;
    params.field54 = 0;
    params.field4c = 0;
    params.position = zero;
    params.count = 20;
    params.field30 = 0;
    params.field38 = 0;
    group->count = 20;
    high = (((*(s32 *)(owner + 0x1824) + 0x8000) & 0xfffffc) << 7) | 0x80000000;
    SetupOwnerAndEntries_020ab010(group, (desc.baseId & 0x1ff) | high, high | ((desc.baseId + 1) & 0x1ff), &params, 1, params.count);
    group->entries = NNSi_FndAllocFromDefaultHeap_0202a178(params.count * 0x48);
    group->slots = NNSi_FndAllocFromDefaultHeap_0202a178(200);
    group->updateCallback = func_ov059_020cda14;
    group->drawCallback = func_ov059_020cdc5c;
    group->callback2c = func_ov059_020cde6c;
    group->callback30 = func_ov059_020cebd4;
    group->owner = owner;
    slot.first = -1;
    slot.second = -1;
    slot.position = zero;
    do {
        group->slots[i] = slot;
        i++;
    } while (i < 10);
    func_ov059_020cd780(group, &desc);
}
