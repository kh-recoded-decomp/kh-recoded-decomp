#include "nitro/types.h"

typedef struct GroupObject {
    u8 pad_00[0x4];
    void *world;
} GroupObject;

typedef struct GroupMemberWork {
    s16 state;
    s8 groupIndex;
    u8 pad_03[0x2D];
    u32 unk_30;
} GroupMemberWork;

typedef struct ObjectGroup {
    u8 pad_00[0x8];
    u32 flags;
    u16 unk_0C;
    s16 respawnCountdown;
} ObjectGroup;

extern GroupMemberWork *func_ov032_020bbc78(GroupObject *object);
extern ObjectGroup *func_ov032_020bbc60(GroupObject *object);
extern s32 func_ov032_020bbc18(void *world, s32 groupIndex);

void InitGroupMode4_020bf1fc(GroupObject *object)
{
    GroupMemberWork *work = func_ov032_020bbc78(object);
    ObjectGroup *group = func_ov032_020bbc60(object);

    work->state = 0;
    work->unk_30 = 0;
    group->respawnCountdown = func_ov032_020bbc18(object->world, work->groupIndex);
    group->flags = (group->flags & ~8) | 4;
}
