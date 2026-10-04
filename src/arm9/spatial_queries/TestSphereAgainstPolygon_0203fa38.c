#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Sphere {
    VecFx32 center;
    fx32 radius;
} Sphere;

typedef struct PolygonVertex {
    VecFx32 position;
    VecFx32 edgeDir;
    VecFx32 edgeNormal;
    u8 pad_24[0xc];
} PolygonVertex;

typedef struct CollisionPolygon {
    PolygonVertex vertices[4];
    u8 vertexCount;
    u8 pad_c1[3];
    VecFx32 normal;
} CollisionPolygon;

typedef struct HitResult {
    s32 distance;
    s32 data[4];
} HitResult;

extern void InitMaxDistanceHit_0203fb74(HitResult *result);
extern void SubtractVecFx32Into_0203f4a8(VecFx32 *dest, const VecFx32 *a, const VecFx32 *b);
extern void NormalizeVectorInto_0203f580(VecFx32 *dest, const VecFx32 *src);
extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);
extern BOOL IsVecZero_0203fc24(const VecFx32 *vec);
extern BOOL func_0203fba4(fx32 extent, const VecFx32 *offset, const VecFx32 *axis, u8 feature, HitResult *result);
extern BOOL func_0203fbe4(fx32 extent, const VecFx32 *offset, const VecFx32 *axis, u8 feature, HitResult *result);
extern void func_0204aea8(VecFx32 *out, const VecFx32 *vec, const VecFx32 *dir);
extern void WritePenetrationContact_0203d8fc(const HitResult *result, void *contact, u32 flags);

static inline HitResult MakeMaxDistanceHit(void)
{
    HitResult result;
    InitMaxDistanceHit_0203fb74(&result);
    return result;
}

static inline VecFx32 SubtractVec(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 result;
    SubtractVecFx32Into_0203f4a8(&result, a, b);
    return result;
}

BOOL TestSphereAgainstPolygon_0203fa38(Sphere **sphereRef, CollisionPolygon **polygonRef, void *contact, u32 flags)
{
    Sphere *sphere = *sphereRef;
    CollisionPolygon *polygon = *polygonRef;
    HitResult hit = MakeMaxDistanceHit();
    VecFx32 axis;
    VecFx32 diff = SubtractVec(&sphere->center, &polygon->vertices[0].position);
    u32 count;
    u8 i;

    if (!func_0203fba4(sphere->radius, &diff, &polygon->normal, 0, &hit)) {
        return FALSE;
    }
    count = polygon->vertexCount;
    for (i = 0; i < count; i++) {
        SubtractVecFx32Into_0203f4a8(&diff, &sphere->center, &polygon->vertices[i].position);
        if (VEC_DotProduct_01ff9e6c(&diff, &polygon->vertices[i].edgeNormal) >= 0) {
            func_0204aea8(&axis, &diff, &polygon->vertices[i].edgeDir);
            if (!func_0203fbe4(sphere->radius, &diff, &axis, 1, &hit)) {
                return FALSE;
            }
            if (VEC_DotProduct_01ff9e6c(&diff, &polygon->vertices[i].edgeDir) < 0) {
                NormalizeVectorInto_0203f580(&axis, &diff);
            } else {
                SubtractVecFx32Into_0203f4a8(&diff, &sphere->center, &polygon->vertices[(i + 1) % (int)count].position);
                if (IsVecZero_0203fc24(&diff)) {
                    continue;
                }
                NormalizeVectorInto_0203f580(&axis, &diff);
                if (VEC_DotProduct_01ff9e6c(&diff, &polygon->vertices[i].edgeDir) <= 0) {
                    continue;
                }
            }
            if (!func_0203fbe4(sphere->radius, &diff, &axis, 1, &hit)) {
                return FALSE;
            }
        }
    }
    WritePenetrationContact_0203d8fc(&hit, contact, flags);
    return TRUE;
}
