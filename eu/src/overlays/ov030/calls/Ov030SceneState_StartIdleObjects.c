#include "nitro/types.h"

extern u32 gOv030SceneWork;
extern void StartIdleSceneObjects(void);
extern void SetFieldObjectInteractionsBlocked(u32 arg);

u32 Ov030SceneState_StartIdleObjects(void)
{
    u32 ctx;

    ctx = gOv030SceneWork;
    *(u16 *)(gOv030SceneWork + 6) = *(u16 *)(gOv030SceneWork + 6) | 0x20;
    if ((*(u16 *)(ctx + 6) & 0x10) == 0) {
        StartIdleSceneObjects();
        SetFieldObjectInteractionsBlocked(1);
    }
    return 0xf;
}
