#include "nitro/types.h"

extern u32 gOv030SceneWork;
extern void BeginFieldScreenModeTransition(s32 arg);

u32 Ov030SceneState_BeginScreenModeTransition(void)
{
    u32 ctx;

    ctx = gOv030SceneWork;
    BeginFieldScreenModeTransition((s32)*(s8 *)(gOv030SceneWork + 8));
    *(u16 *)(ctx + 6) = *(u16 *)(ctx + 6) | 0x20;
    return 10;
}
