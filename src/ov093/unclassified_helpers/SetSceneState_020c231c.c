#include "nitro/types.h"

typedef struct {
    u8 pad_0000[0xd1cc];
    int state;
    int stateTimer;
    int stateFrames;
} SceneWork;

extern void func_ov039_020bc03c(int value);

void SetSceneState_020c231c(int state, SceneWork *work)
{
    work->state = state;
    work->stateTimer = 0;
    work->stateFrames = 0;
    if (state == 6) {
        func_ov039_020bc03c(1);
    }
}
