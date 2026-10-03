#include "nitro/types.h"
#include "nnsys/fnd.h"

typedef struct MemberGroup {
    s32 count;
    s32 active;
    s32 timer;
    s32 state;
    s32 currentIndex;
    s32 targetIndex;
    s32 phase;
    u8 pad1c[8];
    s16 slotIds[19];
    u8 pad4a[2];
    NNSFndList members;
    NNSFndList tasks;
} MemberGroup;

extern void func_0201288c(NNSFndList *list, u16 offset);

void InitMemberGroup_020ad5c8(MemberGroup *group)
{
    int i;

    group->count = 0;
    group->active = 0;
    group->timer = 0;
    group->state = 0;
    group->targetIndex = -1;
    group->phase = 0;
    group->currentIndex = -1;
    for (i = 0; i < 19; i++) {
        group->slotIds[i] = -1;
    }
    func_0201288c(&group->members, 0xc);
    func_0201288c(&group->tasks, 0x14);
}
