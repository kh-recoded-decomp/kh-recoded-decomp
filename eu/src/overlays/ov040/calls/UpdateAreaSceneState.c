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

extern AreaState *data_ov035_020bc4e0;
extern SceneState *data_ov040_020be280;
extern FieldGlobals *data_ov001_020a0480;
extern BOOL IsSessionFlagSet(int id);
extern void ClearSessionPackedBit(int id);
extern void SetFieldEntriesPaused(int paused);
extern void SetMenuHighlight(int on);
extern BOOL IsEntryFlag2Active(int index);
extern void func_0204d808(int sound);
extern void UpdateAreaFromPosition(void);
extern u32 func_ov035_020bae84(void);
extern void func_ov040_020bc83c(u32 value);
extern void StartIdleSceneObjects(void);
extern void func_ov001_02087650(int arg);
extern u8 *GetBoundedEntryField(u32 index);
extern s32 Anim_GetFrame(void *anim, u32 track);
extern s32 func_0202f4cc(void *anim, u32 track);
extern s32 FX_Mul(s32 a, s32 b);
extern int func_02029f5c(void);
extern void SetFieldMenuSuspended(int a, int b);
extern void func_ov001_0206dfbc(void);
extern void AddRegionProgress(u8 amount);

int UpdateAreaSceneState(void) {
    AreaState *state = data_ov035_020bc4e0;

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
        func_0204d808(0x20);
        return 0xc;
    }
    UpdateAreaFromPosition();
    func_ov040_020bc83c(func_ov035_020bae84());
    if (state->sceneReady) {
        StartIdleSceneObjects();
        func_ov001_02087650(1);
        state->displayFlags &= ~0x10;
        {
            s32 frame;
            u8 *anim;
            SceneState **scene = &data_ov040_020be280;
            s32 stars;

            (*scene)->starCount = 0;
            anim = GetBoundedEntryField(0) + 0x18;
            frame = Anim_GetFrame(anim, 0);
            stars = (FX_Mul(func_0202f4cc(anim, 0), 0x666) - frame) >> 12;
            if (stars > 0) {
                if (stars > 5) {
                    (*scene)->starCount = 5;
                } else {
                    (*scene)->starCount = stars;
                }
            }
        }
        if (func_02029f5c() < 0) {
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
    if (func_02029f5c() == 0) {
        if (data_ov001_020a0480->pendingReward > 0) {
            func_ov001_0206dfbc();
            data_ov001_020a0480->pendingReward = 0;
        }
        if (data_ov001_020a0480->regionProgress > 0) {
            AddRegionProgress(data_ov001_020a0480->regionProgress);
            data_ov001_020a0480->regionProgress = 0;
        }
    }
    return -1;
}
