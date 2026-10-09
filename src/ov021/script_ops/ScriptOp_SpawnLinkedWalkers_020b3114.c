#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct {
    u32 count;
    u32 stride;
    u8 *entries;
} LinkTable;

typedef struct {
    u8 pad_00[0x54];
    LinkTable spawns;
} LinkInfo;

typedef struct {
    u8 pad_00[8];
    LinkInfo *info;
} LinkData;

typedef struct {
    u16 id;
    u8 pad_02[2];
    LinkData *data;
} StageLink;

typedef struct {
    u16 eventId;
} LinkSpawn;

typedef struct {
    u8 pad_00[0xe];
    u16 linkId;
    u8 pad_10[2];
    u16 objectId;
} StageEventRecord;

typedef struct {
    u8 pad_00[0xe];
    u16 eventId;
    u16 actorId;
} SpawnEvent;

typedef struct {
    u8 pad_00[0x1d0];
    u16 spawnMode;
    u16 firstEvent;
    u8 pad_1d4[0xaa];
    u16 objectId;
} StageActor;

typedef struct {
    u8 pad_000[0x270];
    u16 spawnArg;
} WalkerActor;

typedef struct {
    u32 flags;
    VecFx32 offset;
    fx32 spread;
    u32 pad_10;
    s32 angle;
    u32 pad_18;
} SpawnPoint;

typedef struct {
    u8 pad_00000[0x18e78];
    SpawnPoint points[2];
} SpawnLayout;

typedef struct {
    StageEventRecord *record;
    void *eventRef;
    StageActor *actor;
} FieldContext;

typedef struct {
    s16 tag;
    s16 pad_02;
    s32 value;
} TaggedValue;

typedef struct {
    TaggedValue first;
    TaggedValue last;
    TaggedValue spawnArg;
    TaggedValue speed;
} ScriptCommand;

extern FieldContext data_ov021_020b56a4;
extern const VecFx32 data_02053438;
extern const s16 data_0205356c[];

extern TaggedValue *ResolveTaggedValueRef_020b0374(void *obj, TaggedValue *value);
extern SpawnLayout *func_ov001_0209c3c0(void);
extern void *GetStageObjectHandle_0209c0c4(u32 id);
extern void *GetStageObjectRecord_0209c0a0(u32 id);
extern StageLink *FindStageLink_02099584(u32 id);
extern s32 func_02023dbc(s32 numerator, s32 denominator);
extern SpawnEvent *GetStageEventRecord_0209c0ec(u32 id);
extern void ResetActorMotion_02093e28(SpawnEvent *actor, BOOL keepSpeed);
extern void SpawnStageGroup_02094f60(SpawnEvent *spawner, int unused1, int unused2, int arg);
extern WalkerActor *GetStageActor_0209c040(int id);
extern void func_ov021_020b0450(s32 value, fx32 spread, VecFx32 *dir);
extern void RandomScaledDirection_020b0488(fx32 scale, VecFx32 *dir);
extern void MTX_Identity33_01ff90ec(MtxFx33 *mtx);
extern void MTX_RotY33_01ff923c(MtxFx33 *mtx, fx32 sinVal, fx32 cosVal);
extern void MTX_MultVec33_01ff9404(const VecFx32 *vec, const MtxFx33 *m, VecFx32 *dst);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern u16 FixedPointAtan2_020062bc(fx32 y, fx32 x);
extern s64 Mul64_02023d9c(s64 a, s64 b);
extern void SetActorFacingDegrees_02090f3c(WalkerActor *actor, int degrees);
extern void WarpWalkerTo_02090f0c(WalkerActor *walker, const VecFx32 *position);
extern fx32 TaggedValueToFixed_020b03b0(TaggedValue *tagged);
extern void BeginWalkerMove_020910c4(WalkerActor *walker, const VecFx32 *target, int frames, int extra);
extern void UpdateActorMovement_020902e0(WalkerActor *actor);

static inline u32 GetSpawnCount(StageLink *link)
{
    if (link == NULL) {
        return 0;
    }
    if (link->data == NULL) {
        return 0;
    }
    return link->data->info->spawns.count;
}

static inline LinkSpawn *GetLinkSpawn(StageLink *link, u16 index)
{
    LinkInfo *info;
    u8 *entries;
    u32 count;

    if (link == NULL) {
        return NULL;
    }
    if (link->data == NULL) {
        return NULL;
    }
    count = GetSpawnCount(link);
    info = link->data->info;
    entries = info->spawns.entries;
    if (count == 0) {
        return NULL;
    }
    if (index >= count) {
        return NULL;
    }
    return (LinkSpawn *)(entries + index * info->spawns.stride);
}

