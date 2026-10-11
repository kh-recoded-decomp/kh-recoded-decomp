#pragma opt_propagation off
#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct IrisSprite {
    u8 pad_00[4];
    s16 width;
    s16 height;
    u8 pad_08[8];
    fx32 centerX;
    fx32 centerY;
    fx32 scaleX;
    fx32 scaleY;
} IrisSprite;

typedef struct IrisContext {
    u32 flags;
    fx32 timer;
    u8 pad_08[0x28];
    IrisSprite sprite;
    u8 pad_50[0x14];
    u8 slot;
    u8 settleFrames;
} IrisContext;

typedef struct G3dGlobalState {
    u8 pad_00[0xd4];
    u32 flag;
} G3dGlobalState;

extern IrisContext *data_ov001_020a0480;
extern const VecFx32 data_ov001_0209da80;
extern u8 data_0205a92c[];
extern G3dGlobalState data_0205a924;

extern void func_ov001_0206aa7c(void);
extern void AlarmCallback_0206ad1c(void *arg);
extern void MTX_OrthoW_02005f10(fx32 t, fx32 b, fx32 l, fx32 r, fx32 n, fx32 f, fx32 scaleW, void *mtx);
extern void func_0201931c(const VecFx32 *scale);
extern void func_020192ec(const VecFx32 *trans);
extern void FlushGeometryState_02019230(void);
extern void DrawFlatRect_0206a424(int x0, int y0, int x1, int y1, int z);

void UpdateIrisFrame_0206a4e4(void)
{
    IrisSprite *sprite;
    VecFx32 scale;
    int halfX;
    int halfY;
    int left;
    int right;
    int top;
    int bottom;

    data_ov001_020a0480->sprite.scaleX = data_ov001_020a0480->timer << 1;
    data_ov001_020a0480->sprite.scaleY = data_ov001_020a0480->timer * 3;
    func_ov001_0206aa7c();
    AlarmCallback_0206ad1c(&data_ov001_020a0480->sprite);

    scale = data_ov001_0209da80;
    {
        VecFx32 trans = {0, 0, 0};

        sprite = &data_ov001_020a0480->sprite;
        MTX_OrthoW_02005f10(0, 0x3000, 0, 0x4000, 0, 0x1000, 0x400000, data_0205a92c);
        data_0205a924.flag &= ~0x50;

        halfX = sprite->width * sprite->scaleX / 2;
        halfY = sprite->height * sprite->scaleY / 2;
        left = (sprite->centerX - halfX) >> 12;
        right = (sprite->centerX + halfX) >> 12;
        top = (sprite->centerY - halfY) >> 12;
        bottom = (sprite->centerY + halfY) >> 12;

        func_0201931c(&scale);
        func_020192ec(&trans);
        FlushGeometryState_02019230();

        if ((data_ov001_020a0480->flags & 1) && data_ov001_020a0480->slot == 0) {
            data_ov001_020a0480->settleFrames++;
            if (data_ov001_020a0480->settleFrames >= 2) {
                data_ov001_020a0480->flags |= 0x80;
            }
        }

        if (top > 0) {
            DrawFlatRect_0206a424(0, 0, 0x100, top, 0);
        }
        if (bottom < 0xc0) {
            DrawFlatRect_0206a424(0, bottom, 0x100, 0xc0, 0);
        }
        if (left > 0) {
            DrawFlatRect_0206a424(0, 0, left, 0xc0, 0);
        }
        if (right < 0x100) {
            DrawFlatRect_0206a424(right, 0, 0x100, 0xc0, 0);
        }
    }
}
