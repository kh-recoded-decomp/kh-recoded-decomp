#include "src/overlays/ov001/StageActorTables.h"

/* Descriptor methods retain their native signatures; only addresses live here. */
extern void StageActor_DefaultInitNoop(void);
extern void SyncNearestEntryPosition();
extern void StageActor_DefaultUpdateNoop(void);
extern void StageActor_DefaultDrawNoop(void);

typedef char DefaultStageDescriptorSizeCheck[(sizeof(StageActorDescriptor) == 0x34) ? 1 : -1];
typedef char DefaultStageDescriptorInitOffsetCheck[((u32)&((StageActorDescriptor *)0)->initialize == 0x10) ? 1 : -1];
typedef char DefaultStageDescriptorUpdateOffsetCheck[((u32)&((StageActorDescriptor *)0)->update == 0x18) ? 1 : -1];
typedef char DefaultStageDescriptorDrawOffsetCheck[((u32)&((StageActorDescriptor *)0)->draw == 0x1c) ? 1 : -1];

StageActorDescriptor gDefaultStageActorDescriptor = {
    0, 0, 0, 0,
    (void *)StageActor_DefaultInitNoop,
    (void *)SyncNearestEntryPosition,
    (void *)StageActor_DefaultUpdateNoop,
    (void *)StageActor_DefaultDrawNoop,
    NULL, NULL, NULL, NULL, NULL
};
