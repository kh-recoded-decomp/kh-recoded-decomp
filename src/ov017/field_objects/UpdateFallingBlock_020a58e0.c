#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct LiftObject {
    u8 pad_00[8];
    u8 *owner;
    u8 pad_0c[4];
    u8 shape[0x22];
    u8 actorId;
    u8 pad_33[5];
    VecFx32 position;
    u8 pad_44[0xc];
    s8 state;
    u8 pad_51;
    s8 timer;
    u8 pad_53;
    u16 flags;
    u8 pad_56[6];
    fx32 floorY;
    fx32 overlap;
} LiftObject;

typedef struct LiftActor {
    u8 pad_000[0x10c];
    u8 collision[0x2c];
    fx32 top;
    u8 pad_13c[8];
    fx32 bottom;
} LiftActor;

extern u32 func_ov042_020bd6ec(void);
extern fx32 *func_ov042_020bd290(void);
extern fx32 *func_ov042_020bd590(void);
extern void func_ov017_020a5d4c(LiftObject *obj, int mode);
extern void ActorSlot_UnlinkByIndex_02035c28(int index);
extern void CacheEntry_SetActive_02087258(LiftObject *obj, BOOL active);
extern void BuildCollisionShape_02080834(void *shape, const VecFx32 *position, int kind, fx32 sizeX, fx32 sizeY, fx32 sizeZ, s32 angle, BOOL allocate, int slot);
extern LiftActor *func_02036240(u32 id);
extern void Obj_SetPosition_0203569c(LiftActor *actor, const VecFx32 *position);
extern LiftObject *func_ov017_020a51c8(LiftObject *obj);
extern void Obj_RemoveFromQuadTree_020355f4(void *entity);
extern void ResizeBoxCollisionObject_02033e6c(void *object, fx32 sizeX, fx32 sizeY, fx32 sizeZ, s32 angle);
extern int func_ov017_020a5854(LiftObject *obj);
extern BOOL IsEntityWithinRange_02086cd8(LiftObject *obj);
extern void ActorSlot_SetFlag8ByIndex_02036120(int index, BOOL enable);

int UpdateFallingBlock_020a58e0(LiftObject *obj)
{
    LiftObject *below;
    LiftActor *actor;
    fx32 height;
    fx32 y;

    if (obj->flags & 8) {
        return 0;
    }
    if (!(func_ov042_020bd6ec() & 1)) {
        fx32 *base = func_ov042_020bd290();
        fx32 *range = func_ov042_020bd590();
        if (obj->position.x - *base < *range * 3) {
            func_ov017_020a5d4c(obj, 1);
            ActorSlot_UnlinkByIndex_02035c28(obj->actorId);
            CacheEntry_SetActive_02087258(obj, FALSE);
            return 0;
        }
    }
    if (obj->timer > 0) {
        obj->timer--;
    }
    obj->overlap = 0;
    if (obj->flags & 2) {
        y = obj->position.y - 0x600;
        obj->position.y = y;
        if (y <= obj->floorY) {
            obj->position.y = obj->floorY;
            obj->flags &= ~2;
            BuildCollisionShape_02080834(obj->shape, &obj->position, 3, 0xc00, 0xc00, 0xc00, 0, 0, -1);
            obj->timer = 4;
        }
        Obj_SetPosition_0203569c(func_02036240(obj->actorId), &obj->position);
    }
    if (obj->flags & 4) {
        below = func_ov017_020a51c8(obj);
        if (below == NULL) {
            Obj_RemoveFromQuadTree_020355f4(obj->owner + 0x10);
            obj->flags &= ~4;
            obj->overlap = 0;
        } else {
            if (!(below->flags & 2)) {
                obj->flags &= ~4;
            }
            actor = func_02036240(obj->actorId);
            height = below->position.y + 0x1800 - obj->position.y;
            obj->overlap = actor->top - actor->bottom - height;
            ResizeBoxCollisionObject_02033e6c(actor->collision, 0x1800, height, 0x1800, 0);
            Obj_SetPosition_0203569c(actor, &obj->position);
        }
    }
    if (obj->state == 1) {
        return func_ov017_020a5854(obj);
    }
    if (obj->state == 0) {
        ActorSlot_SetFlag8ByIndex_02036120(obj->actorId, IsEntityWithinRange_02086cd8(obj));
    }
    return 0;
}
