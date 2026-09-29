#include "nitro/types.h"

typedef struct GroupActor {
    u8 pad_000[0x10];
    s16 groupId;
} GroupActor;

typedef struct GroupMember {
    u8 pad_000[0x288];
    u16 unk_288_0 : 9;
    u16 followsLeaderAnimation : 1;
    u16 unk_288_10 : 6;
} GroupMember;

extern GroupMember *func_ov001_0209c040(s16 groupId);
extern GroupMember *func_ov001_0209c2f0(GroupMember *member);
extern void func_ov001_02091a00(GroupMember *member, u32 track, u8 animId, u32 blendFrames, BOOL enable);

void SetGroupAnimationTrack_02097994(GroupActor *actor, u32 track, u8 animId, u32 blendFrames, BOOL enable)
{
    GroupMember *member = func_ov001_0209c040(actor->groupId);
    GroupMember *leader = member;

    for (; member != NULL; member = func_ov001_0209c2f0(member)) {
        if (member == leader || member->followsLeaderAnimation) {
            func_ov001_02091a00(member, track, animId, blendFrames, enable);
        }
    }
}
