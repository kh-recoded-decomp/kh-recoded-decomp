#include "nitro/types.h"

typedef struct {
    u8 pad_00[6];
    u16 flags;
    u8 pad_08[0xc];
    int state;
} SceneState;

extern SceneState *gOv029SceneWorkStorage;
extern int (*const gOv029SoundControlHandlers[])(void);

extern void UpdateOv029FieldScene(int mode);
extern void DrawOv029FieldScene(void);

int RunSceneStateMachine_020ba4c4(void) {
    int next;

    do {
        gOv029SceneWorkStorage->flags &= 0x7fff;
        next = gOv029SoundControlHandlers[gOv029SceneWorkStorage->state]();
        if (next >= 0) {
            gOv029SceneWorkStorage->state = next;
        }
    } while (gOv029SceneWorkStorage->flags & 0x8000);
    if (gOv029SceneWorkStorage->flags & 8) {
        UpdateOv029FieldScene(0);
    }
    if (gOv029SceneWorkStorage->flags & 4) {
        DrawOv029FieldScene();
    }
    return 0;
}
