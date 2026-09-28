#include "nitro/types.h"

typedef struct GroupObject {
    u8 pad_00[0x4];
    void *world;
} GroupObject;

typedef struct GroupMemberWork {
    s16 state;
    s8 groupIndex;
} GroupMemberWork;

typedef struct ObjectGroup {
    u8 pad_00[0x10];
    u16 respawnTimer;
} ObjectGroup;

extern ObjectGroup *func_ov032_020bbc60(GroupObject *object);
extern GroupMemberWork *func_ov032_020bbc78(GroupObject *object);
extern s32 func_ov032_020bbc18(void *world, s32 groupIndex);
extern void func_ov032_020bd288(void *world, s32 groupIndex, GroupObject *object);

void ForceGroupRespawn_020bd414(GroupObject *object)
{
    ObjectGroup *group = func_ov032_020bbc60(object);
    GroupMemberWork *work = func_ov032_020bbc78(object);

    group->respawnTimer = func_ov032_020bbc18(object->world, work->groupIndex);
    func_ov032_020bd288(object->world, work->groupIndex, object);
}
