#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CollShape {
    u8 pad_00[0x1c];
    s32 kind;
    VecFx32 velocity;
    VecFx32 maxBound;
    VecFx32 minBound;
} CollShape;

typedef struct CollBody {
    u8 pad_00[0x18];
    u8 shapeData[4];
    VecFx32 maxBound;
    VecFx32 minBound;
    s32 type;
} CollBody;

typedef int (*PairHitFunc)(void *shapeData, CollShape *shape, void *arg, u32 flags);
typedef int (*PairTestFunc)(void *shapeData, CollShape *shape, void *arg, u32 flags, VecFx32 *push);

extern PairHitFunc data_020558a0[][6];
extern PairTestFunc data_02055930[][6];
extern void NegateVecFx32_0204aa40(VecFx32 *vec);

int DispatchShapePairTest_02080bfc(CollBody *body, CollShape *shape, void *arg)
{
    VecFx32 reversed;
    VecFx32 push;
    int overlap;
    u32 flags;

    if (body->type >= 0) {
        if (body->maxBound.x >= shape->minBound.x && body->minBound.x <= shape->maxBound.x &&
            body->maxBound.z >= shape->minBound.z && body->minBound.z <= shape->maxBound.z &&
            body->maxBound.y >= shape->minBound.y && body->minBound.y <= shape->maxBound.y) {
            if (shape->velocity.x == 0 && shape->velocity.y == 0 && shape->velocity.z == 0) {
                overlap = 2;
            } else {
                reversed = shape->velocity;
                NegateVecFx32_0204aa40(&reversed);
                push = reversed;
                overlap = 1;
            }
        } else {
            overlap = 0;
        }
        if (overlap != 0) {
            if (overlap == 2) {
                flags = 2;
                if (shape->kind != 2) {
                    flags = 0;
                }
                return data_020558a0[body->type][shape->kind](body->shapeData, shape, arg, flags | 8);
            }
            return data_02055930[body->type][shape->kind](body->shapeData, shape, arg, 8, &push);
        }
        return 0;
    }
    return 0;
}
