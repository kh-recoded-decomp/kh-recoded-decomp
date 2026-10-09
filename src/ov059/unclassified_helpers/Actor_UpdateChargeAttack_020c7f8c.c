#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct TrackState {
    u8 id;
    u8 pad_01[3];
    VecFx32 position;
    u8 pad_10[0x1c - 0x10];
    fx32 height;
    u8 pad_20[0x25 - 0x20];
    u8 kind;
    u16 type;
    u8 pad_28[4];
} TrackState;

typedef struct ActorStats {
    u16 pad_00;
    u16 hp;
} ActorStats;

typedef struct StageProgress {
    fx32 timer;
    int step;
    u8 flags;
    fx32 frameRemainder;
} StageProgress;

typedef struct GroundInfo {
    fx32 heightScale;
    u8 pad_04[0x28 - 0x4];
    fx32 baseZ;
} GroundInfo;

typedef struct GameState {
    u8 pad_0000[0x27b6];
    u8 pad_bits : 4;
    u8 locked : 1;
} GameState;

typedef struct Actor Actor;
typedef void (*ActorStateFunc)(Actor *actor, int state);

struct Actor {
    u8 pad_0000[0x1d4];
    ActorStats *stats;
    u8 pad_01d8[0x928 - 0x1d8];
    u64 flags;
    u8 playerIndex;
    u8 pad_0931[3];
    s32 mode : 8;
    s32 modeRest : 24;
    u8 charging : 8;
    u8 pad_0939[0x944 - 0x939];
    int state;
    fx32 elapsed;
    u8 pad_094c[0x958 - 0x94c];
    fx32 delta;
    fx32 cooldown;
    u8 pad_0960[0xeb0 - 0x960];
    u8 menuState[0x1524 - 0xeb0];
    u8 effect[0x16d4 - 0x1524];
    u8 locked;
    u8 pad_16d5[0x16f0 - 0x16d5];
    StageProgress progress;
    void *animBank;
    fx32 chargeTime;
    int target;
    s32 hitSlots[1];
    u8 pad_1710;
    s8 hitIndex;
    u8 pad_1712[0x171c - 0x1712];
    s32 stance : 8;
    s32 stanceRest : 24;
    u8 pad_1720[0x172c - 0x1720];
    fx32 idleTime;
    fx32 flashTime;
    u8 pad_1734[0x17fc - 0x1734];
    u32 sound;
    u8 pad_1800[0x1808 - 0x1800];
    ActorStateFunc setState;
    u8 pad_180c[0x181c - 0x180c];
    s16 groupId;
};

extern GameState *data_ov001_020a0460;

extern void Actor_HandleFallOut_020c837c(Actor *actor);
extern void ReadActiveMenuState_0206c328(u8 *out);
extern BOOL func_ov001_020645c8(u32 value);
extern void Actor_ProbeLinkIfFlagClear_020cb898(Actor *actor);
extern void Actor_UpdateComboStage_020c8b88(Actor *actor, StageProgress *progress, fx32 delta);
extern void *func_ov001_0206db78(u32 playerIndex);
extern BOOL HasFlagsAt0xe_020a752c(void *holder, u16 mask);
extern BOOL IsButtonAOrRActive_020cba14(void *inputState);
extern unsigned int IsGroupMemberActive_020a8d1c(unsigned int groupId, int index);
extern void func_ov021_020a8ab4(TrackState *state);
extern void Actor_GetRotatedJointPosition_020c895c(VecFx32 *out, Actor *actor);
extern VecFx32 *Actor_GetModelPosition_020cd0d8(Actor *actor);
extern GroundInfo *func_ov021_020af5f4(void);
extern int FixedPointMultiply12(int left, int right);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern int func_ov021_020a8ca0(TrackState *request, int groupId);
extern void func_ov059_020cfdec(void *effect, Actor *actor);
extern u16 GetGroupSlotValue_020a8f1c(int groupId, int index);
extern void SetSlotEntryValue_020a8f4c(int groupId, int slot, int value);
extern s32 GetSelectedMenuEntryValue_02077f80(void);
extern void StopSoundSeqHandle_0204dbe4(u32 handle);
extern void Handle_WritePayloadIfLive_0204db9c(u32 handle, VecFx32 *src);
extern void func_ov059_020ca794(Actor *actor);

