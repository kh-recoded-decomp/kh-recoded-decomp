#ifndef STAGE_ENTRY_RENDER_H
#define STAGE_ENTRY_RENDER_H

#include "src/overlays/ov041/StageModelRender.h"
#include "src/overlays/ov041/StageResources.h"

typedef struct StageEntryNode {
    u16 flags;
    u8 reserved02[0xa2];
    VecFx32 position;
    u8 reserved0b0[0xe4];
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

/* StageEntry.state */
#define STAGE_ENTRY_WAITING 1
#define STAGE_ENTRY_ACTIVE 2

/* StageEntry.state of an entry that is out */
#define STAGE_ENTRY_OUT 6

#define STAGE_ENTRY_FLAG_800 0x800

#define STAGE_ENTRY_STATUS_COUNT 11

/* StageMotion speed profiles */
#define STAGE_MOTION_EASE_IN 0 /* starts at rest */
#define STAGE_MOTION_EASE_OUT 1 /* comes to rest */
#define STAGE_MOTION_STEADY 2

/* A move from start to end over duration frames: speed plus accel per elapsed frame, in units per frame. */
typedef struct StageMotion {
    fx32 elapsed;
    fx32 duration;
    VecFx32 start;
    VecFx32 end;
    fx32 speed;
    fx32 accel;
} StageMotion;

typedef struct StageEntryAction {
    u8 reserved00[0x1c];
    u8 kind;
    u8 reserved1d[0x1b];
} StageEntryAction;

typedef void (*StageEntryFunc)(u8 entryIndex);

struct StageEntry {
    u8 kind;
    u8 index; /* its own place in StageWork.entries */
    u8 reserved002[2];
    u8 state;
    u8 previousState;
    u8 pending;
    u8 reserved007;
    u32 flags;
    u8 reserved00c[4];
    s8 actionIndex; /* the action being carried out, or -1 */
    u8 reserved011;
    u8 targetCount;
    u8 targets[9]; /* indices of the entries the action is aimed at */
    u8 reserved01c[0x108 - 0x1c];
    s8 actionCount;
    u8 reserved109[3];
    StageEntryAction *actions;
    s8 statuses[STAGE_ENTRY_STATUS_COUNT];
    u8 reserved11b;
    int delay;
    int animationFrame;
    u8 reserved124[0xc];
    VecFx32 overheadOffset; /* from its position to where things are shown above it */
    u8 reserved13c[0x20];
    StageEntrySlot slot;
    u8 reserved310[0x10];
    s16 frameStep;
    u8 reserved322[0x12];
    StageShadowActor *attachment;
    u8 reserved338[0x20];
    StageMotion motion;
    u8 reserved380[0xc];
    StageTrackedNode *trackedNodes[5];
    StageResourceItem *statusItem;
    u8 reserved3a4[4];
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

typedef char StageEntrySize[sizeof(StageEntry) == 0x4b4 ? 1 : -1];
typedef char StageEntryActionSize[sizeof(StageEntryAction) == 0x38 ? 1 : -1];
typedef char StageEntryActionsOffset[(u32)&((StageEntry *)0)->actions == 0x10c ? 1 : -1];
typedef char StageEntryMotionOffset[(u32)&((StageEntry *)0)->motion == 0x358 ? 1 : -1];
typedef char StageEntryStatusesOffset[(u32)&((StageEntry *)0)->statuses == 0x110 ? 1 : -1];
typedef char StageEntryStatusItemOffset[(u32)&((StageEntry *)0)->statusItem == 0x3a0 ? 1 : -1];
typedef char StageEntryPositionOffset[(u32)&((StageEntry *)0)->slot.node.position == 0x214 ? 1 : -1];

#endif
