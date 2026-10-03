#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct {
    u32 firstMember : 9;
    u32 unk_00_9 : 23;
    u32 formation : 4;
    u32 prevFormation : 4;
    u32 unk_04_8 : 8;
    u32 memberTotal : 8;
    u32 arrivedCount : 8;
    u32 unk_08;
    u16 memberCount : 8;
    u16 unk_0c_8 : 1;
    u16 turning : 1;
    u16 settled : 1;
    u16 unk_0c_11 : 5;
    u8 pad_0e[8];
    u16 unk_16;
    u8 pad_18[2];
    u16 unk_1a;
    u8 pad_1c[0x18];
    u32 unk_34;
    u8 pad_38[0x1a8];
} FieldObject;

typedef struct {
    u8 pad_00[0xcc];
    FieldObject *objects;
} FieldContext;

typedef struct {
    u8 pad_00[4];
    FieldContext *world;
} GroupObject;

typedef struct {
    s16 state;
    s8 groupIndex;
    s8 slotIndex;
    u8 pad_04[4];
    u32 hopping : 1;
    u32 rising : 1;
    u32 facingFlip : 1;
    u32 unk_08_3 : 29;
    u8 pad_0c[4];
    s32 unk_10;
    s32 unk_14;
    u8 pad_18[0x18];
    s32 unk_30;
    MtxFx33 basis;
} GroupMemberWork;

extern const MtxFx33 data_02053444;
extern const VecFx32 data_02053438;

extern GroupMemberWork *func_ov032_020bbc78(GroupObject *object);
extern GroupObject *func_ov001_0208635c(FieldContext *context, int index);
extern BOOL IsFieldUnitPhase6_020a6a64(GroupObject *object);
extern void func_ov032_020bbd60(GroupObject *object, const VecFx32 *dir);
extern void func_ov032_020bd954(GroupObject *object);
extern void func_ov032_020bddf8(GroupObject *object);
extern void func_ov032_020be654(GroupObject *object);
extern void ResetGroupMemberPhases_020bea44(GroupObject *object);
extern void InitGroupMode4_020bf1fc(GroupObject *object);
extern void ScatterGroupMembers_020befbc(GroupObject *object);

void SetGroupFormation_020bbfc4(GroupObject *object, u32 formation)
{
    FieldContext *world = object->world;
    GroupMemberWork *work = func_ov032_020bbc78(object);
    FieldObject *group = &world->objects[work->groupIndex];
    int i;

    for (i = 0; i < group->memberCount; i++) {
        GroupObject *member = func_ov001_0208635c(world, group->firstMember + i);
        GroupMemberWork *memberWork = func_ov032_020bbc78(member);
        if (!IsFieldUnitPhase6_020a6a64(member)) {
            memberWork->hopping = 0;
            memberWork->rising = 0;
            memberWork->unk_14 = 0;
            memberWork->facingFlip = 0;
            memberWork->unk_10 = 0;
            memberWork->unk_30 = 0;
        }
        memberWork->basis = data_02053444;
        func_ov032_020bbd60(member, &data_02053438);
    }
    switch (formation) {
    case 0:
        func_ov032_020bd954(object);
        break;
    case 1:
        func_ov032_020bddf8(object);
        break;
    case 2:
        func_ov032_020be654(object);
        break;
    case 4:
        InitGroupMode4_020bf1fc(object);
        break;
    case 3:
        ResetGroupMemberPhases_020bea44(object);
        break;
    case 5:
        ScatterGroupMembers_020befbc(object);
        break;
    }
    group->turning = 0;
    group->settled = 0;
    group->unk_1a = 0;
    group->arrivedCount = 0;
    group->formation = formation;
    group->unk_16 = 0;
    group->prevFormation = group->formation;
    group->unk_34 = 0;
}
