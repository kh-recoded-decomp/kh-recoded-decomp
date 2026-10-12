/* SBC NODE: blend node visibility, or use the command visibility bit.
 * Struct layout and command behavior cross-checked against khdays-decomp
 * (CC0-1.0), libs/nitro/nns/auto/NNSi_G3dFuncSbc_NODE.c. */

#pragma opt_common_subs off

#include "libs/nns/g3d/g3d_nsbca_internal.h"

typedef struct NNSG3dVisAnmResult_ {
    BOOL isVisible;
} NNSG3dVisAnmResult;

typedef struct NodeVisibilityState {
    NNSG3dRS rs;
    u8 reserved[0x184 - sizeof(NNSG3dRS)];
    NNSG3dVisAnmResult visResult;
} NodeVisibilityState;

typedef struct VisibilityAnimation {
    u8 reserved00[4];
    u16 numFrame;
    u16 numNode;
    u32 reserved08;
    u32 visData[1];
} VisibilityAnimation;

static inline BOOL BlendNodeVisibility(NNSG3dVisAnmResult *result,
    const NNSG3dAnmObj *animation, u32 nodeId)
{
    const NNSG3dAnmObj *current = animation;
    BOOL found = FALSE;

    result->isVisible = FALSE;
    do {
        if (nodeId < current->numMapData) {
            u32 map = current->mapData[nodeId];
            if (map & 0x100) {
                const VisibilityAnimation *visibility = current->resAnm;
                u32 index = (current->frame >> 12) * visibility->numNode + (map & 0xff);
                result->isVisible |= visibility->visData[index >> 5] & (1U << (index & 0x1f));
                found = TRUE;
            }
        }
        current = current->next;
    } while (current != NULL);
    return found;
}

void NNSi_G3dFuncSbc_NODE(NodeVisibilityState *state)
{
    if (!(state->rs.flag & 0x200)) {
        u32 nodeId = state->rs.c[1];
        NNSG3dRenderObj *object = state->rs.pRenderObj;
        u32 flags = state->rs.flag | 4;
        state->rs.currentNode = nodeId;
        state->rs.pVisAnmResult = &state->visResult;
        state->rs.flag = flags;
        if (object->anmVis == NULL ||
            !(object->hintVisAnmExist[nodeId >> 5] & (1U << (nodeId & 0x1f))) ||
            !BlendNodeVisibility((NNSG3dVisAnmResult *)state->rs.pVisAnmResult, object->anmVis, nodeId)) {
            ((NNSG3dVisAnmResult *)state->rs.pVisAnmResult)->isVisible = state->rs.c[2] & 1;
        }
        if (((NNSG3dVisAnmResult *)state->rs.pVisAnmResult)->isVisible) {
            state->rs.flag |= 1;
        } else {
            state->rs.flag &= ~1;
        }
    }
    state->rs.c += 3;
}
