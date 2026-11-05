#include "nitro/types.h"

typedef struct SceneActionState {
    u8 unknown00[6];
    u16 flags;
    s8 selectedEntry;
} SceneActionState;

extern SceneActionState *data_ov030_020bd020;
extern void SetFieldEntriesPaused(BOOL paused);
extern void PlaySoundChecked(int group, int soundId);
extern BOOL IsEntryFlag2Active(int entryId);
extern void QueueOrUpdateSoundKind3(int value);
extern u32 GetPendingWorldEntryData(void);
extern void UpdateCameraTriggers(void);

int ResolveMovieSceneAction(void)
{
    SceneActionState *state = data_ov030_020bd020;
    if (state->flags & 0x4000) {
        SetFieldEntriesPaused(TRUE);
        data_ov030_020bd020->flags |= 0x8000;
        return 14;
    }
    if (state->flags & 0x12)
        return -1;
    if (state->flags & 0x40) {
        PlaySoundChecked(0, 78);
        data_ov030_020bd020->flags |= 0x8000;
        return 13;
    }
    if (state->selectedEntry >= 0)
        return 9;
    if (IsEntryFlag2Active(0)) {
        data_ov030_020bd020->flags |= 0x10;
        QueueOrUpdateSoundKind3(32);
        return 11;
    }
    if (GetPendingWorldEntryData()) {
        SetFieldEntriesPaused(TRUE);
        return 8;
    }
    UpdateCameraTriggers();
    return -1;
}
