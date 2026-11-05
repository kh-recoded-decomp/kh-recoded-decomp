#include "nitro/types.h"

extern void Ov029SceneState_PushVramWhenIdle(void);
extern void MarkSoundCtxActive(void); /* MarkSoundCtxActive */
extern void Ov029SceneState_ResetSlotsAndLoadShadow(void);
extern void FinishOv029MenuLoad(void);
extern void EnableOv029Sound(void); /* EnableOv029Sound */
extern void HandleOverlayExitFlag(void); /* HandleOverlayExitFlag */
extern void DisableOv029Sound(void); /* DisableOv029Sound */
extern void Ov029_ClearSceneModeBits(void);

void (*gOv029SoundControlHandlers[8])(void) = {
    Ov029SceneState_PushVramWhenIdle,
    MarkSoundCtxActive, /* MarkSoundCtxActive */
    Ov029SceneState_ResetSlotsAndLoadShadow,
    FinishOv029MenuLoad,
    EnableOv029Sound, /* EnableOv029Sound */
    HandleOverlayExitFlag, /* HandleOverlayExitFlag */
    DisableOv029Sound, /* DisableOv029Sound */
    Ov029_ClearSceneModeBits,
};
