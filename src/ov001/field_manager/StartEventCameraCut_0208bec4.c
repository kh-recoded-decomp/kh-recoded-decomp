#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u32 words[14];
} CameraCutHeader;

typedef struct {
    u8 pad_00[0x18];
    fx32 startY;
    u8 pad_1c[0x24 - 0x1c];
    fx32 endY;
    u8 pad_28[0x3c - 0x28];
    fx32 distance;
    fx32 speed;
    fx32 heightOffset;
} CameraCutPath;

typedef struct {
    u8 pad_00[0x44];
    VecFx32 baseRotation;
    u8 pad_50[0x90 - 0x50];
    s32 timer;
    s32 duration;
    s32 cutId;
    u8 pad_9c[0x19c - 0x9c];
    CameraCutHeader savedPath;
    u8 pad_1d4[0x1dc - 0x1d4];
    u16 active;
    u8 pad_1de[0x1e0 - 0x1de];
    s32 targetOverride;
} EventCameraManager;

extern EventCameraManager *data_ov001_020a04f4;
extern int func_02029f48(void);
extern int abs_0202198c(int value);
extern void func_ov021_020af664(EventCameraManager *manager, int target, CameraCutPath *path);
extern BOOL func_02028940(void);
extern void func_01ff89a8(const void *src, void *dst, u32 size);
extern void ActorChannel_ResetFields_0208ae3c(void);
extern fx32 FX_Div_01ff9c84(fx32 numer, fx32 denom);
extern int Math_AsinIdx_0202aaa8(fx32 ratio);
extern VecFx32 *func_ov001_0206dc4c(int index);
extern void func_ov001_0208babc(int actorId, int mode, fx32 speed, int roll, VecFx32 *position, VecFx32 *rotation);

void StartEventCameraCut_0208bec4(void) {
    EventCameraManager *manager = data_ov001_020a04f4;
    VecFx32 rotation;
    VecFx32 position;
    CameraCutPath path;
    fx32 ratio;
    int mode;

    if (manager->active == 0 || manager->cutId == -1) {
        return;
    }
    if (abs_0202198c(func_02029f48()) == 0x10) {
        return;
    }
    rotation = manager->baseRotation;
    if (manager->targetOverride != -1) {
        rotation.x = manager->targetOverride;
    }
    func_ov021_020af664(manager, rotation.x, &path);
    if (manager->cutId == 1 && !func_02028940()) {
        func_01ff89a8(&path, &manager->savedPath, sizeof(CameraCutHeader));
        ActorChannel_ResetFields_0208ae3c();
        manager->duration = 10;
        manager->timer = manager->duration;
        manager->cutId = 6;
        return;
    }
    ratio = FX_Div_01ff9c84(path.endY - path.startY, path.distance);
    if (ratio >= -0x1000 && ratio <= 0x1000) {
        rotation.y = -(u16)Math_AsinIdx_0202aaa8(ratio);
    }
    mode = 0;
    position = *func_ov001_0206dc4c(0);
    position.y += path.heightOffset;
    if (!func_02028940()) {
        mode = 10;
    }
    func_ov001_0208babc(-1, mode, path.speed, 0x1554, &position, &rotation);
    if (manager->cutId == 1) {
        ActorChannel_ResetFields_0208ae3c();
    }
    manager->cutId = 5;
}
