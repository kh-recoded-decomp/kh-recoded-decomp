#include "nitro/types.h"

typedef struct ModelRenderState {
    u8 pad_000[8];
    u32 flags;
    u8 pad_00c[0xa2];
    u8 currentNode;
} ModelRenderState;

typedef struct TrackedModelMatrix {
    u8 pad_000[0x1d4];
    int nodeId;
    u8 matrix[1];
} TrackedModelMatrix;

typedef struct ModelRoot {
    u8 pad_000[0x350];
    TrackedModelMatrix *trackedMatrix;
} ModelRoot;

typedef struct MovieContextState {
    u8 pad_000[0xb8];
    ModelRoot *modelRoot;
} MovieContextState;

extern MovieContextState *gMovieContextState;
extern void NNS_G3dGetCurrentMtx(void *matrix, int mode);
extern void ModelRenderCallbackKindC(ModelRenderState *renderState);

void ModelRenderCallbackKindFD(ModelRenderState *renderState)
{
    ModelRoot *modelRoot = gMovieContextState->modelRoot;
    int nodeId = (renderState->flags & 0x10)
                     ? renderState->currentNode
                     : -1;
    TrackedModelMatrix *trackedMatrix = modelRoot->trackedMatrix;

    if (nodeId == trackedMatrix->nodeId) {
        NNS_G3dGetCurrentMtx(trackedMatrix->matrix, 0);
    }
    ModelRenderCallbackKindC(renderState);
}
