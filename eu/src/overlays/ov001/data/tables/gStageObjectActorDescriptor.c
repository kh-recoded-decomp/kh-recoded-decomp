#include "src/overlays/ov001/StageActorTables.h"

/* The stage-object constructor copies this descriptor into the actor. */
extern void RegisterActorSlotInRecord();
extern void ResolveStageActorSpawnPos();
extern void UpdateActorStageEvent();
extern void TryTriggerActorEvent();
extern void SweepActorStep();
extern void ProbeGroundAhead();
extern void AdjustActorCollisionMotion();
extern void ProbeGroundBetweenPoints();
extern void ProbeCeilingAboveActor();

StageActorDescriptor gStageObjectActorDescriptor = {
    1, 0, 0, 0,
    (void *)RegisterActorSlotInRecord,
    (void *)ResolveStageActorSpawnPos,
    (void *)UpdateActorStageEvent,
    (void *)TryTriggerActorEvent,
    (void *)SweepActorStep,
    (void *)ProbeGroundAhead,
    (void *)AdjustActorCollisionMotion,
    (void *)ProbeGroundBetweenPoints,
    (void *)ProbeCeilingAboveActor
};
