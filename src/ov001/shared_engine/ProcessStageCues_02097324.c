#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct FileSection {
    u32 unk_00;
    u32 count;
    u32 stride;
    u8 *data;
} FileSection;

typedef struct StageFile {
    u8 pad_00[8];
    FileSection *sections;
} StageFile;

typedef struct StageEntry {
    u16 id;
    u8 pad_02[2];
    StageFile *file;
} StageEntry;

typedef struct Matrix43 {
    fx32 m[12];
} Matrix43;

typedef struct CueVariant {
    u8 pad_00[0x1c];
    u16 cueBase;
} CueVariant;

typedef struct CueGroup {
    u32 first;
    u32 count;
} CueGroup;

typedef struct CueShape {
    u8 pad_00[4];
    int nodeName;
    u8 pad_08[0xc];
    s32 type;
    fx32 radius;
    fx32 length;
    u8 pad_20[0x20];
    u16 once;
} CueShape;

typedef struct SweptShape {
    u8 data[0x44];
} SweptShape;

typedef struct CueBody {
    SweptShape shape;
    u8 storage[0x2c];
    VecFx32 position;
    VecFx32 velocity;
    VecFx32 hitPoint;
    fx32 stepScale;
} CueBody;

typedef struct CueOwner {
    u8 pad_00[0xe];
    u16 kind;
    u8 pad_10[4];
    s16 entryId;
    u8 pad_16[0xa0 - 0x16];
    u8 sources[1][0x20];
} CueOwner;

typedef struct CueActor {
    u8 pad_000[0x1d0];
    u8 sequencer[0x26c - 0x1d0];
    u32 behaviorFlags : 31;
    u32 unk_26c_31 : 1;
    u8 pad_270[0x28a - 0x270];
    u16 unk_28a_0 : 10;
    u16 launchState : 4;
    u16 unk_28a_14 : 2;
    u16 variant : 3;
    u16 cueRow : 4;
    u16 cueColumn : 4;
    u16 unk_28c_11 : 5;
    u8 pad_28e[0x2c0 - 0x28e];
    VecFx32 position;
    u8 pad_2cc[0x31c - 0x2cc];
    fx32 scale;
    u8 pad_320[0x380 - 0x320];
    VecFx32 delta;
} CueActor;

typedef struct CueContext {
    CueOwner *owner;
    CueActor *actor;
    StageEntry *entry;
    CueGroup *group;
    CueShape *cue;
    u8 *source;
    u16 count;
    CueBody body;
} CueContext;

typedef struct CueResult {
    u32 flags;
    VecFx32 origin;
    VecFx32 velocity;
    u8 useFirst;
    u8 silent;
    u8 enabled;
} CueResult;

extern void func_01ff8830(void *dst, s32 value, u32 size);
extern StageEntry *GetStageEntry_0209c074(int id);
extern int func_ov001_0208f018(StageFile *file, int index);
extern u16 FindActorResourceIndexByName_02091248(CueActor *actor, const char *name);
extern void GetNodeMatrix_020915ac(CueActor *actor, u32 nodeId, Matrix43 *out);
extern fx32 FixedPointMultiply12(fx32 a, fx32 b);
extern void BuildSweptShape_0209d610(SweptShape *out, void *storage, int kind, const VecFx32 *position, const VecFx32 *delta, const VecFx32 *axis, fx32 radius, fx32 length);
extern u8 *func_ov001_0209c3c0(void);
extern BOOL RaycastMoveStep_02093080(CueBody *body, CueActor *owner);
extern void func_ov001_02096bc8(CueOwner *owner, CueActor *actor, u32 column, u32 row, CueContext *ctx, CueResult *result);
extern void func_ov001_02096f38(CueOwner *owner, CueActor *actor, u32 column, u32 row, CueContext *ctx, CueResult *result);
extern void func_ov001_02097130(CueOwner *owner, CueActor *actor, u32 column, u32 row, CueContext *ctx, CueResult *result);
extern void RunOverrideTrack_020b4b9c(void *sequencer, u16 overrideId);
extern void SpawnLaunchedActor_020929f4(CueOwner *owner, CueActor *actor, CueShape *desc, u8 *source, const VecFx32 *velocity, const VecFx32 *origin, BOOL useFirst, BOOL silent);

