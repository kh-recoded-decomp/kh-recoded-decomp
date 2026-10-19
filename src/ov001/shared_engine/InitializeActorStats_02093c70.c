#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ActorDefinition {
    u8 type;
    u8 variant;
    u8 level;
    u8 statClass : 4;
    u8 reservedClass : 4;
    s8 effect;
    s8 reserved05;
    s16 attackScale;
    u16 reserved08;
    u16 reserved0a;
} ActorDefinition;

typedef struct StatModifier {
    u8 reserved00[8];
    s32 value;
    u8 reserved0c[0x13];
    u8 levelScaled;
} StatModifier;

typedef struct BaseStats {
    s32 hp;
    s32 stats[8];
    u8 reserved24[0xc];
    s32 attack;
    u8 reserved34[0xe];
    u8 fixedHp;
    u8 reserved43;
} BaseStats;

typedef struct ActorStats {
    u8 level;
    u8 statClass;
    u8 reserved02[2];
    s32 maxHp;
    s32 hp;
    s32 stats[8];
    fx32 speed;
    s32 attack;
    StatModifier modifiers[8];
} ActorStats;

typedef struct ScaledOffsetPair {
    fx32 x;
    fx32 y;
} ScaledOffsetPair;

/* The actor fields used by resource initialization and stat calculation. */
typedef struct StatsActor {
    u8 reserved00[4];
    u16 reservedFlags4 : 3;
    u16 active : 1;
    u16 remainingFlags4 : 12;
    u16 reservedFlags6 : 8;
    u16 selectionEnabled : 1;
    u16 remainingFlags6 : 5;
    u16 variantEnabled : 1;
    u16 highFlags6 : 1;
    u8 reserved08[2];
    u8 variantArgument;
    u8 variantLevel;
    u16 reserved0c;
    u16 type;
    u16 state;
    u16 stageIndex;
    u16 stageLink;
    u8 reserved16[4];
    u16 recordIndex;
    u8 reserved1c[4];
    BaseStats base;
    ScaledOffsetPair offset;
    ActorStats stats;
} StatsActor;

typedef struct OverlaySelection {
    u8 set;
    u8 level;
} OverlaySelection;

extern void *GetStageManager(void);
extern const ActorDefinition *GetSmallTableEntry(int index);
extern BOOL func_ov001_02063a24(void);
extern int func_ov001_02063a38(void);
extern int func_ov032_020bb808(void);
extern u32 func_ov001_020925c8(StatsActor *actor, u16 level);
extern u8 GetContextIndexedByte(int index);
extern OverlaySelection *GetOverlaySelectionRecord(u32 index);
extern BOOL LoadResourceSetEntry(int index, BaseStats *base, StatModifier *modifiers);
extern void LoadScaledOffsetPair(ScaledOffsetPair *pair, int statClass);
extern void ComputeLevelStats(ActorStats *out, BaseStats *base, StatModifier *modifiers,
    u8 level, s16 attackScale, fx32 hpScale);
extern void ResetActorMotion(StatsActor *actor, BOOL keepSpeed);
extern u16 FindStageLinkIndex(int type);
extern void func_ov001_020925bc(StatsActor *actor, BOOL enable);

/* Select an actor definition, apply mode/type overrides, then initialize its
 * base and level-scaled stats, stage links and activation/selection flags. */
void InitializeActorStats_02093c70(StatsActor *actor, u16 type, u16 stageIndex,
    u16 recordIndex, BOOL active, BOOL selectionEnabled)
{
    ActorDefinition definition;
    StatModifier modifiers[8];
    const ActorDefinition *source;
    u16 resourceIndex;
    int mode;
    int statClass;

    GetStageManager();
    resourceIndex = type;
    source = NULL;
    if (recordIndex != 0xffff) {
        source = GetSmallTableEntry(recordIndex);
    }
    if (source != NULL) {
        definition = *source;
    } else {
        definition.type = type;
        definition.level = 1;
        definition.statClass = 1;
        definition.reservedClass = 1;
        definition.effect = -1;
        definition.reserved05 = -1;
        definition.attackScale = 0x1000;
        definition.variant = 0;
    }
    actor->variantArgument = 0;
    actor->variantEnabled = 0;
    mode = 0;
    if (func_ov001_02063a24()) {
        mode = func_ov001_02063a38();
    }
    if (mode == 10) {
        if (selectionEnabled && actor->type != 99) {
            actor->variantArgument = func_ov001_020925c8(actor, (u16)func_ov032_020bb808());
        }
        definition.level = GetContextIndexedByte(recordIndex);
    }
    if (type == 62) {
        int level = GetOverlaySelectionRecord(0)->level;
        if (level > 0) {
            definition.level = level;
        }
        definition.statClass = 10;
    } else if (type == 63) {
        int level = GetOverlaySelectionRecord(0)->level;
        if (level > 0) {
            definition.level = level;
        }
        definition.statClass = 1;
    } else if (type == 79) {
        definition.statClass = 8;
    } else if (type == 18 && definition.variant == 1) {
        resourceIndex = 100;
    }
    LoadResourceSetEntry(resourceIndex, &actor->base, modifiers);
    statClass = definition.statClass;
    LoadScaledOffsetPair(&actor->offset, statClass);
    ComputeLevelStats(&actor->stats, &actor->base, modifiers, definition.level,
        definition.attackScale, 0x1000);
    actor->stats.statClass = statClass;
    ResetActorMotion(actor, FALSE);
    actor->type = type;
    actor->stageIndex = stageIndex;
    actor->state = 0;
    actor->stageLink = FindStageLinkIndex(actor->type);
    actor->recordIndex = recordIndex;
    actor->active = (active != FALSE);
    actor->selectionEnabled = (selectionEnabled != FALSE);
    func_ov001_020925bc(actor, TRUE);
}
