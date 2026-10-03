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
extern SceneState *data_ov040_020be260;
extern FieldGlobals *data_ov001_020a0460;
extern BOOL func_ov001_020645c8(int id);
extern void func_ov001_020645e8(int id);
extern void SetFieldEntriesPaused_0206e444(int paused);
extern void SetMenuHighlight_0206c2f8(int on);
extern BOOL IsEntryFlag2Active_020642d0(int index);
extern void func_0204d7f4(int sound);
extern void func_ov040_020bc500(void);
extern u32 func_ov035_020bae64(void);
extern void func_ov040_020bc81c(u32 value);
extern void StartIdleSceneObjects_02066810(void);
extern void func_ov001_02087628(int arg);
extern u8 *GetBoundedEntryField_0206db5c(u32 index);
extern s32 Anim_GetFrame_0202f4a0(void *anim, u32 track);
extern s32 func_0202f4b8(void *anim, u32 track);
extern s32 FixedPointMultiply12(s32 a, s32 b);
extern int func_02029f48(void);
extern void SetFieldMenuSuspended_02077b90(int a, int b);
extern void func_ov001_0206dfbc(void);
extern void AddRegionProgress_0206e074(u8 amount);

int UpdateAreaSceneState_020bd108(void) {
    AreaState *state = data_ov035_020bc4e0;

    if (state->cooldown > 0) {
        state->cooldown--;
    }
    if (func_ov001_020645c8(0x3533) && state->effectTimer >= 0) {
        state->effectTimer--;
        if (state->effectTimer <= 0) {
            func_ov001_020645e8(0x3533);
            state->effectTimer = 0;
        }
    }
    if (state->flags & 0x4000) {
        SetFieldEntriesPaused_0206e444(1);
        SetMenuHighlight_0206c2f8(1);
        return 0xe;
    }
    if (state->flags & 0x10) {
        return -1;
    }
    if (IsEntryFlag2Active_020642d0(0)) {
        state->flags |= 0x10;
        func_0204d7f4(0x20);
        return 0xc;
    }
    func_ov040_020bc500();
    func_ov040_020bc81c(func_ov035_020bae64());
    if (state->sceneReady) {
        StartIdleSceneObjects_02066810();
        func_ov001_02087628(1);
        state->displayFlags &= ~0x10;
        {
            s32 frame;
            u8 *anim;
            SceneState **scene = &data_ov040_020be260;
            s32 stars;

            (*scene)->starCount = 0;
            anim = GetBoundedEntryField_0206db5c(0) + 0x18;
            frame = Anim_GetFrame_0202f4a0(anim, 0);
            stars = (FixedPointMultiply12(func_0202f4b8(anim, 0), 0x666) - frame) >> 12;
            if (stars > 0) {
                if (stars > 5) {
                    (*scene)->starCount = 5;
                } else {
                    (*scene)->starCount = stars;
                }
            }
        }
        if (func_02029f48() < 0) {
            state->flags &= ~4;
            *(vu32 *)0x04000000 = (*(vu32 *)0x04000000 & ~0x1f00) | 0x100;
            SetFieldMenuSuspended_02077b90(1, 0);
        }
        return 6;
    }
    if (state->flags & 2) {
        return -1;
    }
    if (state->pendingChoice >= 0) {
        return 10;
    }
    if (func_02029f48() == 0) {
        if (data_ov001_020a0460->pendingReward > 0) {
            func_ov001_0206dfbc();
            data_ov001_020a0460->pendingReward = 0;
        }
        if (data_ov001_020a0460->regionProgress > 0) {
            AddRegionProgress_0206e074(data_ov001_020a0460->regionProgress);
            data_ov001_020a0460->regionProgress = 0;
        }
    }
    return -1;
}
