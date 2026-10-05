#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct VecFx16 {
    s16 x;
    s16 y;
    s16 z;
} VecFx16;

typedef struct EdgeNormal {
    VecFx16 normal;
    u8 pad_06[6];
} EdgeNormal;

typedef struct CollisionShape {
    u8 pad_00[0x12];
    u16 vertexCount;
    VecFx16 normal;
    u8 pad_1a[6];
    EdgeNormal edgeNormals[4];
    VecFx32 vertices[1];
} CollisionShape;

typedef struct PolygonEdge {
    VecFx32 position;
    VecFx32 direction;
    VecFx32 normal;
    u8 pad_24[0xc];
} PolygonEdge;

typedef struct PolygonEdges {
    PolygonEdge edges[4];
    u8 count;
    u8 pad_c1[3];
    VecFx32 normal;
} PolygonEdges;

extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_NormalizeUnchecked_01ff9f88(const VecFx32 *input, VecFx32 *output);

void BuildPolygonEdges_01ffb3a0(CollisionShape *shape, PolygonEdges *out, BOOL withDirections) {
    VecFx32 unit;
    VecFx32 delta;
    VecFx32 direction;
    VecFx32 faceNormal;
    VecFx32 edgeNormal;
    u32 count;
    u8 i;

    count = out->count = shape->vertexCount;
    for (i = 0; i < count; i++) {
        out->edges[i].position = shape->vertices[i];
    }
    if (withDirections) {
        for (i = 0; i < count; i++) {
            int next = i + 1;
            PolygonEdge *edge;
            if (next == count) {
                next = 0;
            }
            edge = &out->edges[i];
            VEC_Subtract_01ff9e3c(&out->edges[next].position, &edge->position, &delta);
            unit = delta;
            VEC_NormalizeUnchecked_01ff9f88(&unit, &direction);
            edge->direction = direction;
        }
    }
    faceNormal.x = shape->normal.x;
    faceNormal.y = shape->normal.y;
    faceNormal.z = shape->normal.z;
    out->normal = faceNormal;
    for (i = 0; i < count; i++) {
        VecFx16 *src = &shape->edgeNormals[i].normal;
        edgeNormal.x = src->x;
        edgeNormal.y = src->y;
        edgeNormal.z = src->z;
        out->edges[i].normal = edgeNormal;
    }
}
