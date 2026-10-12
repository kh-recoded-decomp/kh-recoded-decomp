#include "src/overlays/ov028/Ov028FieldState.h"
#include "src/overlays/ov001/FieldProgressState.h"

extern FieldProgressState *data_ov001_020a0480;
extern void SetFieldEntriesPaused(s32 paused);
extern void SetMenuHighlight(s32 highlight);
extern void PlaySoundChecked(s32 channel, s32 soundId);
extern BOOL IsEntryFlag2Active(s32 index);
extern void func_0204d808(s32 flags);
extern u32 func_ov001_0206e644(void);
extern s32 func_02029f5c(void);
extern void AwardSlotLevelProgress(s32 amount);
extern void AddRegionProgress(s32 amount);

/* Return a scene-handler index, or -1 to stay in the current state. */
s32 PollFieldTransition(void)
{
    if (gOv028FieldState->flags & 0x4000) {
        SetFieldEntriesPaused(1);
        SetMenuHighlight(1);
        gOv028FieldState->flags |= 0x8000;
        return 14;
    }
    if (gOv028FieldState->flags & 0x12) {
        return -1;
    }
    if (gOv028FieldState->flags & 0x40) {
        PlaySoundChecked(0, 0x4e);
        gOv028FieldState->flags |= 0x8000;
        return 13;
    }
    if (gOv028FieldState->mode >= 0) {
        return 9;
    }
    if (IsEntryFlag2Active(0)) {
        gOv028FieldState->flags |= 0x10;
        func_0204d808(0x20);
        return 11;
    }
    if (func_ov001_0206e644()) {
        data_ov001_020a0480->transitionFlags |= 0x10;
        SetFieldEntriesPaused(1);
        SetMenuHighlight(1);
        gOv028FieldState->flags |= 0x8000;
        return 8;
    }
    if (!func_02029f5c()) {
        if (data_ov001_020a0480->pendingExperience > 0) {
            AwardSlotLevelProgress(data_ov001_020a0480->pendingExperience);
            data_ov001_020a0480->pendingExperience = 0;
        }
        if (data_ov001_020a0480->pendingRegionProgress > 0) {
            AddRegionProgress((u8)data_ov001_020a0480->pendingRegionProgress);
            data_ov001_020a0480->pendingRegionProgress = 0;
        }
    }
    return -1;
}
