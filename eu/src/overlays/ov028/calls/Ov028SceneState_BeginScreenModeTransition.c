#include "nitro/types.h"

extern u32 gOv028FieldSceneWorkStorage;
extern void BeginFieldScreenModeTransition(s32 value);

u32 Ov028SceneState_BeginScreenModeTransition(void)
{
    u32 context = gOv028FieldSceneWorkStorage;

    BeginFieldScreenModeTransition((s32)*(s8 *)(gOv028FieldSceneWorkStorage + 8));
    *(u16 *)(context + 6) = *(u16 *)(context + 6) | 0x20;
    return 10;
}
