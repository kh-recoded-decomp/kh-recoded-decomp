#ifndef STAGE_ENTRY_RENDER_H
#define STAGE_ENTRY_RENDER_H

#include "src/overlays/ov041/StageModelRender.h"
#include "src/overlays/ov041/StageResources.h"

typedef struct StageEntryNode {
    u16 flags;
    u8 reserved02[0x22];
    void *modelResource;
    u8 reserved028[0x54];
    u16 yaw; /* used while flags has STAGE_MODEL_USE_YAW */
    u8 reserved07e[2];
    MtxFx33 rotation;
    VecFx32 position;
    u8 reserved0b0[0x28];
    u8 jointAnimation[0x24]; /* the animation its joints play */
    u8 reserved0fc[0x98];
} StageEntryNode;

/* StageEntrySlot.flags */
#define STAGE_SLOT_FACING_LOCKED 0x20

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
    u8 reservedbc[0x48];
} StageGroundShadow;


/* StageEntry.state */
#define STAGE_ENTRY_WAITING 1
#define STAGE_ENTRY_ACTIVE 2

/* StageEntry.abilities: the first five only work at a quarter of the hp or less */
#define STAGE_ABILITY_LOW_HP_MASK 0x1f
#define STAGE_ABILITY_LEADER 0x20 /* checked on the first entry, for every non-enemy */
#define STAGE_ABILITY_PLAYER 0x40

/* StageEntry.state of an entry that is out */
#define STAGE_ENTRY_OUT 6

/* StageEntry.flags */
#define STAGE_ENTRY_ENEMY 1
#define STAGE_ENTRY_SHOW_HP 8
#define STAGE_ENTRY_HURT 0x10 /* it was hit */
#define STAGE_ENTRY_DODGED 0x20 /* it dodged a hit */
#define STAGE_ENTRY_TIMED_PRESS 0x40 /* the button was pressed in time during its action */
#define STAGE_ENTRY_PRESSED_ATTACK 0x80 /* A pressed in time as the attacker */
#define STAGE_ENTRY_COMBO_FINISHED 0x100 /* landed the last hit of a combo with the press panel lit */
#define STAGE_ENTRY_PRESSED_GUARD 0x600 /* Y pressed in time as the defender (status 9 counts as one) */
#define STAGE_ENTRY_GUARDED 0x200 /* the hit was guarded */
#define STAGE_ENTRY_GUARDING 0x400
#define STAGE_ENTRY_TURNED 0x2000 /* turned to face across while the menu is held */
#define STAGE_ENTRY_PRESS_PANEL 0x10000 /* keep showing the lit press panel */
#define STAGE_ENTRY_MISSED 0x100000 /* its last action missed */
#define STAGE_ENTRY_FLAG_800 0x800
#define STAGE_ENTRY_STEP_BACK 0x4000
#define STAGE_ENTRY_FROZEN 0x8000
#define STAGE_ENTRY_STRUCK 0x20000 /* already hit by the dash going through it */
#define STAGE_ENTRY_NOT_TALLIED 0x80000
#define STAGE_ENTRY_FORCE_ACTION_2 0x200000
#define STAGE_ENTRY_VOICE_TOGGLE 0x400000 /* which of its two hurt voices plays next */
#define STAGE_ENTRY_ALT_VOICES 0x800000

#define STAGE_ENTRY_STATUS_COUNT 11
#define STAGE_ENTRY_STATUS_2 2 /* set by a self action */
#define STAGE_ENTRY_STATUS_3 3 /* cleared by a revive */
#define STAGE_ENTRY_STATUS_9 9 /* blocks the defending press */
#define STAGE_ENTRY_STATUS_10 10 /* widens the timed press window */

/* A model played through an animation that also moves along path nodes (as GetPathNodeOffset reads them). */
typedef struct StagePathModel {
    u8 reserved000[0x20];
    u32 renderFlags;
    u8 reserved024[0x104 - 0x24];
    void *nodes;
    int nodeIndex;
    int animation; /* -1 when none is set */
    fx32 frame;
    int state;
    VecFx32 position;
    VecFx32 direction; /* where the path heads */
    fx32 scale; /* of the horizontal movement */
    u16 angle; /* facing along direction: its cosine */
    u16 turn; /* and its sine */
} StagePathModel;

