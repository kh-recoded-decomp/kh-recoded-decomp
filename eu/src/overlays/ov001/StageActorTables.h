#ifndef EU_STAGE_ACTOR_TABLES_H
#define EU_STAGE_ACTOR_TABLES_H

#include "nitro/types.h"

typedef int (*ActorControllerStateHandler)(void *controller);

/* The actor constructor copies these properties and callback addresses. */
typedef struct StageActorDescriptor {
    u32 scriptTargetKind;
    u32 actorKind;
    u32 actorFlags;
    u32 attributes;
    void *initialize;
    void *placeAtAnchor;
    void *update;
    void *postUpdate;
    void *sweepMove;
    void *callback24;
    void *callback28;
    void *probeGround;
    void *callback30;
} StageActorDescriptor;

typedef struct StageManagerTaskDescriptor {
    u32 typeAndFlags;
    void *initialize;
    void *shutdown;
    u32 workSize;
    void *parameter10;
} StageManagerTaskDescriptor;

typedef struct StageHeapConfig {
    u32 objectHeapSize;
    u32 heapSize;
    u32 eventCount;
} StageHeapConfig;

extern char gDefaultAttachPointName[4];
extern ActorControllerStateHandler gActorControllerStateHandlers[5];
extern StageActorDescriptor gSpawnedActorDescriptor;
extern StageManagerTaskDescriptor gStageManagerTaskDescriptor;
extern StageHeapConfig gStageHeapConfigs[2];
extern s8 gExtendedSlotRemap[32];
extern s8 gGroupMemberRemap[72];

#endif
