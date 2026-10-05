#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct GroupMemberWork {
    s16 state;
    s8 groupIndex;
    s8 slotIndex;
    s16 leaderLink;
    s16 followLink;
    u8 pad_08[0x10];
    VecFx32 offset;
    VecFx32 moveDelta;
    s32 phase;
} GroupMemberWork;

typedef struct GroupObject {
    u8 pad_00[0x4];
    void *world;
    u8 pad_08[0x30];
    VecFx32 position;
    u8 pad_44[0xA8];
    GroupMemberWork *work;
} GroupObject;

typedef struct ObjectGroup {
    u32 firstMember : 9;
    u32 leaderIndex : 9;
    u32 unk_00_18 : 14;
    u32 unk_04_0 : 16;
    u32 memberTotal : 8;
    u32 arrivedCount : 8;
    u32 isFinished : 1;
    u32 unk_08_1 : 2;
    u32 isFalling : 1;
    u32 isAnchored : 1;
    u32 unk_08_5 : 27;
    u16 memberCount : 8;
    u16 unk_0C_8 : 1;
    u16 landSoundPlayed : 1;
    u16 cueSoundPlayed : 1;
    u16 unk_0C_11 : 5;
    u8 pad_0E[0x1A];
    u32 settleTimer;
} ObjectGroup;

extern const VecFx32 data_02053438;

extern ObjectGroup *func_ov032_020bbc60(GroupObject *object);
extern GroupMemberWork *func_ov032_020bbc78(GroupObject *object);
extern VecFx32 *func_ov001_0206dc4c(int index);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern BOOL ComputePushTowardTarget_020bc924(const VecFx32 *target, const VecFx32 *center, s32 *phase, VecFx32 *push);
extern void SpawnSoundSlot_0204da8c(int bank, int id, VecFx32 *position, int flags);
extern void AdvanceGroupSettleCounter_020bca54(GroupObject *object);
extern void StepTowardGroundTarget_020bc9d0(VecFx32 *out, GroupObject *object, ObjectGroup *group, GroupMemberWork *work, VecFx32 *offset, VecFx32 *position);
extern BOOL TurnTowardOpenDirection_020bcfc4(GroupObject *object, VecFx32 *position, fx32 radius);
extern void func_ov032_020bbc80(void *world, int groupIndex, int slotIndex, VecFx32 *out);
extern BOOL func_ov032_020bcf24(void *world, int groupIndex, GroupMemberWork *work, VecFx32 *position, VecFx32 *velocity, fx32 radius, VecFx32 *delta, BOOL *landed);
extern BOOL HasPendingNibbleChange_020bbf30(ObjectGroup *group);
extern void PickJitteredPlayerOffset_020bdd74(GroupObject *object, VecFx32 *offset);
extern void MoveGroupObjectAndSyncActor_020bbcc4(GroupObject *object, const VecFx32 *delta);
extern void func_ov032_020bbd60(GroupObject *object, const VecFx32 *delta);

int UpdateGatheringGroupMember_020bde54(GroupObject *object)
{
    GroupMemberWork *work = func_ov032_020bbc78(object);
    ObjectGroup *group = func_ov032_020bbc60(object);
    VecFx32 zero;
    VecFx32 delta;
    VecFx32 goal;
    BOOL landed;
    BOOL still;
    BOOL reached;

    zero = data_02053438;
    delta = data_02053438;
    switch (work->state) {
    case 0:
        work->moveDelta.x = 0;
        work->moveDelta.y = -0x8f;
        work->moveDelta.z = 0;
        if (!group->isAnchored) {
            object->work->state = 0x10;
            group->landSoundPlayed = 1;
        } else {
            object->work->state = 0xe;
        }
        break;
    case 0xe:
        if (group->arrivedCount == group->memberTotal) {
            object->work->state = 0xf;
            if (!group->cueSoundPlayed) {
                SpawnSoundSlot_0204da8c(0xf8, 7, &object->position, 0);
                group->cueSoundPlayed = 1;
            }
        } else {
            if (work->leaderLink == -1 && group->arrivedCount != group->memberTotal) {
                AdvanceGroupSettleCounter_020bca54(object);
            }
            StepTowardGroundTarget_020bc9d0(&delta, object, group, work, &work->offset, &object->position);
        }
        break;
    case 0xf:
        work->moveDelta = zero;
        work->moveDelta.y = -0x11e;
        object->work->state = 0x11;
        group->isAnchored = 0;
        break;
    case 0x10:
        if (TurnTowardOpenDirection_020bcfc4(object, &object->position, 0xc00)) {
            func_ov032_020bbc80(object->world, work->groupIndex, work->slotIndex, &work->moveDelta);
            object->work->state = 0x11;
            group->isFalling = 1;
        }
        break;
    case 0x11:
        landed = FALSE;
        still = FALSE;
        if (work->moveDelta.x == 0 && work->moveDelta.z == 0) {
            still = TRUE;
        }
        reached = func_ov032_020bcf24(object->world, work->groupIndex, work, &object->position, &work->moveDelta, 0xc00, &delta, &landed);
        if ((landed && !still) || (still && reached)) {
            object->work->state = 0x10;
        }
        if (reached && !group->landSoundPlayed) {
            SpawnSoundSlot_0204da8c(0xf8, 5, &object->position, 0);
            group->landSoundPlayed = 1;
        }
        if (HasPendingNibbleChange_020bbf30(group)) {
            PickJitteredPlayerOffset_020bdd74(object, &work->offset);
            work->phase = 0;
            work->state = 0x12;
            if (object->work->leaderLink == -1) {
                group->settleTimer = 0;
                group->isFalling = 0;
                group->isAnchored = 1;
                SpawnSoundSlot_0204da8c(0xf8, 4, &object->position, 0);
            }
        }
        break;
    case 0x12:
        VEC_Add_01ff9e0c(func_ov001_0206dc4c(0), &work->offset, &goal);
        reached = ComputePushTowardTarget_020bc924(&goal, &object->position, &work->phase, &delta);
        if (object->work->leaderLink == -1) {
            if (group->settleTimer < 4) {
                if (reached) {
                    group->settleTimer += 0x89;
                }
            } else {
                group->isFinished = 1;
            }
        }
        break;
    }
    MoveGroupObjectAndSyncActor_020bbcc4(object, &delta);
    func_ov032_020bbd60(object, &delta);
    return 0;
}




