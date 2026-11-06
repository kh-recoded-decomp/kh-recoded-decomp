#include "nitro/types.h"

typedef struct {
    u8 pad_00[6];
    u16 flags;
    u8 pad_08[0x18];
    int state;
} SceneState;

extern SceneState *gOv028FieldSceneWorkStorage;
extern int (*const gSceneStateHandlers[])(void);

extern void UpdateOv028FieldScene(s32 mode);
extern void DrawOv028FieldScene(void);

int RunSceneStateMachine(void) {
    int next;

    do {
        gOv028FieldSceneWorkStorage->flags &= 0x7fff;
        next = gSceneStateHandlers[gOv028FieldSceneWorkStorage->state]();
        if (next >= 0) {
            gOv028FieldSceneWorkStorage->state = next;
        }
    } while (gOv028FieldSceneWorkStorage->flags & 0x8000);
    if (gOv028FieldSceneWorkStorage->flags & 8) {
        UpdateOv028FieldScene(0);
    }
    if (gOv028FieldSceneWorkStorage->flags & 4) {
        DrawOv028FieldScene();
    }
    return 0;
}
