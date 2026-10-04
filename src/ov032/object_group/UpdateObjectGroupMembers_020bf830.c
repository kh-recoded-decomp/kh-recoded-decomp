#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct GroupWorld {
    u8 pad_00[0x59];
    u8 kind;
} GroupWorld;

typedef struct GroupMemberWork {
    s16 state;
    s8 groupIndex;
    s8 slotIndex;
    s16 leaderLink;
    s16 nextLink;
    u32 unk_08_0 : 5;
    u32 order : 8;
    u32 unk_08_13 : 19;
} GroupMemberWork;

typedef struct GroupObject {
    u8 pad_00[0x4];
    GroupWorld *world;
    u8 pad_08[0x2b];
    u8 actorId;
    u8 pad_34[0x4];
    VecFx32 position;
    u8 pad_44[0x2c];
    u16 unk_70_0 : 1;
    u16 isMoving : 1;
    u16 unk_70_2 : 3;
    u16 isUpdated : 1;
    u16 unk_70_6 : 10;
    u8 pad_72[0x4c];
    u8 unk_be_0 : 4;
    u8 phase : 4;
    u8 pad_bf[0x2d];
    GroupMemberWork *work;
} GroupObject;

typedef struct ObjectGroup {
    u32 unk_00;
    u32 mode : 4;
    u32 unk_04_4 : 28;
    u32 needsRebuild : 1;
    u32 needsRefresh : 1;
    u32 unk_08_2 : 3;
    u32 dirty : 1;
    u32 unk_08_6 : 26;
    u16 unk_0c_0 : 8;
    u16 showGauge : 1;
    u16 unk_0c_9 : 7;
    u8 pad_0e[0xe];
    s32 maxHitPoints;
    s32 hitPoints;
} ObjectGroup;

extern ObjectGroup *func_ov032_020bbc60(GroupObject *object);
extern GroupMemberWork *func_ov032_020bbc78(GroupObject *object);
extern GroupObject *func_ov001_0208635c(GroupWorld *world, int index);
extern void func_ov032_020bf790(GroupWorld *world, int groupIndex);
extern void func_ov032_020bc4f8(GroupWorld *world, int groupIndex);
extern void func_ov032_020bc108(GroupObject *object);
extern void func_ov032_020bd9b8(int index, GroupObject *object);
extern void func_ov032_020bde54(GroupObject *object);
extern int UpdateGroupMember_020be6b8(GroupObject *object);
extern void func_ov032_020bf230(GroupObject *object);
extern void func_ov032_020beb6c(GroupObject *object);
extern void func_ov032_020bf0b8(GroupObject *object);
extern u8 func_ov032_020bd02c(GroupObject *object, int index);
extern BOOL IsRowSettledInMode5_020bf088(GroupWorld *world, int groupIndex);
extern void func_ov001_020881dc(u32 slotIndex, u8 kind, u8 subKind, s32 hitPoints, s32 maxHitPoints, const VecFx32 *position);

int UpdateObjectGroupMembers_020bf830(GroupObject *object)
{
    ObjectGroup *group;
    GroupObject *member;
    int index;
    GroupMemberWork *work;

    if (object->phase == 6) {
        return 0;
    }
    if (object->phase == 5) {
        return 0;
    }
    if (-1 == object->work->leaderLink) {
        group = func_ov032_020bbc60(object);

        VecFx32 position;
        member = object;
        index = 0;
        position = member->position;
        func_ov032_020bf790(object->world, object->work->groupIndex);
        if (group->needsRefresh) {
            func_ov032_020bc4f8(object->world, object->work->groupIndex);
        }
        if (group->needsRebuild) {
            func_ov032_020bc108(object);
        }
        if (group->dirty) {
            group->dirty = 0;
        }
        while (member != NULL) {
            work = func_ov032_020bbc78(member);
            switch (group->mode) {
            case 0:
                func_ov032_020bd9b8(index, member);
                break;
            case 1:
                func_ov032_020bde54(member);
                break;
            case 2:
                UpdateGroupMember_020be6b8(member);
                break;
            case 4:
                func_ov032_020bf230(member);
                break;
            case 3:
                func_ov032_020beb6c(member);
                break;
            case 5:
                func_ov032_020bf0b8(member);
                break;
            }
            member->isUpdated = 1;
            member->isMoving = 0;
            work->order = func_ov032_020bd02c(member, index);
            ++index;
            if (work->nextLink != -1) {
                member = func_ov001_0208635c(object->world, work->nextLink);
            } else {
                member = NULL;
            }
        }
        if (IsRowSettledInMode5_020bf088(object->world, object->work->groupIndex)) {
            position.y = 0x96000;
        }
        if (group->showGauge) {
            func_ov001_020881dc(object->work->groupIndex, object->world->kind, object->actorId, group->hitPoints << 3,
                                group->maxHitPoints << 3, &position);
        }
    }
        return 0;
}
