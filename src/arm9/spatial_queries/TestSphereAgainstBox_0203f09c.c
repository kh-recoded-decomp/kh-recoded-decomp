#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct CollisionSphere {
    VecFx32 center;
    fx32 radius;
} CollisionSphere;

typedef struct OrientedBox {
    VecFx32 center;
    VecFx32 halfExtents;
    MtxFx33 axes;
} OrientedBox;

typedef struct SphereContact {
    fx32 depth;
    VecFx32 normal;
    s32 time;
    u8 onEdge;
} SphereContact;

extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 FX_Sqrt_01ff9cfc(fx32 value);
extern void MTX_MultVec33_01ff9404(const VecFx32 *vec, const MtxFx33 *m, VecFx32 *dst);
extern fx32 AbsFx32_0203f228(fx32 value);
extern s32 Sign_0203f240(s32 value);
extern fx32 Vec_DotSelf_0203f258(const VecFx32 *v);
extern fx32 SquareFx32ToFx64_0203f268(fx32 value);
extern s32 SignNonNegativeOne_0203f2a0(s32 value);
extern VecFx32 VecFx32DividedByScalar_0203f2b0(const VecFx32 *vec, fx32 divisor);
extern void NegateVecFx32_0204aa40(VecFx32 *vec);
extern void TransformVectorByBasis_0204bee8(const VecFx32 *vec, const MtxFx33 *basis, VecFx32 *out);

BOOL TestSphereAgainstBox_0203f09c(CollisionSphere **sphereRef, OrientedBox **boxRef, SphereContact *contact, u32 flags)
{
    CollisionSphere *sphere = *sphereRef;
    OrientedBox *box = *boxRef;
    VecFx32 local;
    VecFx32 excess;
    fx32 distSq;
    fx32 absX;
    fx32 absY;
    fx32 absZ;
    BOOL onEdge;

    VEC_Subtract_01ff9e3c(&sphere->center, &box->center, &local);
    TransformVectorByBasis_0204bee8(&local, &box->axes, &local);
    if (AbsFx32_0203f228(local.x) > box->halfExtents.x) {
        excess.x = local.x - box->halfExtents.x * Sign_0203f240(local.x);
    } else {
        excess.x = 0;
    }
    if (AbsFx32_0203f228(local.y) > box->halfExtents.y) {
        excess.y = local.y - box->halfExtents.y * Sign_0203f240(local.y);
    } else {
        excess.y = 0;
    }
    if (AbsFx32_0203f228(local.z) > box->halfExtents.z) {
        excess.z = local.z - box->halfExtents.z * Sign_0203f240(local.z);
    } else {
        excess.z = 0;
    }
    distSq = Vec_DotSelf_0203f258(&excess);
    if (distSq > SquareFx32ToFx64_0203f268(sphere->radius)) {
        return FALSE;
    }
    if (contact != NULL) {
        if (distSq == 0) {
            absX = AbsFx32_0203f228(local.x);
            absY = AbsFx32_0203f228(local.y);
            absZ = AbsFx32_0203f228(local.z);
            if (absX > absY) {
                if (absX > absZ) {
                    contact->depth = sphere->radius + box->halfExtents.x - absX;
                    excess.x = SignNonNegativeOne_0203f2a0(local.x) << 12;
                } else {
                    contact->depth = sphere->radius + box->halfExtents.z - absZ;
                    excess.z = SignNonNegativeOne_0203f2a0(local.z) << 12;
                }
            } else if (absY > absZ) {
                contact->depth = sphere->radius + box->halfExtents.y - absY;
                excess.y = SignNonNegativeOne_0203f2a0(local.y) << 12;
            } else {
                contact->depth = sphere->radius + box->halfExtents.z - absZ;
                excess.z = SignNonNegativeOne_0203f2a0(local.z) << 12;
            }
            contact->normal = excess;
            onEdge = FALSE;
        } else {
            fx32 length = FX_Sqrt_01ff9cfc(distSq);
            contact->depth = sphere->radius - length;
            contact->normal = VecFx32DividedByScalar_0203f2b0(&excess, length);
            onEdge = (excess.x != 0) + (excess.y != 0) + (excess.z != 0) >= 2;
        }
        contact->onEdge = onEdge;
        if (flags & 1) {
            NegateVecFx32_0204aa40(&contact->normal);
        }
        MTX_MultVec33_01ff9404(&contact->normal, &box->axes, &contact->normal);
    }
    return TRUE;
}
