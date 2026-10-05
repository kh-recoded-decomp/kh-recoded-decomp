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

extern const VecFx32 data_02053438;

extern int func_ov031_020bc738(void);
extern void SyncActorShapePosition_020a3530(FieldObject *obj, const VecFx32 *position);
extern void SetScaledPosition_020a34f4(FieldObject *obj, const VecFx32 *position);
extern void func_ov018_020a3484(FieldObject *obj);
extern void FieldObject_SetDisabled_020a333c(FieldObject *obj, BOOL disable);
extern void CacheEntry_SetActive_02087258(FieldObject *obj, BOOL active);
extern void ResetObjectRotation_020a2968(FieldObject *obj);
extern int GetEntryUnlockState_02087478(BOOL skipModeCheck, int flagOffset, u32 entryId, u32 slot);
extern BOOL func_ov018_020a1ee4(FieldObject *obj);
extern void func_ov001_020645dc(int id);
extern void func_ov001_020645e8(int id);
extern void ResetKindDirection_020a1ebc(FieldObject *obj);
extern Actor *func_02036240(u32 id);
extern void RefreshShapeDerivedData_0203eeac(ShapeData **shape);
extern void FieldObject_HandleStrongHit_020a28d4(void);
extern void FieldObject_SpawnContactEffect_020a286c(void);

static inline HitCallback MakeCallback(void *func, void *context)
{
    HitCallback callback;
    callback.func = func;
    callback.context = context;
    return callback;
}

void RespawnKind6FieldObject_020a35b8(FieldObject *obj, const VecFx32 *position, int spawnParam, u8 level, int kind,
                                      s8 linkIndex, s8 linkGroup, BOOL sync)
{
    Actor *actor;
    BOOL skipCheck;

    if (!(obj->flags & 8)) {
        obj->flags &= ~0x1100;
        return;
    }
    obj->areaId = func_ov031_020bc738();
    if (sync) {
        SyncActorShapePosition_020a3530(obj, position);
    } else {
        SetScaledPosition_020a34f4(obj, position);
    }
    obj->anchor = obj->position;
    obj->spawnParam = spawnParam;
    obj->level = level;
    obj->hitCount = 0;
    obj->state = 2;
    func_ov018_020a3484(obj);
    FieldObject_SetDisabled_020a333c(obj, FALSE);
    CacheEntry_SetActive_02087258(obj, TRUE);
    obj->linkIndex = linkIndex;
    obj->linkGroup = linkGroup;
    ResetObjectRotation_020a2968(obj);
    if (kind == 10) {
        skipCheck = FALSE;
        if (kind != 10) {
            skipCheck = TRUE;
        }
        if (!GetEntryUnlockState_02087478(skipCheck, linkGroup, obj->entryId, obj->entrySlot)) {
            obj->kind = 10;
        } else {
            obj->kind = 1;
        }
    } else {
        obj->kind = kind;
    }
    if (func_ov018_020a1ee4(obj)) {
        if (obj->linkGroup == -1) {
            func_ov001_020645dc(obj->entryId);
        } else {
            func_ov001_020645e8(obj->entryId);
        }
    }
    CacheEntry_SetActive_02087258(obj, TRUE);
    obj->flags &= ~0x1e00;
    obj->velocity = data_02053438;
    ResetKindDirection_020a1ebc(obj);
    actor = func_02036240(obj->actorId);
    if (kind == 3) {
        actor->shape->scaleX = 0x666;
        actor->shape->scaleZ = actor->shape->scaleX;
    } else {
        actor->shape->scaleX = 0x800;
        actor->shape->scaleZ = 0x800;
    }
    RefreshShapeDerivedData_0203eeac(&actor->shape);
    switch (obj->kind) {
    case 3:
        actor->hitHandlers[1] = MakeCallback(FieldObject_SpawnContactEffect_020a286c, obj);
        actor->hitHandlers[0].func = NULL;
        break;
    case 1:
        actor->hitHandlers[1].func = NULL;
        actor->hitHandlers[0].func = NULL;
        break;
    case 2:
        actor->hitHandlers[1].func = NULL;
        actor->hitHandlers[0] = MakeCallback(FieldObject_HandleStrongHit_020a28d4, obj);
        break;
    }
    obj->flags &= ~0x100;
}