static inline u32 GetEntrySectionCount(StageEntry *entry, int type)
{
    if (entry == NULL) {
        return 0;
    }
    if (entry->file == NULL) {
        return 0;
    }
    if (type < 0) {
        return 0;
    }
    if (type >= 0x13) {
        return 0;
    }
    return entry->file->sections[type].count;
}

static inline u8 *GetEntrySectionItem(StageEntry *entry, int type, u32 index)
{
    u32 count;
    FileSection *sections;
    u8 *data;

    if (entry == NULL) {
        return NULL;
    }
    if (entry->file == NULL) {
        return NULL;
    }
    if (type < 0) {
        return NULL;
    }
    if (type >= 0x13) {
        return NULL;
    }
    count = GetEntrySectionCount(entry, type);
    sections = entry->file->sections;
    data = sections[type].data;
    if (count == 0) {
        return NULL;
    }
    if (index >= count) {
        return NULL;
    }
    return data + index * sections[type].stride;
}

static inline u8 *GetVariantItem(StageEntry *entry, int type, u32 index)
{
    u32 count;
    FileSection *sections;
    u8 *data;
    u8 *item;

    item = NULL;
    if (entry != NULL && entry->file != NULL && type >= 0 && type < 0x13) {
        count = GetEntrySectionCount(entry, type);
        sections = entry->file->sections;
        data = sections[type].data;
        if (count == 0) {
            item = NULL;
        } else if (index >= count) {
            item = NULL;
        } else {
            item = data + index * sections[type].stride;
        }
    }
    return item;
}

static inline u16 GetActorVariant(CueActor *actor)
{
    return actor->variant;
}

static inline u16 GetCueSlot(CueGroup *group, int i)
{
    return group->first + (u16)i;
}

static inline void AimAlongNode(VecFx32 *axis, const Matrix43 *mtx, fx32 length)
{
    if (length > 0) {
        axis->x = mtx->m[3];
        axis->y = mtx->m[4];
        axis->z = mtx->m[5];
    } else {
        axis->x = -mtx->m[3];
        axis->y = -mtx->m[4];
        axis->z = -mtx->m[5];
    }
}

static inline CueBody *BuildCueBody(CueBody *body, CueShape *cue, Matrix43 *mtx, fx32 scale, const VecFx32 *delta)
{
    void *storage;
    int kind;
    fx32 radius;
    fx32 length;

    kind = -1;
    storage = NULL;

    if (cue == NULL) {
        return NULL;
    }
    body->position = *(VecFx32 *)&mtx->m[9];
    switch (cue->type) {
    case 0:
        body->velocity.x = 0;
        body->velocity.y = 0x1000;
        body->velocity.z = 0;
        length = cue->radius;
        radius = length;
        kind = 0;
        storage = body->storage;
        break;
    case 1:
        AimAlongNode(&body->velocity, mtx, cue->length);
        length = cue->length;
        if (length < 0) {
            length = -length;
        }
        radius = cue->radius;
        kind = 3;
        storage = body->storage;
        break;
    case 2:
        AimAlongNode(&body->velocity, mtx, cue->length);
        length = cue->length;
        if (length < 0) {
            length = -length;
        }
        radius = cue->radius;
        storage = body->storage;
        kind = 4;
        break;
    }
    length = FixedPointMultiply12(length, scale);
    radius = FixedPointMultiply12(radius, scale);
    BuildSweptShape_0209d610(&body->shape, storage, kind, (VecFx32 *)&mtx->m[9], delta, &body->velocity, radius, length);
    body->stepScale = length;
    return body;
}

