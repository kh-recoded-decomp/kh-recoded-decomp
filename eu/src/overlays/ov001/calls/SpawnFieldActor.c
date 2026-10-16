#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ActorEntry ActorEntry;

typedef struct ShapeParams {
    s32 kind;
    fx32 sizeY;
    fx32 sizeX;
    fx32 sizeZ;
    s32 angle;
} ShapeParams;

typedef char ShapeParamsSize[sizeof(ShapeParams) == 0x14 ? 1 : -1];
typedef char ShapeAngleOffset[(u32)&((ShapeParams *)0)->angle == 0x10 ? 1 : -1];

extern void ActorEntry_Init(int slot, ActorEntry *entry, u16 group,
                           const u8 *attributes, const ShapeParams *shape,
                           BOOL flag20, s8 priority);
extern void MIi_CpuCopy32(const void *source, void *destination, u32 size);

/* Initialize the field actor and return whether it has a supported shape. */
BOOL SpawnFieldActor(ActorEntry *entry, u8 group, u8 index, u32 slot,
                     ShapeParams *shapeOut, s8 shapeKind,
                     fx32 sizeX, fx32 sizeY, fx32 sizeZ, s32 angle,
                     BOOL flag20, BOOL isKind2)
{
    ShapeParams shape;
    u8 attributes[4];
    BOOL hasShape = FALSE;
    u8 kind = isKind2 ? 2 : 4;
    attributes[0] = kind;
    attributes[1] = group;
    attributes[2] = index;
    attributes[3] = 0;
    s8 priority = isKind2 ? 0x21 : 0x22;

    if ((u8)shapeKind <= 3) {
        shape.kind = shapeKind;
        shape.sizeX = sizeX;
        shape.sizeY = sizeY;
        shape.sizeZ = sizeZ;
        shape.angle = angle;
        ActorEntry_Init((u16)slot, entry, 0, attributes, &shape, flag20, priority);
        hasShape = TRUE;
    } else {
        shape.kind = -1;
        shape.sizeX = sizeX;
        shape.sizeY = sizeY;
        shape.sizeZ = sizeZ;
        shape.angle = angle;
        ActorEntry_Init((u16)slot, entry, 0, attributes, NULL, flag20, priority);
    }
    if (shapeOut != NULL) {
        MIi_CpuCopy32(&shape, shapeOut, sizeof(shape));
    }
    return hasShape;
}
