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

extern void func_02032b0c(MotionState *state, void *info);
extern BOOL TestMoverAgainstModelTree_02032c6c(MotionState *state, void *model);
extern CollisionResult g_collisionResult_027e0134;

CollisionResult *QueryModelCollision_01ffce24(CollisionScene *scene, void *info)
{
    MotionState state;

    func_02032b0c(&state, info);
    if (TestMoverAgainstModelTree_02032c6c(&state, scene->modelRef->model)) {
        g_collisionResult_027e0134.hitRange = state.maxRange;
        return &g_collisionResult_027e0134;
    }
    return NULL;
}
