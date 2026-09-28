#include "nitro/types.h"

typedef struct GroupActor {
    u8 pad_000[0x10];
    s16 groupId;
    u8 pad_012[0x1b4 - 0x12];
    u8 groupFlagA;
    u8 groupFlagB;
} GroupActor;

typedef struct AnimController {
    u8 pad_00[0x10];
    void *defaults;
} AnimController;

typedef struct GroupMember {
    u8 pad_000[0x1d0];
    AnimController animController;
} GroupMember;

extern GroupMember *func_ov001_0209c040(s16 groupId);
extern void ClearActorMotionState_02091194(GroupMember *member);
extern void func_ov021_020b4b7c(AnimController *controller);
extern void func_ov001_02091964(GroupMember *member);
extern void func_ov001_02091ac0(GroupMember *member, u32 slotKey, u32 slotSubKey, int reserved);
extern u32 func_ov001_020925bc(GroupActor *actor, u32 state);

void ResetGroupLeaderAndSetState_02097a1c(GroupActor *actor)
{
    GroupMember *leader = func_ov001_0209c040(actor->groupId);

    if (leader != NULL) {
        actor->groupFlagA = 0;
        actor->groupFlagB = 0;
        ClearActorMotionState_02091194(leader);
        func_ov021_020b4b7c(&leader->animController);
        func_ov001_02091964(leader);
        func_ov001_02091ac0(leader, 0xffff, 0xffff, 0);
        func_ov001_020925bc(actor, 11);
    }
}
