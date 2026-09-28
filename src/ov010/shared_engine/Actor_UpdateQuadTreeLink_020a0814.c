#include "nitro/types.h"

extern u32 func_02036230(void);
extern int FixedPointMultiply12(int left, int right);
extern u32 Obj_UpdateQuadTreeLink_02035634(u32 world, void *entity, u32 arg);
extern void QuadTree_RemoveObject_02033c60(int *tree, int node);

void Actor_UpdateQuadTreeLink_020a0814(int actor, int speedDelta)
{
    u32 world;
    int scaledSpeed;
    int worldPtr;

    world = func_02036230();
    scaledSpeed = FixedPointMultiply12(speedDelta, (int)*(short *)(actor + 0x1c4));
    Obj_UpdateQuadTreeLink_02035634(world, (void *)(actor + 0x10), scaledSpeed);
    worldPtr = func_02036230();
    QuadTree_RemoveObject_02033c60((int *)**(int **)(worldPtr + 4), actor + 0x11c);
}
