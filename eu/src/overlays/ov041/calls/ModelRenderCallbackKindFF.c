#include "nitro/types.h"

typedef struct ModelRenderState {
    u8 pad_000[8];
    u32 flags;
    u8 pad_00c[0xa2];
    u8 currentNode;
} ModelRenderState;

typedef struct CapturedNodeMatrix {
    u8 pad_000[0x1d4];
    int nodeId;
    u8 matrix[1];
} CapturedNodeMatrix;

typedef struct ModelRoot {
    u8 pad_000[0x2cc];
    int nodeId;
    u8 matrix[0x7c];
    CapturedNodeMatrix *secondaryCapture;
} ModelRoot;

typedef struct MovieContextState {
    u8 pad_000[0xb8];
    ModelRoot *modelRoot;
} MovieContextState;

extern MovieContextState *gMovieContextState;
extern void NNS_G3dGetCurrentMtx(void *matrix, int mode);

void ModelRenderCallbackKindFF(ModelRenderState *renderState)
{
    ModelRoot *modelRoot = gMovieContextState->modelRoot;
    int nodeId = (renderState->flags & 0x10)
                     ? renderState->currentNode
                     : -1;
    CapturedNodeMatrix *secondaryCapture;

    if (nodeId == modelRoot->nodeId) {
        NNS_G3dGetCurrentMtx(modelRoot->matrix, 0);
    }
    secondaryCapture = modelRoot->secondaryCapture;
    if (nodeId == secondaryCapture->nodeId) {
        NNS_G3dGetCurrentMtx(secondaryCapture->matrix, 0);
    }
}
