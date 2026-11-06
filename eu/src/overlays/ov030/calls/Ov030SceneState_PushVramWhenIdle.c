#include "nitro/types.h"

extern u32 gOv030SceneWork;
extern s32 GetSessionScriptRunMask(void);
extern void PushVramState(void);

u32 Ov030SceneState_PushVramWhenIdle(void)
{
    s32 ready;

    ready = GetSessionScriptRunMask();
    if (ready != 0) {
        return 0xffffffff;
    }
    PushVramState();
    *(u16 *)(gOv030SceneWork + 6) = *(u16 *)(gOv030SceneWork + 6) | 0x8000;
    return 1;
}
