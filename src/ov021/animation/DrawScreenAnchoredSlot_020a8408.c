#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct {
    s8 inUse;
    s8 actorId;
    s8 anchorMode;
    u8 pad_03;
    u16 flags;
    u8 pad_06[0x22];
    u8 model[0x90];
    fx32 baseScaleX;
    u32 pad_bc;
    fx32 baseScaleY;
    u8 pad_c4[0x64];
    fx32 screenX;
    fx32 screenY;
    fx32 scaleX;
    fx32 scaleY;
} EntrySlot;

typedef struct {
    u8 pad_00[0x54];
    u32 flags;
} RenderState;

extern RenderState data_0205a9a4;
extern u8 data_0205a9b8[];
extern fx32 FixedPointMultiply12(fx32 a, fx32 b);
extern void func_0201931c(VecFx32 *scale);
extern void func_020192ec(VecFx32 *translation);
extern void func_01ff90ec(MtxFx33 *mtx);
extern void func_01ff87c4(const MtxFx33 *src, void *dst);
extern void func_02019188(void);
extern void func_01ffe1bc(void *model);

void DrawScreenAnchoredSlot_020a8408(EntrySlot *slot)
{
    VecFx32 translation;
    VecFx32 scale;
    MtxFx33 rotation;

    if (slot->inUse == 0 || slot->anchorMode != 3) {
        return;
    }
    if (slot->flags & 2) {
        slot->flags &= 0xfffd;
        return;
    }
    if (slot->anchorMode != 3) {
        return;
    }
    translation.x = slot->screenX;
    translation.y = 0xc0000 - slot->screenY;
    translation.z = 0x400000;
    scale.x = FixedPointMultiply12(slot->scaleX, slot->baseScaleX);
    scale.y = FixedPointMultiply12(slot->scaleY, slot->baseScaleY);
    scale.z = FX32_ONE;
    func_0201931c(&scale);
    func_020192ec(&translation);
    data_0205a9a4.flags &= ~0xa4;
    func_01ff90ec(&rotation);
    func_01ff87c4(&rotation, data_0205a9b8);
    data_0205a9a4.flags &= ~0xa4;
    func_02019188();
    func_01ffe1bc(slot->model);
}