static inline void ApplyCueResult(CueOwner *owner, CueActor *actor, CueContext *ctx, CueResult *result)
{
    if (result->flags & 4) {
        RunOverrideTrack_020b4b9c(actor->sequencer, 7);
        actor->launchState = 8;
    } else if (result->flags & 2) {
        if (result->enabled) {
            SpawnLaunchedActor_020929f4(owner, actor, ctx->cue, ctx->source, &result->velocity, &result->origin, result->useFirst, result->silent);
        }
    } else if (result->flags & 8) {
        SpawnLaunchedActor_020929f4(owner, actor, ctx->cue, ctx->source, &result->velocity, &result->origin, result->useFirst, 0);
    } else if (result->flags & 1) {
        RunOverrideTrack_020b4b9c(actor->sequencer, 8);
        SpawnLaunchedActor_020929f4(owner, actor, ctx->cue, ctx->source, &result->velocity, &result->origin, result->useFirst, result->silent);
    }
    if (result->flags != 0 && ctx->cue->once != 0) {
        result->flags = 0;
    }
}

u32 ProcessStageCues_02097324(CueOwner *owner, CueActor *actor, u16 cueIndex, u16 sourceIndex)
{
    int i;
    BOOL moved;
    u32 cueBase;
    u16 index;
    u16 variantId;
    u8 *variant;
    CueGroup *group;
    CueResult first;
    CueResult second;
    CueResult third;
    Matrix43 mtx;
    CueContext ctx;
    CueShape *cue;
    CueBody *body;
    char *name;

    moved = FALSE;
    func_01ff8830(&first, 0, sizeof(CueResult));
    func_01ff8830(&second, 0, sizeof(CueResult));
    func_01ff8830(&third, 0, sizeof(CueResult));
    func_01ff8830(&ctx, 0, sizeof(CueContext));
    ctx.owner = owner;
    ctx.actor = actor;
    ctx.entry = GetStageEntry_0209c074(owner->entryId);
    if (ctx.entry != NULL) {
        if (cueIndex != 0xffff) {
            variantId = GetActorVariant(actor);
            cueBase = 0;
            if (variantId != 0) {
                variant = GetVariantItem(ctx.entry, 0x11, (u16)(variantId - 1));
                if (variant == NULL) {
                    group = NULL;
                    goto checked;
                }
                cueBase = ((CueVariant *)variant)->cueBase;
            }
            group = (CueGroup *)GetEntrySectionItem(ctx.entry, 0xe, (u16)(cueBase + (u16)(cueIndex - 1)));
        checked:
            ctx.group = group;
            if (ctx.group == NULL) {
                goto done;
            }
            ctx.count = ctx.group->count;
        } else {
            ctx.count = 1;
        }
        ctx.source = owner->sources[sourceIndex - 1];
    }
done:
    for (i = 0; i < ctx.count; i++) {
        fx32 scale = actor->scale;

        cue = NULL;
        if (ctx.group != NULL) {
            index = GetCueSlot(ctx.group, i);
            cue = (CueShape *)GetEntrySectionItem(ctx.entry, 8, index);
            if (cue == NULL) {
                goto noBody;
            }
        }
        ctx.cue = cue;
        if (ctx.group != NULL) {
            name = (char *)func_ov001_0208f018(ctx.entry->file, cue->nodeName);
            if (name != NULL) {
                GetNodeMatrix_020915ac(ctx.actor, FindActorResourceIndexByName_02091248(ctx.actor, name), &mtx);
            }
        }
        if (ctx.group != NULL) {
            body = BuildCueBody(&ctx.body, cue, &mtx, scale, &actor->delta);
        } else {
        noBody:
            body = NULL;
        }
        if (body != NULL) {
            if (!moved && owner->kind == 8) {
                u8 *world = func_ov001_0209c3c0();
                moved = RaycastMoveStep_02093080(&ctx.body, actor);
                *(VecFx32 *)(world + 0x18e78) = ctx.body.hitPoint;
            }
            if (actor->behaviorFlags & 0x10000) {
                first.flags = 1;
                first.origin = actor->position;
                break;
            }
            func_ov001_02096bc8(owner, actor, actor->cueColumn, actor->cueRow, &ctx, &first);
            func_ov001_02096f38(owner, actor, actor->cueColumn, actor->cueRow, &ctx, &second);
            func_ov001_02097130(owner, actor, actor->cueColumn, actor->cueRow, &ctx, &third);
        }
    }
    ApplyCueResult(owner, actor, &ctx, &first);
    ApplyCueResult(owner, actor, &ctx, &second);
    ApplyCueResult(owner, actor, &ctx, &third);
    return first.flags | second.flags | third.flags;
}
