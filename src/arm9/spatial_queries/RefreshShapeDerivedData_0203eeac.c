#include "nitro/types.h"

typedef struct CollisionShape {
    void *data;
    s32 bounds[6];
    s32 kind;
} CollisionShape;

typedef void (*ComputeBoundsFunc)(CollisionShape *shape, s32 *bounds);

extern ComputeBoundsFunc data_020559c0[];
void UpdateBoxAxisAlignedFlag_0203b1c0(void *box);
void InitSegmentFromEndpoints_0203b1f0(void *segment);
void func_0203b0b4(void *mesh);

void RefreshShapeDerivedData_0203eeac(CollisionShape *shape)
{
    switch (shape->kind) {
    case 0:
        break;
    case 1:
        UpdateBoxAxisAlignedFlag_0203b1c0(shape->data);
        break;
    case 2:
        InitSegmentFromEndpoints_0203b1f0(shape->data);
        break;
    case 3:
        InitSegmentFromEndpoints_0203b1f0(shape->data);
        break;
    case 4:
        InitSegmentFromEndpoints_0203b1f0(shape->data);
        break;
    case 5:
        func_0203b0b4(shape->data);
        break;
    }
    /* Recompute bounds for this shape kind */
    data_020559c0[shape->kind](shape, shape->bounds);
}
