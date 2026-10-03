#include "nitro/types.h"

typedef struct {
    u8 pad_00[6];
    u16 flags;
    u8 pad_08[0x18];
    int state;
} SceneState;

extern SceneState *data_ov030_020bd000;
extern int (*const data_ov030_020bcf98[])(void);

extern void ApplyOverlayScaleMode_020baab4(int mode);
extern void func_ov030_020baa98(void);

int RunSceneStateMachine_020ba4c0(void) {
    int next;

    do {
        data_ov030_020bd000->flags &= 0x7fff;
        next = data_ov030_020bcf98[data_ov030_020bd000->state]();
        if (next >= 0) {
            data_ov030_020bd000->state = next;
        }
    } while (data_ov030_020bd000->flags & 0x8000);
    if (data_ov030_020bd000->flags & 8) {
        ApplyOverlayScaleMode_020baab4(0);
    }
    if (data_ov030_020bd000->flags & 4) {
        func_ov030_020baa98();
    }
    return 0;
}
