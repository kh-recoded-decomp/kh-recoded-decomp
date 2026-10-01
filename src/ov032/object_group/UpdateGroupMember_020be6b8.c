#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct GroupMemberWork {
    s16 state;
    s8 groupIndex;
    s8 slotIndex;
    s16 leaderLink;
    u8 pad_06[0x1E];
    VecFx32 moveDelta;
    s32 unk_30;
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
    u16 unk_0C_8 : 2;
    u16 cueSoundPlayed : 1;
    u16 unk_0C_11 : 5;
    u8 pad_0E[0x1A];
    u32 settleTimer;
    u8 pad_2C[0xC];
    VecFx32 memberOffsets[20];
    VecFx32 center;
    VecFx32 velocity;
} ObjectGroup;

extern const VecFx32 data_02053438;

extern GroupMemberWork *func_ov032_020bbc78(GroupObject *object);
extern ObjectGroup *func_ov032_020bbc60(GroupObject *object);
extern GroupObject *func_ov001_0208635c(void *world, int index);
extern void InitGroupFormation_020be0c8(GroupObject *object);
extern void func_0204da8c(int bank, int soundId, VecFx32 *position, int flags);
extern void func_ov032_020bca54(GroupObject *object);
extern BOOL func_ov032_020be5c0(GroupObject *object);
extern int func_ov032_020bc6d8(GroupObject *object);
extern VecFx32 func_ov032_020bc9d0(GroupObject *object, ObjectGroup *group, GroupMemberWork *work, VecFx32 *offset, VecFx32 *position);
extern BOOL func_ov032_020bc8d4(VecFx32 *position, VecFx32 *velocity, VecFx32 *out, fx32 radius);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void func_ov032_020be454(GroupObject *object, s32 *mask);
extern BOOL func_ov032_020bcfc4(GroupObject *object, VecFx32 *position, fx32 radius);
extern void func_ov032_020bbc80(void *world, int groupIndex, int slotIndex, VecFx32 *out);
extern BOOL func_ov032_020bcf24(void *world, int groupIndex, GroupMemberWork *work, VecFx32 *position, VecFx32 *velocity, fx32 radius, VecFx32 *delta, BOOL *landed);
extern BOOL func_ov032_020bbf30(ObjectGroup *group);
extern void *func_ov001_0206dc4c(int index);
extern BOOL func_ov032_020bc924(void *target, VecFx32 *center, s32 *phase, VecFx32 *push);
extern void func_ov032_020be348(GroupObject *object, const VecFx32 *delta);
extern void func_ov032_020bbcc4(GroupObject *object, VecFx32 *delta);

int UpdateGroupMember_020be6b8(GroupObject *object)
{
    GroupMemberWork *work = func_ov032_020bbc78(object);
    ObjectGroup *group = func_ov032_020bbc60(object);
    VecFx32 position = group->center;
    GroupObject *leader = func_ov001_0208635c(object->world, group->leaderIndex);

    if (object->work->leaderLink == -1) {
        position.y -= 0x1b33;
    }
    switch (work->state) {
    case 0:
        if (object->work->leaderLink == -1) {
            InitGroupFormation_020be0c8(object);
        }
        if (group->isAnchored) {
            object->work->state = 8;
        } else {
            object->work->state = 10;
        }
        break;
    case 8:
        if (group->arrivedCount == group->memberTotal) {
            object->work->state = 9;
            work->moveDelta = data_02053438;
            if (!group->cueSoundPlayed) {
                func_0204da8c(0xf8, 7, &object->position, 0);
                group->cueSoundPlayed = 1;
            }
        } else if (work->leaderLink == -1) {
            if (group->arrivedCount != group->memberTotal) {
                func_ov032_020bca54(object);
            }
            if (func_ov032_020be5c0(object)) {
                work->moveDelta = group->velocity;
                group->arrivedCount = 1;
            } else {
                work->moveDelta = group->velocity;
            }
        } else {
            VecFx32 offset = group->memberOffsets[func_ov032_020bc6d8(object)];
            work->moveDelta = func_ov032_020bc9d0(object, group, work, &offset, &object->position);
        }
        break;
    case 9:
        if (object->work->leaderLink == -1) {
            group->velocity.z = 0;
            group->velocity.x = 0;
            group->velocity.y -= 0x1ad;
            if (func_ov032_020bc8d4(&position, &group->velocity, &group->velocity, 0x1b33)) {
                object->work->state = 10;
                func_0204da8c(0xf8, 5, &object->position, 0);
            }
            VEC_Add_01ff9e0c(&group->center, &group->velocity, &group->center);
        } else {
            object->work->state = leader->work->state;
        }
        {
            s32 mask = 0x3f;
            func_ov032_020be454(object, &mask);
        }
        break;
    case 10:
        if (object->work->leaderLink == -1) {
            group->isFalling = 1;
            group->isAnchored = 0;
            if (func_ov032_020bcfc4(object, &position, 0x1b33)) {
                func_ov032_020bbc80(object->world, work->groupIndex, work->slotIndex, &group->velocity);
                object->work->state = 11;
            }
        } else {
            object->work->state = 11;
        }
        func_ov032_020be348(object, &data_02053438);
        break;
    case 11:
        if (object->work->leaderLink == -1) {
            BOOL landed = 0;
            VecFx32 delta = data_02053438;
            BOOL reached = func_ov032_020bcf24(object->world, work->groupIndex, work, &position, &group->velocity, 0x1b33, &delta, &landed);

            if (landed) {
                object->work->state = 10;
            }
            VEC_Add_01ff9e0c(&group->center, &delta, &group->center);
            if (reached) {
                if (func_ov032_020bbf30(group)) {
                    object->work->state = 12;
                    group->isFalling = 0;
                    group->settleTimer = 0;
                    group->isAnchored = 1;
                    work->unk_30 = 0;
                    func_0204da8c(0xf8, 4, &object->position, 0);
                }
            } else if (group->center.y < 0) {
                work->state = 8;
            }
            func_ov032_020be348(object, &delta);
        } else {
            object->work->state = leader->work->state;
            func_ov032_020be348(object, &data_02053438);
        }
        break;
    case 12:
        if (object->work->leaderLink == -1) {
            if (group->settleTimer < 4) {
                VecFx32 push;
                if (func_ov032_020bc924(func_ov001_0206dc4c(0), &group->center, &work->unk_30, &push)) {
                    group->settleTimer += 0x89;
                }
                group->velocity = data_02053438;
                VEC_Add_01ff9e0c(&group->center, &push, &group->center);
            } else {
                group->isFinished = 1;
            }
        }
        func_ov032_020be348(object, &data_02053438);
        break;
    }
    func_ov032_020bbcc4(object, &work->moveDelta);
    return 0;
}