static inline void InitSpawnDirection(SpawnLayout *layout, int index, s32 seed, VecFx32 *dir)
{
    if (layout->points[index].flags & 0x40) {
        func_ov021_020b0450(seed, layout->points[index].spread, dir);
    } else if (layout->points[index].flags & 0x80) {
        RandomScaledDirection_020b0488(layout->points[index].spread, dir);
    }
}

s32 ScriptOp_SpawnLinkedWalkers_020b3114(void *obj, ScriptCommand *cmd)
{
    VecFx32 dir;
    VecFx32 targets[2];
    MtxFx33 rotation;
    VecFx32 zero;
    TaggedValue *firstValue = ResolveTaggedValueRef_020b0374(obj, &cmd->first);
    TaggedValue *lastValue = ResolveTaggedValueRef_020b0374(obj, &cmd->last);
    TaggedValue *argValue = ResolveTaggedValueRef_020b0374(obj, &cmd->spawnArg);
    TaggedValue *speedValue = ResolveTaggedValueRef_020b0374(obj, &cmd->speed);
    SpawnLayout *layout = func_ov001_0209c3c0();
    StageEventRecord *record = data_ov021_020b56a4.record;
    StageActor *actor = data_ov021_020b56a4.actor;
    StageLink *link;
    SpawnEvent *event;
    LinkSpawn *spawn;
    WalkerActor *walker;
    s32 first;
    s32 last;
    u16 spawnIndex;
    s32 step;
    u16 index;
    u16 i;
    s32 angle;

    GetStageObjectHandle_0209c0c4(record->objectId);
    GetStageObjectRecord_0209c0a0(actor->objectId);
    if (actor->spawnMode != 1) {
        return 0;
    }
    if (actor->firstEvent == 0) {
        return 0;
    }
    link = FindStageLink_02099584(record->linkId);
    if (link == NULL) {
        return 0;
    }
    if ((u16)GetSpawnCount(link) == 0) {
        return 0;
    }
    first = firstValue->value;
    if (first == 0) {
        return 0;
    }
    last = lastValue->value;
    if (last == 0) {
        return 0;
    }
    spawnIndex = 0;
    step = func_02023dbc(0xffff, (u16)(last - first + 1));
    index = first;
    if (index <= last) {
        do {
            zero = data_02053438;
            event = GetStageEventRecord_0209c0ec((u16)(actor->firstEvent + index));
            spawn = GetLinkSpawn(link, index - 1);
            if (spawn == NULL) {
                return 0;
            }
            if (event == NULL) {
                return 0;
            }
            if (event->actorId != 0) {
                return 0;
            }
            if (event->eventId != spawn->eventId) {
                return 0;
            }
            i = 0;
            ResetActorMotion_02093e28(event, FALSE);
            SpawnStageGroup_02094f60(event, 0, 0x1000, 0);
            walker = GetStageActor_0209c040((s16)event->actorId);
            if (walker != NULL) {
                do {
                    dir = zero;
                    InitSpawnDirection(layout, i, step * spawnIndex, &dir);
                    MTX_Identity33_01ff90ec(&rotation);
                    angle = layout->points[i].angle >> 4;
                    MTX_RotY33_01ff923c(&rotation, data_0205356c[angle], data_0205356c[((FX32_ONE >> 2) - angle) & 0xfff]);
                    MTX_MultVec33_01ff9404(&dir, &rotation, &dir);
                    VEC_Add_01ff9e0c(&layout->points[i].offset, &dir, &targets[i]);
                    SetActorFacingDegrees_02090f3c(walker, (Mul64_02023d9c(FixedPointAtan2_020062bc(dir.x, dir.z), 0x1680000) + 0x80000) >> 20);
                    i++;
                } while (i < 2);
                WarpWalkerTo_02090f0c(walker, &targets[0]);
                BeginWalkerMove_020910c4(walker, &targets[1], TaggedValueToFixed_020b03b0(speedValue), 0);
                walker->spawnArg = argValue->value;
                UpdateActorMovement_020902e0(walker);
                spawnIndex++;
            }
            index++;
        } while (index <= lastValue->value);
    }
    return 0;
}
