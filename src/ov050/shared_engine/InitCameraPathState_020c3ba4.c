#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CameraPathInit {
    VecFx32 position;
    VecFx32 target;
} CameraPathInit;

typedef struct CameraPathState {
    VecFx32 position;
    VecFx32 target;
    u8 pad18[0xc];
    VecFx32 startPosition;
    VecFx32 startTarget;
    VecFx32 currentTarget;
} CameraPathState;

extern void *ReturnToCommitPage_020c3500(void);
extern u32 func_ov050_020c3510(u32 context, u32 data);

void *InitCameraPathState_020c3ba4(CameraPathState *state, u32 mode, const CameraPathInit *init)
{
    ReturnToCommitPage_020c3500();
    state->position = init->position;
    state->startPosition = state->position;
    state->target = init->target;
    state->startTarget = state->target;
    state->currentTarget = state->startTarget;
    return (void *)func_ov050_020c3510;
}
