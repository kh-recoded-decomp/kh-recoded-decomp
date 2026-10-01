#include "nitro/types.h"

typedef struct StageLink {
    u16 lowBits : 11;
    u16 stageEntry : 3;
    u16 highBits : 2;
    u8 pad_02[0x32];
    u8 entryList[4];
} StageLink;

typedef struct StageActor {
    u8 pad_000[0x1D0];
    u8 component[0xBC];
    StageLink link;
} StageActor;

typedef struct GroupTask {
    u8 pad_00[0x6];
    u16 flagsLow : 13;
    u16 pending : 1;
    u16 flagsHigh : 2;
    u8 pad_08[0x8];
    s16 actorId;
} GroupTask;

extern StageActor *GetStageActor_0209c040(int id);
extern u16 FindNearestStageEntry_02099328(void *entries);
extern StageActor *GetLinkedStageActor_0209c2f0(StageActor *actor);
extern int RunGroupScriptSlot_020925d8(StageActor *actor, int slot);
extern void func_ov021_020b4b7c(void *component);

int StartGroupStageScript_020935e0(GroupTask *task)
{
    StageActor *leader = GetStageActor_0209c040(task->actorId);
    StageActor *actor = leader;
    u16 entry;

    if (actor->link.stageEntry == 0) {
        entry = FindNearestStageEntry_02099328(leader->link.entryList);
        for (; actor != NULL; actor = GetLinkedStageActor_0209c2f0(actor)) {
            actor->link.stageEntry = entry;
        }
    }
    if (RunGroupScriptSlot_020925d8(leader, 1) != 4) {
        return 0;
    }
    task->pending = 0;
    func_ov021_020b4b7c(leader->component);
    return 3;
}
