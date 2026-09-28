#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct NNSG3dMtx33 {
    fx32 m[9];
} NNSG3dMtx33;

typedef struct NNSG3dJntAnmResult {
    u32 flag;
    VecFx32 scale;
    VecFx32 scaleEx0;
    VecFx32 scaleEx1;
    NNSG3dMtx33 rot;
    VecFx32 trans;
} NNSG3dJntAnmResult;

typedef struct NNSG3dResDictTreeNode {
    u8 refBit;
    u8 idxLeft;
    u8 idxRight;
    u8 idxEntry;
} NNSG3dResDictTreeNode;

typedef struct NNSG3dResDict {
    u8 revision;
    u8 numEntry;
    u16 sizeDictBlk;
    u16 dummy;
    u16 ofsEntry;
    NNSG3dResDictTreeNode node[1];
} NNSG3dResDict;

typedef struct NNSG3dResDictEntryHeader {
    u16 sizeUnit;
    u16 ofsName;
    u8 data[4];
} NNSG3dResDictEntryHeader;

typedef struct NNSG3dResNodeInfo {
    NNSG3dResDict dict;
} NNSG3dResNodeInfo;

typedef struct NNSG3dResDictNodeData {
    u32 offset;
} NNSG3dResDictNodeData;

typedef struct NNSG3dResNodeData {
    u16 flag;
    s16 rot00;
} NNSG3dResNodeData;

typedef struct NNSG3dAnmObj NNSG3dAnmObj;

typedef struct NNSG3dRenderObj {
    u32 flags;
    void *pResMdl;
    NNSG3dAnmObj *anmMat;
    u8 pad_0C[4];
    NNSG3dAnmObj *anmJnt;
    u8 pad_14[0x20];
    NNSG3dJntAnmResult *jntResults;
} NNSG3dRenderObj;

struct NNSG3dRenderState;
typedef void (*NNSG3dSbcCallback)(struct NNSG3dRenderState *);
typedef void (*NNSG3dFuncJntScale)(NNSG3dJntAnmResult *, const fx32 *, const u8 *, u32);
typedef void (*NNSG3dFuncJntSend)(NNSG3dJntAnmResult *);

typedef struct NNSG3dRenderState {
    u8 *pSbc;
    NNSG3dRenderObj *pRenderObj;
    u32 flags;
    NNSG3dSbcCallback sbcCallbacks[32];
    u8 callbackTimings[32];
    u8 commandAc;
    u8 materialAd;
    u8 nodeId;
    u8 pad_AF;
    u32 pad_B0;
    u32 jointWork;
    u8 pad_B8[0x1c];
    NNSG3dResNodeInfo *pResNodeInfo;
    u8 pad_D8[0x10];
    NNSG3dFuncJntScale funcJntScale;
    NNSG3dFuncJntSend sendJnt;
    u8 pad_F0[0x3c];
    NNSG3dJntAnmResult jntBuffer;
} NNSG3dRenderState;

extern void QueueOrSendGeometryCommandPair_01ffcedc(u32 command, u32 argument);
extern BOOL NNSi_G3dAnmBlendJnt_01ffda04(NNSG3dJntAnmResult *result, const NNSG3dAnmObj *anmObj, u32 nodeId);
extern void MI_Zero36B_01ff90dc(void *destination);
extern const u8 g_pivotPermutation_02055868[][4];

void NNSi_G3dFuncSbcNODEDESC_01ffe934(NNSG3dRenderState *state, u32 option)
{
    u32 nodeId = state->pSbc[1];
    u32 commandSize = 4;
    u32 sourceIndex;
    NNSG3dRenderObj *renderObj;
    NNSG3dJntAnmResult *result;

    state->nodeId = (u8)nodeId;
    state->flags |= 0x10;
    if (state->flags & 0x400) {
        if (option == 0x40 || option == 0x60) {
            ++commandSize;
        }
        if (option == 0x20 || option == 0x60) {
            ++commandSize;
            if (!(state->flags & 0x100)) {
                QueueOrSendGeometryCommandPair_01ffcedc(0x14, state->pSbc[4]);
            }
        }
        state->pSbc += commandSize;
        return;
    }

    sourceIndex = 4;
    if (option == 0x40 || (sourceIndex = 5, option == 0x60)) {
        ++commandSize;
        if (!(state->flags & 0x100)) {
            QueueOrSendGeometryCommandPair_01ffcedc(0x14, state->pSbc[sourceIndex]);
        }
    }
    renderObj = state->pRenderObj;
    if (renderObj->jntResults != NULL) {
        result = &renderObj->jntResults[nodeId];
        if (state->flags & 0x80) {
        } else {
            goto send_joint;
        }
    } else {
        result = &state->jntBuffer;
    }
    if (renderObj->anmJnt == NULL || !NNSi_G3dAnmBlendJnt_01ffda04(result, renderObj->anmJnt, nodeId)) {
        const NNSG3dResNodeInfo *info = state->pResNodeInfo;
        const NNSG3dResDictEntryHeader *header =
            (const NNSG3dResDictEntryHeader *)((const u8 *)info + info->dict.ofsEntry);
        const NNSG3dResNodeData *node = (const NNSG3dResNodeData *)((const u8 *)info +
            ((const NNSG3dResDictNodeData *)(header->data + header->sizeUnit * nodeId))->offset);
        u16 nodeFlags = node->flag;
        const u8 *payload = (const u8 *)node + sizeof(*node);

        result->flag = 6;
        if (!(nodeFlags & 1)) {
            const fx32 *translation = (const fx32 *)payload;
            result->trans.x = translation[0];
            result->trans.y = translation[1];
            result->trans.z = translation[2];
            payload += sizeof(VecFx32);
            result->flag &= ~4U;
        }
        if (!(nodeFlags & 2)) {
            if (nodeFlags & 8) {
                u32 pivot = (nodeFlags & 0xf0) >> 4;
                const u8 *permutation = g_pivotPermutation_02055868[pivot];
                fx32 first = ((const s16 *)payload)[0];
                fx32 second = ((const s16 *)payload)[1];
                MI_Zero36B_01ff90dc(&result->rot);
                result->rot.m[pivot] = (nodeFlags & 0x100) ? -0x1000 : 0x1000;
                result->rot.m[permutation[0]] = first;
                result->rot.m[permutation[1]] = second;
                result->rot.m[permutation[2]] = (nodeFlags & 0x200) ? -second : second;
                result->rot.m[permutation[3]] = (nodeFlags & 0x400) ? -first : first;
                payload += 4;
            } else {
                const s16 *rotation = (const s16 *)payload;
                result->rot.m[0] = node->rot00;
                result->rot.m[1] = rotation[0];
                result->rot.m[2] = rotation[1];
                result->rot.m[3] = rotation[2];
                result->rot.m[4] = rotation[3];
                result->rot.m[5] = rotation[4];
                result->rot.m[6] = rotation[5];
                result->rot.m[7] = rotation[6];
                result->rot.m[8] = rotation[7];
                payload += 16;
            }
            result->flag &= ~2U;
        }
        state->funcJntScale(result, (const fx32 *)payload, state->pSbc, nodeFlags);
    }
send_joint:
    if (!(state->flags & 0x100)) {
        state->sendJnt(result);
    }
    state->jointWork = 0;
    if (state->callbackTimings[6] == 3) {
        state->sbcCallbacks[6](state);
    }
    if (option == 0x20 || option == 0x60) {
        ++commandSize;
        if (!(state->flags & 0x100)) {
            QueueOrSendGeometryCommandPair_01ffcedc(0x13, state->pSbc[4]);
        }
    }
    state->pSbc += commandSize;
}
