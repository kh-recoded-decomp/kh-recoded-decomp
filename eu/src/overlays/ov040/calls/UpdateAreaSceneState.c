#include "nitro/types.h"

typedef struct {
    u8 pad_00[6];
    u16 flags;
    u8 pad_08[0x14];
    s8 pendingChoice;
    u8 sceneReady;
    u8 pad_1e[6];
    u16 displayFlags;
    u8 pad_26[0xc];
    s16 cooldown;
    s16 effectTimer;
} AreaState;

typedef struct {
    u8 pad_000[0x13e];
    u8 starCount;
} SceneState;

typedef struct {
    u8 pad_0000[0x2772];
    s16 regionProgress;
    s32 pendingReward;
} FieldGlobals;

extern AreaState *gMovieContextState;
extern SceneState *gAreaRewardSceneWork;
extern FieldGlobals *gFieldSessionWork;
extern BOOL IsSessionFlagSet(int id);
extern void ClearSessionPackedBit(int id);
extern void SetFieldEntriesPaused(int paused);
extern void SetMenuHighlight(int on);
extern BOOL IsEntryFlag2Active(int index);
extern void QueueOrUpdateSoundKind3(int sound);
extern void UpdateAreaFromPosition(void);
extern u32 GetCurrentAreaIndex(void);
extern void RefreshAreaEventObjectAndLayerState(u32 value);
extern void StartIdleSceneObjects(void);
extern void SetFieldObjectInteractionsBlocked(int arg);
extern u8 *GetBoundedEntryField(u32 index);
extern s32 Anim_GetFrame(void *anim, u32 track);
extern s32 GetModelAnimationDurationFx32(void *anim, u32 track);
extern s32 FX_Mul(s32 a, s32 b);
extern int GetMainBrightnessSetting(void);
extern void SetFieldMenuSuspended(int a, int b);
extern void AwardSlotLevelProgress(int amount);
extern void AddRegionProgress(u8 amount);

int UpdateAreaSceneState(void) {
    AreaState *state = gMovieContextState;

    if (state->cooldown > 0) {
        state->cooldown--;
    }
    if (IsSessionFlagSet(0x3533) && state->effectTimer >= 0) {
        state->effectTimer--;
        if (state->effectTimer <= 0) {
            ClearSessionPackedBit(0x3533);
            state->effectTimer = 0;
        }
    }
    if (state->flags & 0x4000) {
        SetFieldEntriesPaused(1);
        SetMenuHighlight(1);
        return 0xe;
    }
    if (state->flags & 0x10) {
        return -1;
    }
    if (IsEntryFlag2Active(0)) {
        state->flags |= 0x10;
        QueueOrUpdateSoundKind3(0x20);
        return 0xc;
    }
    UpdateAreaFromPosition();
    RefreshAreaEventObjectAndLayerState(GetCurrentAreaIndex());
    if (state->sceneReady) {
        StartIdleSceneObjects();
        SetFieldObjectInteractionsBlocked(1);
        state->displayFlags &= ~0x10;
        {
            s32 frame;
            u8 *anim;
            SceneState **scene = &gAreaRewardSceneWork;
            s32 stars;

            (*scene)->starCount = 0;
            anim = GetBoundedEntryField(0) + 0x18;
            frame = Anim_GetFrame(anim, 0);
            stars = (FX_Mul(GetModelAnimationDurationFx32(anim, 0), 0x666) - frame) >> 12;
            if (stars > 0) {
                if (stars > 5) {
                    (*scene)->starCount = 5;
                } else {
                    (*scene)->starCount = stars;
                }
            }
        }
        if (GetMainBrightnessSetting() < 0) {
            state->flags &= ~4;
            *(vu32 *)0x04000000 = (*(vu32 *)0x04000000 & ~0x1f00) | 0x100;
            SetFieldMenuSuspended(1, 0);
        }
        return 6;
    }
    if (state->flags & 2) {
        return -1;
    }
    if (state->pendingChoice >= 0) {
        return 10;
    }
    if (GetMainBrightnessSetting() == 0) {
        if (gFieldSessionWork->pendingReward > 0) {
            AwardSlotLevelProgress(gFieldSessionWork->pendingReward);
            gFieldSessionWork->pendingReward = 0;
        }
        if (gFieldSessionWork->regionProgress > 0) {
            AddRegionProgress(gFieldSessionWork->regionProgress);
            gFieldSessionWork->regionProgress = 0;
        }
    }
    return -1;
}
