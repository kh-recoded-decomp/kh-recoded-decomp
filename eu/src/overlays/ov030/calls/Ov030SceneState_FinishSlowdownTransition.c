#include "nitro/types.h"

extern u32 gOv030SceneWork;
extern s32 IsScreenModeIdle(void);

u32 Ov030SceneState_FinishSlowdownTransition(void)
{
    s32 ready;

    ready = IsScreenModeIdle();
    if (ready != 0) {
        *(u16 *)(gOv030SceneWork + 6) = *(u16 *)(gOv030SceneWork + 6) & 0xffbf;
        *(u16 *)(gOv030SceneWork + 6) = *(u16 *)(gOv030SceneWork + 6) | 0x80;
        return 7;
    }
    return 0xffffffff;
}