/* An item to spawn: SpawnStageItem's category, index and animation. */
typedef struct StageItemSpec {
    u16 category;
    u8 index;
    u8 animation;
} StageItemSpec;

/* StageEntryHit.heal */
#define STAGE_HEAL_NONE 0
#define STAGE_HEAL_REVIVE 1 /* heals, and brings back an entry that is out */
#define STAGE_HEAL_HP 2

/* What an entry's hit does (filled by func_ov041_020c4d58). */
typedef struct StageEntryHit {
    fx32 amount; /* hp it takes (or gives), at most 9999 */
    int accuracy;
    u16 critical;
    s16 minDamage; /* hp the hit takes at the least */
    u8 element; /* 1-4 for an elemental action */
    u8 heal; /* STAGE_HEAL_*: whether it heals instead */
    StageItemSpec effect; /* shown on the target */
    StageItemSpec altEffect; /* shown instead when a player entry's hit sets result bit 2 */
    u8 reserved16[2];
    struct StageEntry *source;
} StageEntryHit;

/* StageEntryMove.phase: out to a destination, a pause there, then back to its grid place */
#define STAGE_MOVE_IDLE 0
#define STAGE_MOVE_OUT 1
#define STAGE_MOVE_PAUSE 2
#define STAGE_MOVE_BACK 3

typedef struct StageEntryMove {
    StageMotion motion;
    fx32 duration;
    fx32 pause; /* frames to wait at the destination */
    u8 phase; /* STAGE_MOVE_* */
    u8 reserved31[3];
} StageEntryMove;

typedef void (*StageEntryFunc)(u8 entryIndex);

/* The hp fractions (0.8, 0.6, 0.4, 0.2) whose crossing sets STAGE_ENTRY_FORCE_ACTION_2. */
typedef struct StageHpThresholds {
    fx32 values[4];
} StageHpThresholds;

/* Entry indices (or columns) a target is picked from at random (-1 = none). */
/* A sound: its archive and its index there. */
typedef struct StageSoundRef {
    int seqArc;
    int index;
} StageSoundRef;

/* What a player entry calls out as it attacks: by 0xff - kind, then a random pick. */
extern const StageSoundRef gAttackVoices[3][3];

/* Two sounds of which one is picked at random. */
typedef struct StageSoundChoices {
    int indices[2];
} StageSoundChoices;

typedef struct StageTargetCandidates {
    int indices[9];
} StageTargetCandidates;

typedef struct StageColumnCandidates {
    int columns[3];
} StageColumnCandidates;

/* Indices of the actions an entry can pick from (-1 = none). */
typedef struct StageActionChoices {
    s8 indices[4];
} StageActionChoices;

struct StageEntry {
    u8 kind;
    u8 index; /* its own place in StageWork.entries */
    s8 row;
    s8 column;
    u8 state;
    u8 previousState;
    u8 stateStep; /* progress inside the current state */
    u8 reserved007;
    u32 flags;
    int waitFrames;
    s8 actionIndex; /* the action being carried out, or -1 */
    u8 mainTarget; /* the entry its action is aimed at (itself when idle) */
    u8 targetCount;
    u8 targets[9]; /* indices of the entries the action is aimed at */
    StageOrbBurst orbBursts[3]; /* the orbs of its defeat (the stage waits for them before it ends) */
    s16 hp;
    s16 maxHp;
    s16 shownHp; /* follows hp down a little at a time */
    s16 checkedHp; /* hp when the hp thresholds were last checked */
    u16 strength;
    u16 defense; /* a hit's power over it is weighed against this */
    u8 reserved0e8[4];
    u16 hitRate; /* percent of an action's accuracy that lands on it */
    u8 reserved0ee[2];
    fx32 minDamage; /* copied to its hits */
    BOOL countsForProgress; /* passed to TallyStageCharacter when the stage ends */
    u8 reserved0f8[4];
    u8 orbsMin; /* the hp its orbs give back on defeat: a random amount in [orbsMin, orbsMax] */
    u8 orbsMax;
    u8 reserved0fe[2];
    u8 elementRates[4]; /* percent of an elemental hit's damage it takes, by element 1-4 */
    u8 reserved104[4];
    s8 actionCount;
    u8 reserved109[3];
    StageEntryAction *actions;
    s8 statuses[STAGE_ENTRY_STATUS_COUNT];
    u8 shownStatusIcon; /* the status icon on show (they take turns every 30 frames), 8 = none */
    int delay;
    int animationFrame;
    u8 animation;
    u8 sceneSlot;
    u8 reserved126[2];
    fx32 radius;
    fx32 groundHeight; /* how high it stands on its grid place */
    VecFx32 overheadOffset; /* from its position to where things are shown above it */
    u8 idleAnimation;
    u8 hurtAnimation;
    u8 downAnimation; /* played by a player entry that goes out */
    u8 stepAnimation;
    u8 guardAnimation;
    u8 hurtVoices[2]; /* played in turn when it is hurt */
    u8 altHurtVoices[2]; /* the same for entries with STAGE_ENTRY_ALT_VOICES (enemies use them when they go out) */
    u8 downVoice; /* played when it goes out */
    u8 reserved146[0x16];
    StageEntrySlot slot;
    u8 reserved310[0x10];
    s16 frameStep;
    u8 reserved322[0xa];
    u8 actorSlot;
    u8 reserved32d[3];
    StageResourceContainer *resources; /* of its model */
    StageFollowerActor *attachment;
    u8 reserved338[4];
    StageEntryHit hit;
    StageEntryMove move;
    StageResourceItem *effects[5]; /* effect items following it */
    StageResourceItem *statusItem;
    StagePathModel *pathModel;
    StageGroundShadow shadow;
    int voiceSeqArc; /* the sound archive of its voices */
    u16 magic;
    u8 abilities; /* STAGE_ABILITY_* bits */
    u8 reserved4b3;
};

