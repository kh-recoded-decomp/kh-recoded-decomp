#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CollisionShapeDesc {
    u16 flags;
    u16 groupMask;
    fx32 sizeY;
    fx32 radius;
    fx32 sizeZ;
    s32 angle;
} CollisionShapeDesc;

typedef struct CollisionOwner {
    u32 flags;
    u8 pad_004[0x108];
    u8 object[0x88];
    u32 contactState;
} CollisionOwner;

extern BOOL InitCylinderCollisionObject_02033c9c(void *object, u16 groupMask, s32 ownerId, fx32 radius, fx32 height);
extern BOOL InitCapsuleCollisionObject_02033d54(void *object, u16 groupMask, s32 ownerId, fx32 radius, fx32 height);
extern BOOL InitSphereCollisionObject_02033d18(void *object, u16 groupMask, s32 ownerId, fx32 radius);
extern BOOL InitBoxCollisionObject_02033dd0(void *object, u16 groupMask, s32 ownerId, fx32 sizeX, fx32 sizeY, fx32 sizeZ, s32 angle);
extern void func_01ff86fc(u32 value, void *dst, u32 size);

BOOL SetupOwnerCollisionShape_02035458(CollisionOwner *owner, const CollisionShapeDesc *desc)
{
    if (desc != NULL) {
        owner->flags |= desc->flags;
        switch (desc->flags & 3) {
        case 0:
            InitCylinderCollisionObject_02033c9c(owner->object, desc->groupMask, (s32)owner, desc->radius, desc->sizeY);
            break;
        case 1:
            InitCapsuleCollisionObject_02033d54(owner->object, desc->groupMask, (s32)owner, desc->radius, desc->sizeY);
            break;
        case 2:
            InitSphereCollisionObject_02033d18(owner->object, desc->groupMask, (s32)owner, desc->radius);
            break;
        case 3:
            InitBoxCollisionObject_02033dd0(owner->object, desc->groupMask, (s32)owner, desc->radius, desc->sizeY, desc->sizeZ, desc->angle);
            break;
        }
        owner->flags &= ~0x10;
    } else {
        owner->flags |= 0x10;
    }
    func_01ff86fc(0, &owner->contactState, sizeof(owner->contactState));
    return TRUE;
}



