#include "nitro/types.h"

typedef struct StageActorFlags {
    u32 bits : 31;
    u32 top : 1;
} StageActorFlags;

typedef struct StageActor {
    u8 pad_000[0x1d0];
    u8 runner[0x26c - 0x1d0];
    StageActorFlags flags;
    u8 pad_270[0x29c - 0x270];
    int pending;
} StageActor;

typedef struct StageEvent {
    u16 pad_00[2];
    u16 lowFlags : 13;
    u16 resumes : 1;
    u16 highFlags : 2;
    u16 lowState : 10;
    u16 effectPending : 1;
    u16 highState : 5;
    u8 pad_08[8];
    s16 actorId;
    u16 objectId;
    u8 pad_14[0x70 - 0x14];
    int nextState;
    int resumeState;
    u8 pad_78[0x1b8 - 0x78];
    u16 slots[2];
} StageEvent;

extern int Session_Exists_02063a24(void);
extern BOOL func_ov001_020645c8(u32 value);
extern void ClearActorMotionState_02091194(StageActor *actor);
extern void ClearActorGroupFlagsAndNotify_02092ad0(StageEvent *event);
extern void StartStageEventEffect_02097b88(StageEvent *event);
extern int ReleaseStageSlotEntry_0209c024(int index, int slot);
extern StageActor *GetStageActor_0209c040(int id);
extern void *GetStageObjectHandle_0209c0c4(u32 id);
extern int func_ov021_020b4bdc(void *runner, int slot);

int FinishStageEventStep_02093a04(StageEvent *event)
{
    StageActor *actor = GetStageActor_0209c040(event->actorId);
    int i;

    GetStageObjectHandle_0209c0c4(event->objectId);
    if (event->effectPending) {
        event->effectPending = 0;
        StartStageEventEffect_02097b88(event);
    }
    ClearActorGroupFlagsAndNotify_02092ad0(event);
    actor->pending = 0;
    if (!Session_Exists_02063a24() || !func_ov001_020645c8(0x379c)) {
        if (func_ov021_020b4bdc(actor->runner, 8) != 4) {
            return 0;
        }
    }
    ClearActorMotionState_02091194(actor);
    for (i = 0; i < 2; i++) {
        if (event->slots[i] != 0) {
            ReleaseStageSlotEntry_0209c024(4, event->slots[i]);
            event->slots[i] = 0;
        }
    }
    actor->flags.bits &= ~1;
    if (event->resumes) {
        event->nextState = event->resumeState;
        return 3;
    }
    return 8;
}
