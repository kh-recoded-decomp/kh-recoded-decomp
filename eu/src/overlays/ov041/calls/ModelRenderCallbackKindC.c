#include "nitro/types.h"

typedef struct ModelRenderState {
    u8 pad_000[8];
    u32 flags;
    u8 pad_00c[0xa2];
    u8 currentNode;
} ModelRenderState;

typedef struct TrackedNodeMatrix {
    u8 flags;
    u8 nodeId;
    u8 pad_002[0x82];
    u8 matrix[1];
} TrackedNodeMatrix;

typedef struct TrackedNodeManager {
    u8 pad_000[0x38c];
    TrackedNodeMatrix *entries[5];
} TrackedNodeManager;

typedef struct ModelContext {
    u8 pad_000[0x10];
    TrackedNodeManager *trackedNodes;
} ModelContext;

extern ModelContext data_ov041_020cff48;
extern void NNS_G3dGetCurrentMtx(void *matrix, int mode);

void ModelRenderCallbackKindC(ModelRenderState *renderState)
{
    TrackedNodeManager *trackedNodes = data_ov041_020cff48.trackedNodes;
    int nodeId = (renderState->flags & 0x10)
                     ? renderState->currentNode
                     : -1;
    int i;

    for (i = 0; i < 5; ++i) {
        TrackedNodeMatrix *entry = trackedNodes->entries[i];
        if (entry != 0 && (entry->flags & 0x10) && nodeId == entry->nodeId) {
            NNS_G3dGetCurrentMtx(entry->matrix, 0);
        }
    }
}
