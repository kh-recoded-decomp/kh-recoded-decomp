#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CollisionSphere {
    VecFx32 center;
    fx32 radius;
} CollisionSphere;

typedef struct CollisionCylinder {
    VecFx32 start;
    VecFx32 end;
    VecFx32 direction;
    fx32 length;
    fx32 radius;
} CollisionCylinder;

typedef struct SphereShapeRef {
    CollisionSphere *sphere;
    u8 reserved04[0x18];
    int kind;
} SphereShapeRef;

typedef struct CylinderShapeRef {
    CollisionCylinder *cylinder;
    u8 reserved04[0x18];
    int kind;
} CylinderShapeRef;

typedef struct CollisionContact {
    u8 reserved00[0x14];
    u8 kind;
} CollisionContact;

extern BOOL SweepSphereAgainstCylinder_02042678(SphereShapeRef *sphere,
    CylinderShapeRef *cylinder, CollisionContact *contact, u32 flags,
    const VecFx32 *velocity);

BOOL SweepInflatedSphereAgainstCylinder_02042b04(const SphereShapeRef *sphereRef,
    CylinderShapeRef *cylinderRef, CollisionContact *contact, u32 flags,
    const VecFx32 *velocity)
{
    SphereShapeRef inflatedRef;
    CollisionSphere inflated;
    CollisionSphere *sphere = sphereRef->sphere;

    inflatedRef.sphere = &inflated;
    inflated.center = sphere->center;
    inflated.radius = sphere->radius + cylinderRef->cylinder->radius;
    if (SweepSphereAgainstCylinder_02042678(&inflatedRef, cylinderRef, contact,
            flags | 8, velocity)) {
        if (contact != NULL) {
            contact->kind = 3;
        }
        return TRUE;
    }
    return FALSE;
}
