#ifndef STAGE_MODEL_RENDER_H
#define STAGE_MODEL_RENDER_H

#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct StageModelResource {
    u8 reserved00[0x1c];
    fx32 positionScale;
} StageModelResource;

typedef struct StageModelRenderObject {
    u32 flags;
    StageModelResource *model;
    u8 reserved08[0x54];
} StageModelRenderObject;

typedef struct StageModelNode {
    u16 flags;
    u8 reserved02[0x1e];
    StageModelRenderObject renderObject;
    u8 reserved7c[0x80];
    u16 colorScale;
    u8 reservedfe[2];
} StageModelNode;

typedef struct StageModelActor {
    u8 reserved000[0x14];
    StageModelNode node;
} StageModelActor;

typedef struct StageShadowActor {
    u8 reserved000[0x14];
    StageModelNode node;
    u8 reserved114[0xc4];
    MtxFx43 shadowMatrix;
    u8 stateFlags;
} StageShadowActor;

typedef struct StageEntry StageEntry;

typedef struct StageModelWork {
    u8 reserved000[0x14];
    StageEntry *entries;
    u8 entryCount;
    u8 reserved019[0xdf];
    StageModelActor primaryActor;
    u8 reserved20c[0xc4];
    MtxFx43 primaryMatrix;
    u8 reserved300[0x48];
    u8 shadowHeightIndex;
    u8 reserved349[3];
    StageShadowActor *shadowActors[2];
} StageModelWork;

typedef struct StageModelContext {
    u8 reserved000[0xb8];
    StageModelWork *stageWork;
} StageModelContext;

extern StageModelContext *gMovieContextState;
extern void NNS_G3dGeBufferOP_N(u32 command, const void *data, u32 words);
extern void NNS_G3dGlbFlushP(void);
extern void func_01fff67c(int colorScale);
extern void NNS_G3dDraw(StageModelRenderObject *renderObject);

void DrawTrackedStageShadow(StageShadowActor *actor);
void DrawStagePrimaryModel(StageModelActor *actor);

#endif
