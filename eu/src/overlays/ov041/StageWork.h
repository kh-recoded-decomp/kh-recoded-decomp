#ifndef STAGE_WORK_H
#define STAGE_WORK_H

#include "nitro/types.h"
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

typedef struct StageResourceHeader {
    u16 reserved00;
    u16 recordCount;
} StageResourceHeader;

typedef struct StageResourceContainer {
    StageResourceHeader *header;
    u8 cursor;
    u8 reserved05[3];
} StageResourceContainer;

/* StageResourceItem.flags */
#define STAGE_ITEM_VISIBLE 1
#define STAGE_ITEM_DRAW 2
#define STAGE_ITEM_IN_USE 4
#define STAGE_ITEM_PERSISTENT 8
#define STAGE_ITEM_OWN_MATRIX 0x10
#define STAGE_ITEM_HELD 0x20

/* The model of an item: animation bindings and render object, then its placement. */
/* StageItemModel.flags */
#define STAGE_MODEL_USE_YAW 0x20 /* rotation from the yaw angle; cleared when a matrix is set instead */
#define STAGE_MODEL_COLOR_SCALE 0x40

typedef struct StageItemModel {
    u16 flags;
    u8 reserved02[0x1e];
    StageModelRenderObject renderObject;
    u8 reserved07c[4];
    MtxFx33 rotation; /* with position: the 4x3 matrix it is drawn with */
    VecFx32 position;
    u8 reserved0b0[0x28];
    u8 blend[0x24];
    u16 colorScale;
    u8 reserved0fe[0x3a];
} StageItemModel;

typedef struct StageResourceItem {
    u8 flags;
    u8 variant;
    u8 reserved02[2];
    StageItemModel model;
} StageResourceItem;

typedef struct StageResourceList {
    StageResourceItem *items;
    u8 count;
    u8 reserved05[3];
} StageResourceList;

typedef struct StageResourceGroup {
    StageResourceList *lists;
    u8 count;
    u8 reserved05[3];
} StageResourceGroup;

/* A screen-space marker (a point projected from the stage). */
typedef struct StageScreenPoint {
    fx32 x;
    fx32 y;
} StageScreenPoint;

/* StageMarker.flags */
#define STAGE_MARKER_VISIBLE 1
#define STAGE_MARKER_IN_USE 2
#define STAGE_MARKER_PERSISTENT 4

typedef struct StageMarker {
    u8 reserved00[0x10];
    StageScreenPoint screen;
    u8 reserved18[0x18];
    u8 timer;
    u8 flags;
    u8 reserved32[2];
} StageMarker;

typedef struct StageMarkerList {
    StageMarker *markers;
    u8 count;
    u8 reserved05[3];
} StageMarkerList;

/* StageHudMessage.flags */
#define STAGE_HUD_MESSAGE_SHOWN 1

/* A HUD message line: its kind picks the text, args fill it in (kind 6 has a short string instead). */
typedef struct StageHudMessage {
    u8 kind;
    u8 timer;
    u8 flags;
    u8 reserved03;
    union {
        int args[3];
        char text[12];
    };
} StageHudMessage;

/* The factor of each scale level: 0.1, 0.15 and 0.2. */
typedef struct StageScaleFactors {
    fx32 values[3];
} StageScaleFactors;

/* StageWork.flags */
#define STAGE_WORK_NO_TIMED_INPUT 4
#define STAGE_WORK_SKIP_CHANCE_A 8
#define STAGE_WORK_SKIP_CHANCE_B 0x10
#define STAGE_WORK_FIELD_OP_DONE 0x4000
#define STAGE_WORK_PANEL_MOVING 0x4000000
#define STAGE_WORK_FAST_PANELS 0x20000000

typedef struct StageEntry StageEntry;

typedef void (*StageStateFunc)(void);

/* The stage (gMovieContextState->stageWork): state machine, entries, models, markers and resource lists. */
typedef struct StageWork {
    u8 reserved000[6];
    u8 state;
    s8 stateStep;
    u32 flags;
    u8 stateTimer;
    u8 reserved00d[7];
    StageEntry *entries;
    u8 entryCount;
    u8 primaryCount; /* entries [0, primaryCount) are the primary ones, the secondary ones follow */
    u8 secondaryCount;
    u8 reserved01b[0x20 - 0x1b];
    void *subModeTask;
    u8 commandId;
    u8 reserved025;
    u8 targetIndex;
    u8 commandEffectKind;
    u8 reserved028[0xd4 - 0x28];
    StageMarker *commandMarkers[9];
    StageModelActor primaryActor;
    u8 reserved20c[0xc4];
    MtxFx43 primaryMatrix;
    u8 reserved300[0x14];
    StageMarkerList markerLists[4];
    u8 reserved334[4];
    StageHudMessage hudMessage;
    u8 shadowHeightIndex;
    u8 panelState;
    u8 reserved34a[2];
    StageShadowActor *shadowActors[2];
    void *messages;
    StageResourceList *lists[0x3e];
    StageResourceGroup *groups[0x1b];
} StageWork;

typedef struct StageContext {
    u8 reserved000[6];
    u16 flags;
    u8 reserved008[0xb8 - 8];
    StageWork *stageWork;
} StageContext;

extern StageContext *gMovieContextState;

typedef char StageResourceListSize[sizeof(StageResourceList) == 8 ? 1 : -1];
typedef char StageItemModelSize[sizeof(StageItemModel) == 0x138 ? 1 : -1];
typedef char StageResourceItemSize[sizeof(StageResourceItem) == 0x13c ? 1 : -1];
typedef char StageMarkerSize[sizeof(StageMarker) == 0x34 ? 1 : -1];
typedef char StageMarkerListsOffset[(u32)&((StageWork *)0)->markerLists == 0x314 ? 1 : -1];
typedef char StageResourceListsOffset[(u32)&((StageWork *)0)->lists == 0x358 ? 1 : -1];

typedef char StageWorkCommandMarkersOffset[(u32)&((StageWork *)0)->commandMarkers == 0xd4 ? 1 : -1];
typedef char StageWorkPrimaryActorOffset[(u32)&((StageWork *)0)->primaryActor == 0xf8 ? 1 : -1];
typedef char StageWorkPrimaryMatrixOffset[(u32)&((StageWork *)0)->primaryMatrix == 0x2d0 ? 1 : -1];
typedef char StageWorkHudMessageOffset[(u32)&((StageWork *)0)->hudMessage == 0x338 ? 1 : -1];
typedef char StageWorkShadowActorsOffset[(u32)&((StageWork *)0)->shadowActors == 0x34c ? 1 : -1];
typedef char StageWorkGroupsOffset[(u32)&((StageWork *)0)->groups == 0x450 ? 1 : -1];

#endif
