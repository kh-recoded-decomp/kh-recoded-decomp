#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct VecFx16 {
    fx16 x;
    fx16 y;
    fx16 z;
} VecFx16;

typedef struct Plane {
    VecFx16 normal;
    u16 pad;
    fx32 dist;
} Plane;

extern void func_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void func_0202fff4(const VecFx32 *a, const VecFx16 *b, VecFx32 *out);
extern void func_02030098(const VecFx32 *input, VecFx16 *output);
extern fx32 VEC_DotProductFx16_0202ffb8(const VecFx32 *v, const VecFx16 *m);

void ComputeEdgePlane_02030204(const VecFx32 *pointA, const VecFx32 *pointB, Plane *plane, const VecFx16 *dir) {
    VecFx32 edge;

    func_01ff9e3c(pointB, pointA, &edge);
    func_0202fff4(&edge, dir, &edge);
    func_02030098(&edge, &plane->normal);
    plane->dist = VEC_DotProductFx16_0202ffb8(pointA, &plane->normal);
}
