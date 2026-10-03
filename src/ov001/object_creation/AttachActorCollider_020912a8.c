#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ColliderFilter {
    s32 unk00;
    s32 priority;
} ColliderFilter;

typedef struct ColliderCallback {
    void (*func)(void);
    void *owner;
} ColliderCallback;

typedef struct ActorCollider {
    u8 object[0x68];
    ColliderFilter filter;
    ColliderCallback callback;
    u8 pad_78[0x10];
    fx32 radius;
    fx32 height;
    VecFx32 offset;
    u8 active;
    u8 pad_9d[3];
    u16 resourceIndex;
    u16 nextId;
} ActorCollider;

typedef struct ColliderParams {
    u8 pad_00[8];
    VecFx32 offset;
    s32 shape;
    fx32 sizeX;
    fx32 sizeY;
    fx32 sizeZ;
} ColliderParams;

typedef struct ColliderOwner {
    u8 pad_000[0x10];
    u8 body[0x274];
    u16 colliderHead;
} ColliderOwner;

extern BOOL func_02036230(ColliderOwner *owner);
extern int ReleaseStageSlot_0209c008(int index);
extern ActorCollider *GetStageLinkedActor_0209c168(u32 id);
extern void func_01ff88c4(void *dst, u32 value, u32 size);
extern void func_01ff86fc(u32 value, void *dst, u32 size);
extern BOOL InitCylinderCollisionObject_02033c9c(void *object, u16 groupMask, s32 ownerId, fx32 radius, fx32 height);
extern BOOL InitSphereCollisionObject_02033d18(void *object, u16 groupMask, s32 ownerId, fx32 radius);
extern BOOL InitCapsuleCollisionObject_02033d54(void *object, u16 groupMask, s32 ownerId, fx32 radius, fx32 height);
extern BOOL InitBoxCollisionObject_02033dd0(void *object, u16 groupMask, s32 ownerId, fx32 sizeX, fx32 sizeY, fx32 sizeZ, s32 angle);
extern u16 FindActorResourceIndexByName_02091248(ColliderOwner *owner, const char *name);
extern void func_ov001_0208f658(void);

static inline ColliderFilter MakeFilter(s32 unk00, s32 priority)
{
    ColliderFilter filter;
    filter.unk00 = unk00;
    filter.priority = priority;
    return filter;
}

static inline ColliderCallback MakeCallback(void (*func)(void), void *owner)
{
    ColliderCallback callback;
    callback.func = func;
    callback.owner = owner;
    return callback;
}

void AttachActorCollider_020912a8(ColliderOwner *owner, ColliderParams *params, const char *name)
{
    int slotId;
    ActorCollider *collider;
    ActorCollider *link;
    u32 id;

    if (!func_02036230(owner)) {
        return;
    }
    slotId = ReleaseStageSlot_0209c008(7);
    if (slotId == 0) {
        return;
    }
    collider = GetStageLinkedActor_0209c168(slotId);
    if (collider == NULL) {
        return;
    }
    func_01ff88c4(collider, 0, sizeof(ActorCollider));
    func_01ff86fc(0, &collider->active, 4);
    collider->active = 1;
    switch (params->shape) {
    case 2:
        collider->radius = params->sizeX;
        collider->height = params->sizeY;
        InitCylinderCollisionObject_02033c9c(collider, 0x40, (s32)owner->body, collider->radius, collider->height);
        break;
    case 1:
        collider->radius = params->sizeX;
        collider->height = params->sizeY;
        InitCapsuleCollisionObject_02033d54(collider, 0x40, (s32)owner->body, collider->radius, collider->height);
        break;
    case 0:
        collider->radius = params->sizeX;
        collider->height = params->sizeY;
        InitSphereCollisionObject_02033d18(collider, 0x40, (s32)owner->body, collider->radius);
        break;
    case 3:
        InitBoxCollisionObject_02033dd0(collider, 0x40, (s32)owner->body, params->sizeX, params->sizeY, params->sizeZ, 0);
        break;
    }
    collider->callback = MakeCallback(func_ov001_0208f658, owner);
    collider->filter = MakeFilter(0, 0x19);
    collider->offset = params->offset;
    id = owner->colliderHead;
    if (id == 0) {
        owner->colliderHead = slotId;
    } else {
        while (id != 0) {
            link = GetStageLinkedActor_0209c168(id);
            if (link == NULL) {
                break;
            }
            id = link->nextId;
            if (id == 0) {
                link->nextId = slotId;
                break;
            }
        }
    }
    if (collider != NULL) {
        collider->resourceIndex = FindActorResourceIndexByName_02091248(owner, name);
    }
}
