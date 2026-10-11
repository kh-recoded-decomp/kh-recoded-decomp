#include "src/overlays/ov001/StageActorTables.h"

/* Only the addresses are used here; the callbacks have different signatures. */
extern void RegisterActorSlotInEntity();
extern void PlaceActorAtStageAnchor();
extern void UpdateActorController();
extern void PostUpdateActorController();
extern void SweepActorMove();
extern void ProbeActorGround();

StageActorDescriptor gSpawnedActorDescriptor = {
    2, 1, 0x200, 8,
    (void *)RegisterActorSlotInEntity,
    (void *)PlaceActorAtStageAnchor,
    (void *)UpdateActorController,
    (void *)PostUpdateActorController,
    (void *)SweepActorMove,
    NULL,
    NULL,
    (void *)ProbeActorGround,
    NULL
};
