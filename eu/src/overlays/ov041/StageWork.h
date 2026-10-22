#ifndef STAGE_WORK_H
#define STAGE_WORK_H

#include "nitro/types.h"
#include "src/overlays/ov041/StageOrbs.h"
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

typedef struct StageItemModel {
    u16 flags;
    u8 reserved02[0x1e];
    StageModelRenderObject renderObject;
    u16 yaw; /* used while flags has STAGE_MODEL_USE_YAW */
    u8 reserved07e[2];
    MtxFx33 rotation; /* with position: the 4x3 matrix it is drawn with */
    VecFx32 position;
    VecFx32 scale;
    u8 reserved0bc[0x1c];
    u8 blend[0x24];
    u16 colorScale;
    u8 reserved0fe[6];
    StageMotion motion; /* moves position (projectiles) */
    u8 reserved12c[0xc];
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

/* An action an entry can take (from its list, or an item's). */
/* StageEntryAction.flurry */
#define FLURRY_START_FRAME 0 /* animation frame the attacker sets off on */
#define FLURRY_RETURN_LENGTH 1 /* frames of the walk back */
#define FLURRY_ANIMATION 2 /* the first hit's animation; each hit plays the next one */
#define FLURRY_HIT_END 3 /* [3 + hit]: the frame each hit's animation ends on */
#define FLURRY_RECOVER_ANIMATION 9

/*
 * StageEntryAction.targetKind and StageWork.commandEffectKind: what the target cursor picks. Scene slots go in columns
 * of three (slot / 3 is the column, slot % 3 the row): column 0 holds the primary entries, columns 1-3 the secondary.
 */
#define STAGE_TARGET_ONE 0 /* one secondary entry, moved over every column */
#define STAGE_TARGET_COLUMN 1 /* every secondary entry in a column, moved a column at a time */
#define STAGE_TARGET_ALL 4 /* every secondary entry */
#define STAGE_TARGET_ONE_PRIMARY 7 /* one primary entry, moved up and down its column */
#define STAGE_TARGET_ALL_PRIMARY 8 /* every primary entry */
#define STAGE_TARGET_FIELD_MENU 10 /* no cursor move: L with the d-pad works the field menu */

typedef struct StageEntryAction {
    s16 soundSeqArc;
    u8 reserved02[2];
    s8 hitSoundIndex; /* sound played when it hits */
    s8 soundIndex;
    s16 soundFrame; /* animation frame the sound plays on */
    fx32 power; /* (word-sized: the action is copied by words) */
    u16 chance; /* out of 1000 */
    u16 critical;
    u16 accuracy;
    u8 reserved12[2];
    u8 minRepeats; /* barrages and combos: how many shots or hits they make, from minRepeats to maxRepeats */
    u8 maxRepeats;
    u8 targetKind; /* STAGE_TARGET_*: below 7 the action is aimed at the secondary entries */
    u8 range; /* how many rows away it reaches */
    u16 pressWindow; /* frames before the hit in which the timed press counts */
    u16 effectLength; /* frames of its effect item's animation before the hit lands */
    u8 kind;
    u8 element; /* 1-4 for an elemental action */
    u8 reserved1e[2];
    u8 animation;
    u8 reserved21;
    u8 hitEffectCategory; /* the item shown on a target it hits */
    u8 hitEffectIndex;
    u8 hitEffectAnimation;
    u8 altEffectCategory;
    u8 altEffectIndex;
    u8 altEffectAnimation;
    union {
        struct {
            union {
                u8 castFrame; /* animation frame its effect takes hold on */
                u8 variant; /* path attacks: which of their three runs (0-2) */
            };
            union {
                u8 effectFrame; /* animation frame its effect item appears on */
                u8 recoverAnimation; /* path attacks: played on the way back */
            };
            union {
                u8 returnFrame; /* melee: animation frame the walk back starts on */
                u8 shotInterval; /* barrages: frames between two shots */
            };
            union {
                u8 effectCategory;
                u8 returnEndFrame; /* melee: and ends on */
            };
            union {
                u8 effectIndex;
                u8 windupAnimation; /* dashes: played before and after the run */
            };
            u8 effectAnimation;
            union {
                struct {
                    u8 healEffectCategory; /* heals: the item shown over the healed entry */
                    u8 healEffectIndex;
                    u8 healEffectAnimation;
                };
                struct {
                    u8 reserved2e;
                    u8 attackStyle; /* kind 1: 3 plays the hit sound even on a miss; kind 0x10 attackers: 0 aims high */
                    u8 extraReach; /* kinds 1 and 6: tenths of a unit the attacker stops further away */
                };
                struct {
                    u8 aimEffectCategory; /* barrages: the item shown over the attacker as it starts shooting */
                    u8 aimEffectIndex;
                    u8 aimEffectAnimation;
                };
            };
            u8 shotCategory; /* barrages: the item each shot flies as */
            u8 shotIndex;
            u8 shotAnimation;
            u8 statusTurns;
            u8 itemSlot;
            u8 effect;
            u8 effectArg;
        };
        struct {
            u8 reserved28[4];
            u8 rushEffectCategory; /* melee rushes: the item that rushes in with the attacker */
            u8 rushEffectIndex;
            u8 rushEffectAnimation;
        };
        struct {
            u8 comboAnimations[4]; /* combos: the animation of each of the four attacks (3 is the finisher) */
            u8 comboEndFrames[4]; /* and the frame each one ends on */
            u8 comboRecoverFrame; /* where the walk back joins the first animation */
            u8 comboStyle; /* 0-2: how far each attack carries the attacker */
        };
        struct {
            u8 flurry[10]; /* flurries: FLURRY_* timings and animations */
            u8 flurryPressFrames[6]; /* the hit frames the timed press is checked against */
        };
    };
} StageEntryAction;

/* StageWork.flags */
#define STAGE_WORK_NO_TIMED_INPUT 4
#define STAGE_WORK_SKIP_CHANCE_A 8
#define STAGE_WORK_SKIP_CHANCE_B 0x10
#define STAGE_WORK_FIELD_OP_DONE 0x4000
#define STAGE_WORK_PANEL_MOVING 0x4000000
#define STAGE_WORK_RUNNING_COMMANDS 0x8000000 /* the chosen menu commands are being carried out */
#define STAGE_WORK_TURN_STARTED 0x10000000
#define STAGE_WORK_FAST_PANELS 0x20000000
#define STAGE_WORK_CAPTION_DOWN 0x40000000
#define STAGE_WORK_STOP_COMMANDS 0x80000000 /* go back to the menu after the current command */

typedef struct StageEntry StageEntry;

typedef void (*StageStateFunc)(void);

/* The stage (gMovieContextState->stageWork): state machine, entries, models, markers and resource lists. */
/* A command taken from the field's command queue: an item id and its level. */
typedef struct StageFieldCommand {
    int id;
    int arg;
} StageFieldCommand;

/* The actions of the items, as loaded for the stage. */
typedef struct StageItemActionTable {
    u32 count;
    StageEntryAction actions[1];
} StageItemActionTable;

typedef struct StageWork {
    u32 frameCounter;
    u16 turn; /* turns played */
    u8 state;
    s8 stateStep;
    u32 flags;
    u8 stateTimer;
    u8 targetSlot; /* scene slot of the entry the target cursor is on */
    u8 targetRow; /* top or bottom row the cursor last changed column from; a change from the middle row starts there */
    u8 introStep;
    u8 introValue;
    u8 introKind;
    u8 reserved012[2];
    StageEntry *entries;
    u8 entryCount;
    u8 primaryCount; /* entries [0, primaryCount) are the primary ones, the secondary ones follow */
    u8 secondaryCount;
    u8 currentEntry; /* the entry whose turn it is */
    u8 reserved01c[4];
    void *subModeTask;
    u8 commandId;
    u8 fieldSlot;
    u8 targetIndex;
    u8 commandEffectKind; /* STAGE_TARGET_* of the chosen command */
    u8 reserved028[4];
    StageEntryAction itemActions[3]; /* what each primary entry does with the chosen item */
    StageMarker *commandMarkers[9];
    StageModelActor primaryActor;
    u8 reserved20c[0xc4];
    MtxFx43 primaryMatrix;
    u8 reserved300[0xc];
    int hitSeqArc; /* the sound archive of the hit sounds */
    u8 reserved310[4];
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
    u8 reserved4bc[0x53c - 0x4bc];
    StageOrbPool orbPool;
    u8 reserved2310[4];
    StageItemActionTable *itemActionTable;
    int menuDepth; /* submenus opened in the command menu */
    int menuStack[3]; /* the entry chosen at each depth, -1 above menuDepth */
    fx32 frameStep; /* how far animations and moves advance per frame */
} StageWork;

typedef char StageWorkOrbPoolOffset[(u32)&((StageWork *)0)->orbPool == 0x53c ? 1 : -1];
typedef char StageWorkItemTableOffset[(u32)&((StageWork *)0)->itemActionTable == 0x2314 ? 1 : -1];

typedef struct StageContext {
    u8 reserved000[6];
    u16 flags;
    u8 reserved008[0x1c - 8];
    s8 pendingChoice;
    u8 sceneReady;
    u8 reserved01e[3];
    u8 endKind; /* how the stage ended: 1, 2 or 3 */
    u8 reserved022[4];
    s16 unk26;
    s16 unk28;
    u8 reserved02a[8];
    s16 cooldown;
    s16 effectTimer;
    u8 reserved036[0xb8 - 0x36];
    StageWork *stageWork;
} StageContext;

extern StageContext *gMovieContextState;

typedef char StageResourceListSize[sizeof(StageResourceList) == 8 ? 1 : -1];
typedef char StageItemModelSize[sizeof(StageItemModel) == 0x138 ? 1 : -1];
typedef char StageResourceItemSize[sizeof(StageResourceItem) == 0x13c ? 1 : -1];
typedef char StageMarkerSize[sizeof(StageMarker) == 0x34 ? 1 : -1];
typedef char StageMarkerListsOffset[(u32)&((StageWork *)0)->markerLists == 0x314 ? 1 : -1];
typedef char StageResourceListsOffset[(u32)&((StageWork *)0)->lists == 0x358 ? 1 : -1];

typedef char StageEntryActionSize[sizeof(StageEntryAction) == 0x38 ? 1 : -1];
typedef char StageWorkCommandMarkersOffset[(u32)&((StageWork *)0)->commandMarkers == 0xd4 ? 1 : -1];
typedef char StageWorkPrimaryActorOffset[(u32)&((StageWork *)0)->primaryActor == 0xf8 ? 1 : -1];
typedef char StageWorkPrimaryMatrixOffset[(u32)&((StageWork *)0)->primaryMatrix == 0x2d0 ? 1 : -1];
typedef char StageWorkHudMessageOffset[(u32)&((StageWork *)0)->hudMessage == 0x338 ? 1 : -1];
typedef char StageWorkShadowActorsOffset[(u32)&((StageWork *)0)->shadowActors == 0x34c ? 1 : -1];
typedef char StageWorkGroupsOffset[(u32)&((StageWork *)0)->groups == 0x450 ? 1 : -1];

#endif
