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

extern SceneState *data_ov030_020bd000;
extern FieldGlobal *data_ov001_020a0460;

extern BOOL IsScreenModeIdle_0206a814(void);
extern void Panel_CaptureBrightness_0207b704(void);

int SceneState_WaitScreenIdle_020ba874(void) {
    SceneState *scene = data_ov030_020bd000;

    if (!IsScreenModeIdle_0206a814()) {
        return -1;
    }
    if (!(scene->flags & 0x4000)) {
        if (scene->mode != 3) {
            data_ov001_020a0460->flags &= ~0x40000;
            Panel_CaptureBrightness_0207b704();
        }
        scene->mode = -1;
    }
    scene->flags &= ~0x20;
    return 7;
}