void Actor_UpdateChargeAttack_020c7f8c(Actor *actor)
{
    TrackState track;
    VecFx32 joint;

    Actor_HandleFallOut_020c837c(actor);
    actor->elapsed += 0x1000;
    if (actor->cooldown > 0) {
        actor->cooldown -= actor->delta;
        if (actor->cooldown <= 0) {
            actor->cooldown = 0;
        }
    }
    if ((actor->flags & 0x400) == 0) {
        ReadActiveMenuState_0206c328(actor->menuState);
    }
    if (actor->state != 0xd && !func_ov001_020645c8(0x3525) && !data_ov001_020a0460->locked &&
        actor->stats->hp == 0) {
        actor->setState(actor, 0xd);
        return;
    }
    Actor_ProbeLinkIfFlagClear_020cb898(actor);
    Actor_UpdateComboStage_020c8b88(actor, &actor->progress, actor->delta);
    if (actor->mode == 0 && actor->locked == 0) {
        if (HasFlagsAt0xe_020a752c(func_ov001_0206db78(actor->playerIndex), 1) ||
            HasFlagsAt0xe_020a752c(func_ov001_0206db78(actor->playerIndex), 0x100)) {
            actor->mode = 1;
            actor->charging = 1;
            actor->chargeTime = 0;
        }
    }
    if (actor->charging) {
        BOOL allowed = TRUE;
        /* states 7, 17 and 18 block charging */

        u32 index = actor->state - 7;

        if (index <= 11 && ((1 << index) & 0xc01)) {
            allowed = FALSE;
        }
        if (allowed) {
            if (IsButtonAOrRActive_020cba14(func_ov001_0206db78(actor->playerIndex))) {
                actor->chargeTime += 0x1000;
                if (actor->locked == 0 && !IsGroupMemberActive_020a8d1c(actor->groupId, 0) && actor->charging &&
                    actor->chargeTime >= 0x6000 && actor->chargeTime >= 0x6000 && actor->locked == 0) {
                    func_ov021_020a8ab4(&track);
                    track.id = 0;
                    Actor_GetRotatedJointPosition_020c895c(&joint, actor);
                    track.position = joint;
                    track.kind = 5;
                    track.type = 6;
                    track.position.x = Actor_GetModelPosition_020cd0d8(actor)->x;
                    track.position.z -= 0xc00;
                    {
                        GroundInfo *ground = func_ov021_020af5f4();
                        track.height = FixedPointMultiply12(ground->heightScale, ground->baseZ - track.position.z);
                    }
                    VEC_Subtract_01ff9e3c(&track.position, Actor_GetModelPosition_020cd0d8(actor), &track.position);
                    func_ov021_020a8ca0(&track, actor->groupId);
                    actor->mode = 2;
                    func_ov059_020cfdec(actor->effect, actor);
                }
            } else {
                if (actor->state <= 4 || actor->state == 0xc) {
                    switch (actor->mode) {
                    default:
                        actor->setState(actor, 0xc);
                        break;
                    case 3:
                    case 4:
                        actor->flags &= ~0x2000;
                        break;
                    }
                    if (actor->mode == 2 && actor->locked != 0) {
                        actor->mode = 3;
                        actor->stance = 2;
                    } else {
                        actor->mode = 0;
                        actor->stance = 1;
                    }
                    actor->charging = 0;
                } else {
                    if (actor->locked != 0) {
                        goto update_sound;
                    }
                    actor->mode = 0;
                    actor->charging = 0;
                }
                SetSlotEntryValue_020a8f4c(actor->groupId, 0, GetGroupSlotValue_020a8f1c(actor->groupId, 0) & ~4);
            }
        }
    }
update_sound:
    if (!HasFlagsAt0xe_020a752c(func_ov001_0206db78(actor->playerIndex), 0x400) || actor->state == 8 ||
        actor->state == 0xd || actor->state == 0x12 || GetSelectedMenuEntryValue_02077f80() == -1 ||
        actor->hitSlots[actor->hitIndex] != 0) {
        StopSoundSeqHandle_0204dbe4(actor->sound);
        actor->sound = 0;
    } else {
        Handle_WritePayloadIfLive_0204db9c(actor->sound, Actor_GetModelPosition_020cd0d8(actor));
    }
    if (actor->idleTime != 0x7fffffff) {
        actor->idleTime += 0x1000;
    }
    if (actor->flashTime > 0) {
        actor->flashTime -= 0x1000;
        if (actor->flashTime < 0) {
            actor->flashTime = 0;
        }
    }
    if (actor->target != -1 && actor->state != 7) {
        func_ov059_020ca794(actor);
    }
}
