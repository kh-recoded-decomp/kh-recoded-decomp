#include "nitro/types.h"

extern u32 gOv030SceneWork;
extern s32 HasActiveFieldEffects(void);
extern s32 IsScreenModeIdle(void);
extern void BeginScreenFadeOut(s32 arg);

u32 Ov030SceneState_BeginFadeOutWhenIdle(void)
{
    u32 ctx;
    s32 ready;

    ctx = gOv030SceneWork;
    if (((*(u16 *)(gOv030SceneWork + 6) & 0x10) == 0) &&
        (ready = HasActiveFieldEffects(), ready != 0)) {
        return 0xffffffff;
    }
    ready = IsScreenModeIdle();
    if (ready == 0) {
        return 0xffffffff;
    }
    BeginScreenFadeOut((s32)*(s8 *)(ctx + 8));
    return 0x10;
}
