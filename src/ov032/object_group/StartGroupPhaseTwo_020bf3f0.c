#include "nitro/types.h"

typedef struct {
    u32 pad_bits : 18;
    u32 phase : 5;
    u32 targetPhase : 5;
    u32 high : 4;
    u8 pad_04[4];
    u32 active : 1;
} GroupEntry;

typedef struct {
    u8 pad_00[2];
    s8 slot;
    u8 pad_03;
    s16 target;
} MemberState;

typedef struct {
    u8 pad_00[0xc4];
    int busy;
} GroupOwner;

typedef struct {
    u8 pad_00[4];
    GroupOwner *owner;
} Group;

extern MemberState *func_ov032_020bbc78(void *group);
extern GroupEntry *func_ov032_020bbc60(void *group);
extern void func_ov032_020bc464(GroupOwner *owner, int index, int arg);
extern void func_ov032_020bbfc4(void *group, int state);

void StartGroupPhaseTwo_020bf3f0(Group *group)
{
    MemberState *state = func_ov032_020bbc78(group);
    GroupEntry *entry = func_ov032_020bbc60(group);

    if (state->target == -1 && group->owner->busy == 0) {
        entry->active = 1;
        func_ov032_020bc464(group->owner, state->slot, 1);
        entry->targetPhase = 2;
        entry->phase = entry->targetPhase;
        func_ov032_020bbfc4(group, 5);
    }
}