typedef struct StageRenderCapture {
    union {
        u8 unk00;
        u8 flurryRound; /* flurries: counts the rounds of three hits */
    };
    u8 comboStage; /* combos: which of the four attacks comes next (3 is the finisher, 0 ends it) */
    union {
        u8 comboCount; /* extra melee hits made in a row */
        u8 shotsFired; /* barrages */
        u8 comboHit; /* combos: the hit being made, from 1 */
        u8 flurryHit; /* flurries: hits made so far */
    };
    u8 reserved03;
    union {
        int teamLeader; /* the entry whose sounds a team attack plays */
        int shotCount; /* barrages: one less than the shots they fire */
        int comboLength; /* combos: one less than the hits they make */
    };
    union {
        int reviveWait; /* frames waited after a revive */
        int shotTimer; /* barrages: counts down; a shot goes off whenever it is a multiple of the interval */
    };
    fx32 flurryHitEnd; /* flurries: the frame the current hit's animation ends on */
    StageEntry *entry;
    fx32 castTimer; /* frames since a spell was cast, while its caster is not frozen */
    VecFx32 panelOffset; /* from a defender to its timed press panel */
} StageRenderCapture;

extern StageRenderCapture data_ov041_020cff48;
extern const fx32 gStageShadowHeights[4];
extern void GetPositionAboveGround(VecFx32 *position, StageEntry *entry);
extern void ShadowVolume_Draw(const VecFx32 *position);
extern void SceneNode_Draw(void *node);

void DrawStageEntryModels(StageEntrySlot *slot, BOOL drawShadow);
void UpdateStageEntryAnimation(StageEntrySlot *slot);

typedef char StageEntrySize[sizeof(StageEntry) == 0x4b4 ? 1 : -1];
typedef char StageEntryActionsOffset[(u32)&((StageEntry *)0)->actions == 0x10c ? 1 : -1];
typedef char StageEntryMoveOffset[(u32)&((StageEntry *)0)->move == 0x358 ? 1 : -1];
typedef char StageEntryMoveSize[sizeof(StageEntryMove) == 0x34 ? 1 : -1];
typedef char StageEntryHpOffset[(u32)&((StageEntry *)0)->hp == 0xdc ? 1 : -1];
typedef char StageEntryRadiusOffset[(u32)&((StageEntry *)0)->radius == 0x128 ? 1 : -1];
typedef char StageEntryAbilitiesOffset[(u32)&((StageEntry *)0)->abilities == 0x4b2 ? 1 : -1];
typedef char StageEntryStatusesOffset[(u32)&((StageEntry *)0)->statuses == 0x110 ? 1 : -1];
typedef char StageEntryStatusItemOffset[(u32)&((StageEntry *)0)->statusItem == 0x3a0 ? 1 : -1];
typedef char StageEntryPositionOffset[(u32)&((StageEntry *)0)->slot.node.position == 0x214 ? 1 : -1];

#endif
