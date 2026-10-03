#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct GlowColors {
    u8 nearColor[3];
    u8 farColor[3];
} GlowColors;

typedef struct GlowOwner {
    u8 pad_00[0x64];
    s16 state;
} GlowOwner;

typedef struct GlowMaterial {
    u8 pad_00[0x4];
    u16 diffuse;
} GlowMaterial;

typedef struct GlowModel {
    u8 pad_00[0x10];
    GlowMaterial material;
} GlowModel;

typedef struct GlowObject {
    u8 pad_00[0x8];
    GlowOwner *owner;
    GlowModel *model;
    u8 pad_10[0x28];
    u8 lightId;
    u8 pad_39[0x7];
    VecFx32 position;
} GlowObject;

extern const u8 data_ov001_0209e330[3];
extern const GlowColors data_ov001_0209e333[];
extern u32 ReadSessionPackedBits_02064574(int bitOffset, u32 bitCount);
extern VecFx32 *func_ov001_0206dc4c(int index);
extern fx32 func_01ffa0f4(const VecFx32 *a, const VecFx32 *b);
extern fx32 FX_Div_01ff9c84(fx32 numer, fx32 denom);
extern fx32 func_02006450(fx32 left, fx32 right);
extern void func_0202f590(u16 *color, int flag);
extern void func_0202f5b4(u16 *color, u16 value);
extern void func_020367d0(int lightId, s16 alpha);

int UpdateProximityGlow_02081bc0(GlowObject *object)
{
    GlowMaterial *material;
    int level;
    fx32 distance;
    fx32 ratio;
    fx32 alpha;
    const u8 *from;
    const u8 *to;
    int color[3];
    int i;

    if (object->owner->state >= 0) {
        material = &object->model->material;
        level = ReadSessionPackedBits_02064574(0x1a0f, 3) - 1;
        if (level < 0) {
            level = 0;
        }
        ratio = 0;
        distance = func_01ffa0f4(func_ov001_0206dc4c(0), &object->position);
        if (distance <= 0x5000) {
            from = data_ov001_0209e333[level].nearColor;
            to = data_ov001_0209e330;
            ratio = FX_Div_01ff9c84(0x5000 - distance, 0x5000);
            alpha = func_02006450(0xb33, ratio) + 0x4cd;
        } else if (distance <= 0x1c000) {
            to = data_ov001_0209e333[level].nearColor;
            from = data_ov001_0209e333[level].farColor;
            ratio = FX_Div_01ff9c84(0x1c000 - distance, 0x1c000);
            alpha = func_02006450(0x4cd, ratio);
        } else {
            to = data_ov001_0209e333[level].nearColor;
            from = data_ov001_0209e333[level].farColor;
            alpha = ratio;
        }
        for (i = 0; i < 3; i++) {
            color[i] = from[i] + (((to[i] - from[i]) * ratio) >> 12);
        }
        func_0202f590(&material->diffuse, 1);
        func_0202f5b4(&material->diffuse, (u16)(color[0] | (color[1] << 5) | (color[2] << 10)));
        func_020367d0(object->lightId, (s16)(alpha + FX32_ONE));
    }
    return 0;
}
