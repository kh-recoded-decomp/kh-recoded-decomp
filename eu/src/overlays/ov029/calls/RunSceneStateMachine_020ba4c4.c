#include "nitro/types.h"

typedef struct {
    u8 pad_00[6];
    u16 flags;
    u8 pad_08[0xc];
    int state;
} SceneState;

extern SceneState *data_ov029_020babc0;
extern int (*const gOv029SoundControlHandlers[])(void);

extern void UpdateOv029FieldScene(int mode);
extern void DrawOv029FieldScene(void);

int RunSceneStateMachine_020ba4c4(void) {
    int next;

    do {
        data_ov029_020babc0->flags &= 0x7fff;
        next = gOv029SoundControlHandlers[data_ov029_020babc0->state]();
        if (next >= 0) {
            data_ov029_020babc0->state = next;
        }
    } while (data_ov029_020babc0->flags & 0x8000);
    if (data_ov029_020babc0->flags & 8) {
        UpdateOv029FieldScene(0);
    }
    if (data_ov029_020babc0->flags & 4) {
        DrawOv029FieldScene();
    }
    return 0;
}
