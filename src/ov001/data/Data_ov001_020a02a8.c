#include "nitro/types.h"

#pragma explicit_zero_data on

extern void ProbeCeilingAboveActor_02092124(void);
extern void ProbeGroundAhead_02091d9c(void);
extern void ProbeGroundBetweenPoints_0209206c(void);
extern void RegisterActorSlotInRecord_02091cf8(void);
extern void ResolveStageActorSpawnPos_02091d18(void);
extern void SweepActorStep_02091e68(void);
extern void TryTriggerActorEvent_0209256c(void);
extern void UpdateActorStageEvent_0209252c(void);
extern void func_ov001_0209224c(void);

void *data_ov001_020a02a8[13] = {
    (void *)0x00000001,
    NULL,
    NULL,
    NULL,
    (void *)RegisterActorSlotInRecord_02091cf8,
    (void *)ResolveStageActorSpawnPos_02091d18,
    (void *)UpdateActorStageEvent_0209252c,
    (void *)TryTriggerActorEvent_0209256c,
    (void *)SweepActorStep_02091e68,
    (void *)ProbeGroundAhead_02091d9c,
    (void *)func_ov001_0209224c,
    (void *)ProbeGroundBetweenPoints_0209206c,
    (void *)ProbeCeilingAboveActor_02092124,
};
