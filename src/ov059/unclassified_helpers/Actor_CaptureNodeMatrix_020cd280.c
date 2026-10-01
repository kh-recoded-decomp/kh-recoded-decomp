#include "nitro/types.h"
#include "nitro/fx.h"
#include "nnsys/g3d.h"

typedef struct Actor {
    u8 pad_000[0x6bc];
    u32 captureNodeIds[4];
    MtxFx43 captureMatrices[3];
} Actor;

extern void CaptureGeometryMatrices_02019d00(MtxFx43 *m, MtxFx33 *n);

void Actor_CaptureNodeMatrix_020cd280(Actor *actor, NNSG3dRS *renderState)
{
    u32 nodeId;
    int slot;

    if (renderState->flag & NNS_G3D_RSFLAG_CURRENT_NODEDESC_VALID) {
        nodeId = renderState->currentNodeDesc;
    } else {
        nodeId = (u32)-1;
    }
    for (slot = 0; slot < 3; slot++) {
        if (nodeId == actor->captureNodeIds[slot]) {
            CaptureGeometryMatrices_02019d00(&actor->captureMatrices[slot], NULL);
            return;
        }
    }
}
