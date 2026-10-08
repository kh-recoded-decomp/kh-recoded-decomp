#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ShapeData {
    u8 pad_00[0xc];
    fx32 scaleX;
    u8 pad_10[4];
    fx32 scaleZ;
} ShapeData;

typedef struct HitCallback {
    void *func;
    void *context;
} HitCallback;

typedef struct Actor {
    u8 pad_000[0x130];
    ShapeData *shape;
    u8 pad_134[0x50];
    HitCallback hitHandlers[2];
} Actor;

typedef struct FieldObject {
    u8 pad_00[0x32];
    u8 actorId;
    u8 pad_33[5];
    VecFx32 position;
    u16 entryId;
    u8 entrySlot;
    u8 pad_47[5];
    s8 linkIndex;
    s8 linkGroup;
    u8 pad_4e[2];
    u16 flags;
    s8 state;
    u8 pad_53[0x11];
    VecFx32 velocity;
    u8 pad_70[0x24];
    VecFx32 anchor;
    s32 kind;
    s32 areaId;
    u8 pad_a8[0xc];
    s32 spawnParam;
    u8 level;
    u8 hitCount;
} FieldObject;

extern const VecFx32 data_0205344c;

extern int GetMovieFrameCount(void);
extern void SyncActorShapePosition(FieldObject *obj, const VecFx32 *position);
extern void SetScaledPosition(FieldObject *obj, const VecFx32 *position);
extern void func_ov018_020a34a4(FieldObject *obj);
extern void func_ov018_020a335c(FieldObject *obj, BOOL disable);
extern void CacheEntry_SetActive(FieldObject *obj, BOOL active);
extern void ResetObjectRotation(FieldObject *obj);
extern int GetEntryUnlockState(BOOL skipModeCheck, int flagOffset, u32 entryId, u32 slot);
extern BOOL func_ov018_020a1f04(FieldObject *obj);
extern void SetSessionFlag(int id);
extern void ClearSessionPackedBit(int id);
extern void ResetKindDirection(FieldObject *obj);
extern Actor *ActorRegistry_GetEntityByIndex(u32 id);
extern void RefreshShapeDerivedData(ShapeData **shape);
extern void FieldObject_HandleStrongHit(void);
extern void FieldObject_SpawnContactEffect(void);

static inline HitCallback MakeCallback(void *func, void *context)
{
    HitCallback callback;
    callback.func = func;
    callback.context = context;
    return callback;
}

void RespawnKind6FieldObject(FieldObject *obj, const VecFx32 *position, int spawnParam, u8 level, int kind,
                                      s8 linkIndex, s8 linkGroup, BOOL sync)
{
    Actor *actor;
    BOOL skipCheck;

    if (!(obj->flags & 8)) {
        obj->flags &= 0xeeff;
        return;
    }
    obj->areaId = GetMovieFrameCount();
    if (sync) {
        SyncActorShapePosition(obj, position);
    } else {
        SetScaledPosition(obj, position);
    }
    obj->anchor = obj->position;
    obj->spawnParam = spawnParam;
    obj->level = level;
    obj->hitCount = 0;
    obj->state = 2;
    func_ov018_020a34a4(obj);
    func_ov018_020a335c(obj, FALSE);
    CacheEntry_SetActive(obj, TRUE);
    obj->linkIndex = linkIndex;
    obj->linkGroup = linkGroup;
    ResetObjectRotation(obj);
    if (kind == 10) {
        skipCheck = FALSE;
        if (kind != 10) {
            skipCheck = TRUE;
        }
        if (!GetEntryUnlockState(skipCheck, linkGroup, obj->entryId, obj->entrySlot)) {
            obj->kind = 10;
        } else {
            obj->kind = 1;
        }
    } else {
        obj->kind = kind;
    }
    if (func_ov018_020a1f04(obj)) {
        if (obj->linkGroup == -1) {
            SetSessionFlag(obj->entryId);
        } else {
            ClearSessionPackedBit(obj->entryId);
        }
    }
    CacheEntry_SetActive(obj, TRUE);
    obj->flags &= 0xe1ff;
    obj->velocity = data_0205344c;
    ResetKindDirection(obj);
    actor = ActorRegistry_GetEntityByIndex(obj->actorId);
    if (kind == 3) {
        actor->shape->scaleX = 0x666;
        actor->shape->scaleZ = actor->shape->scaleX;
    } else {
        actor->shape->scaleX = 0x800;
        actor->shape->scaleZ = 0x800;
    }
    RefreshShapeDerivedData(&actor->shape);
    switch (obj->kind) {
    case 3:
        actor->hitHandlers[1] = MakeCallback(FieldObject_SpawnContactEffect, obj);
        actor->hitHandlers[0].func = NULL;
        break;
    case 1:
        actor->hitHandlers[1].func = NULL;
        actor->hitHandlers[0].func = NULL;
        break;
    case 2:
        actor->hitHandlers[1].func = NULL;
        actor->hitHandlers[0] = MakeCallback(FieldObject_HandleStrongHit, obj);
        break;
    }
    obj->flags &= 0xfeff;
}
