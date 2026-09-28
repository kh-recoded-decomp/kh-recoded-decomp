#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    VecFx32 position;
    u8 pad_0c[0x24];
} ShapeVertex;

typedef struct {
    ShapeVertex vertices[4];
    u8 vertexCount;
} ConvexShape;

extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);

fx32 GetMaxProjectedSpread_0203d7f4(ConvexShape *shape, const VecFx32 *axis)
{
    fx32 maxSpread;
    fx32 origin;
    u8 i;
    u8 count;
    maxSpread = (fx32)0x80000000;
    origin = VEC_DotProduct_01ff9e6c(&shape->vertices[0].position, axis);
    count = shape->vertexCount;
    for (i = 1; i < count; i++) {
        fx32 spread = VEC_DotProduct_01ff9e6c(&shape->vertices[i].position, axis) - origin;
        if (spread < 0) {
            spread = -spread;
        }
        if (maxSpread < spread) {
            maxSpread = spread;
        }
    }
    return maxSpread;
}
