#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct FadeState {
    fx32 baseAngle;
    u8 pad_04[0x10];
    s8 framesLeft;
    u8 snapshotSaved;
} FadeState;

typedef struct AreaContext {
    u8 pad_00[6];
    u16 flags;
    u8 pad_08[0x1a];
    u16 mainLayers;
    u16 subLayers;
    u8 pad_26[0x4a];
    FadeState fade;
    u8 snapshot[0x30];
} AreaContext;

typedef struct MenuMachine {
    u8 pad_000[0x13c];
    u16 flags;
    s8 delay;
} MenuMachine;

extern AreaContext *data_ov035_020bc4e0;
extern MenuMachine *data_ov040_020be280;
extern void func_ov001_0206e444(int paused);
extern void SetMenuHighlight(int value);
extern void func_ov001_0206cab4(int value);
extern void Camera_SaveSnapshot(void *snapshot);
extern void SetPanelEnabled(int value);
extern fx32 *func_ov046_020c1608(void);
extern u16 Math_AsinIdx(fx32 sine);
extern int func_ov001_020645c8(int id);
extern void FadeBgmVolume(int volume, int frames);

int StartAreaCameraIntro(void)
{
    AreaContext *context = data_ov035_020bc4e0;
    FadeState *fade;

    if (data_ov040_020be280->delay > 0) {
        data_ov040_020be280->delay--;
        if (data_ov040_020be280->delay <= 0) {
            func_ov001_0206e444(1);
            SetMenuHighlight(1);
            func_ov001_0206cab4(1);
        } else {
            return -1;
        }
    }
    context->subLayers = 0xa0;
    if (!(context->flags & 0x80)) {
        Camera_SaveSnapshot(data_ov035_020bc4e0->snapshot);
        data_ov035_020bc4e0->fade.snapshotSaved = 1;
    }
    SetPanelEnabled(0);
    func_ov046_020c1608();
    fade = &data_ov035_020bc4e0->fade;
    fade->framesLeft = 0xf;
    fade->baseAngle = (fx32)(((s64)Math_AsinIdx(*func_ov046_020c1608()) * 0x1680000 + 0x80000) >> 20);
    if (func_ov001_020645c8(0x3308) == 0) {
        FadeBgmVolume(0, 0x14);
    }
    data_ov040_020be280->flags |= 0x8000;
    return 7;
}
