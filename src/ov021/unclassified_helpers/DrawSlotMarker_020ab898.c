#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct {
    u8 pad_000[0x20];
    u8 renderObj[0x84];
    VecFx32 position;
    VecFx32 scale;
    u8 pad_0bc[0x74];
    s8 slot;
    s8 active;
    u8 pad_132[0xe];
    u16 angle;
} SlotMarker;

typedef struct {
    u8 pad_00[0x54];
    u32 flags;
} GeometryState;

extern const s16 data_0205356c[];
extern MtxFx33 data_0205a9b8;
extern GeometryState data_0205a9a4;

extern VecFx32 *func_ov001_0206dc60(int slot);
extern u16 GetBiasAdjustedField_0206dc80(int index);
extern void func_0201931c(const VecFx32 *scale);
extern void func_020192ec(const VecFx32 *trans);
extern void MTX_RotY33_01ff923c(MtxFx33 *mtx, fx32 sinVal, fx32 cosVal);
extern void MI_Copy36B_01ff87c4(const void *src, void *dst);
extern void FlushGeometryStateVariant_020191b8(void);
extern void func_01ffe1bc(void *renderObj);

void DrawSlotMarker_020ab898(SlotMarker *marker)
{
    MtxFx33 rotation;
    int angleIndex;

    if (marker->active == 0) {
        return;
    }
    marker->position = *func_ov001_0206dc60(marker->slot);
    marker->angle = GetBiasAdjustedField_0206dc80(marker->slot);
    func_0201931c(&marker->scale);
    angleIndex = marker->angle >> 4;
    MTX_RotY33_01ff923c(&rotation, -data_0205356c[angleIndex], -data_0205356c[(0x400 - angleIndex) & 0xfff]);
    MI_Copy36B_01ff87c4(&rotation, &data_0205a9b8);
    data_0205a9a4.flags &= ~0xa4;
    func_020192ec(&marker->position);
    FlushGeometryStateVariant_020191b8();
    func_01ffe1bc(marker->renderObj);
}
