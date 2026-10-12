#ifndef STAGE_ENTRY_RENDER_H
#define STAGE_ENTRY_RENDER_H

#include "src/overlays/ov041/StageModelRender.h"

typedef struct StageEntryNode {
    u16 flags;
    u8 reserved02[0x192];
} StageEntryNode;

typedef struct StageEntrySlot {
    u8 reserved000[0x10];
    u32 flags;
    StageEntryNode node;
    VecFx32 shadowPosition;
} StageEntrySlot;

typedef struct StageGroundShadow {
    u8 reserved00[0xa4];
    VecFx32 position;
    VecFx32 scale;
    u8 reservedbc[0x50];
} StageGroundShadow;

typedef struct StageTrackedNode {
    u8 flags;
} StageTrackedNode;

struct StageEntry {
    u8 kind;
    u8 reserved001[7];
    u32 flags;
    u8 reserved00c[0x110];
    int delay;
    int animationFrame;
    u8 reserved124[0x38];
    StageEntrySlot slot;
    u8 reserved310[0x10];
    s16 frameStep;
    u8 reserved322[0x12];
    StageShadowActor *attachment;
    u8 reserved338[0x54];
    StageTrackedNode *trackedNodes[5];
    u8 reserved3a0[8];
    StageGroundShadow shadow;
};

typedef struct StageRenderCapture {
    u8 reserved00[0x10];
    StageEntry *entry;
} StageRenderCapture;

extern StageRenderCapture data_ov041_020cff48;
extern const fx32 gStageShadowHeights[4];
extern void GetPositionAboveGround(VecFx32 *position, StageEntry *entry);
extern void ShadowVolume_Draw(const VecFx32 *position);
extern void SceneNode_Draw(void *node);

void DrawStageEntryModels(StageEntrySlot *slot, BOOL drawShadow);
void UpdateStageEntryAnimation(StageEntrySlot *slot);

#endif
