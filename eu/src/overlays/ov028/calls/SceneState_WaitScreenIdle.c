#include "nitro/types.h"

typedef struct {
    u8 pad_00[6];
    u16 flags;
    s8 mode;
} SceneState;

typedef struct {
    u8 pad_000[0x214];
    u32 flags;
} FieldGlobal;

extern SceneState *gOv028FieldSceneWorkStorage;
extern FieldGlobal *data_ov001_020a0480;

extern BOOL IsScreenModeIdle(void);
extern void Panel_CaptureBrightness(void);

int SceneState_WaitScreenIdle(void) {
    SceneState *scene = gOv028FieldSceneWorkStorage;

    if (!IsScreenModeIdle()) {
        return -1;
    }
    scene->flags &= ~0x20;
    if (!(scene->flags & 0x4000)) {
        if (scene->mode != 3) {
            data_ov001_020a0480->flags &= ~0x40000;
            Panel_CaptureBrightness();
        }
        scene->mode = -1;
    }
    return 7;
}
