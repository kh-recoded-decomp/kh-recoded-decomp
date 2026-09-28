#include "nitro/types.h"

typedef struct MotionState {
    u8 pad_00[0xe4];
    s32 maxRange;
    u8 pad_e8[0x2c];
} MotionState;

typedef struct CollModelRef {
    void *model;
} CollModelRef;

typedef struct CollisionScene {
    u32 unk_00;
    CollModelRef *modelRef;
} CollisionScene;

typedef struct CollisionResult {
    u8 pad_00[0x2c];
    s32 hitRange;
} CollisionResult;

extern void InitMotionState_02032fe8(MotionState *state, void *info);
extern BOOL func_020330c0(MotionState *state, void *model);
extern CollisionResult g_collisionResult_027e0134;

CollisionResult *QueryModelMotionCollision_01ffce6c(CollisionScene *scene, void *info)
{
    MotionState state;

    InitMotionState_02032fe8(&state, info);
    if (func_020330c0(&state, scene->modelRef->model)) {
        g_collisionResult_027e0134.hitRange = state.maxRange;
        return &g_collisionResult_027e0134;
    }
    return NULL;
}
