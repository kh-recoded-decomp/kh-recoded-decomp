#pragma opt_common_subs off

#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/gx.h"

typedef struct MtxFx33 { fx32 aM[9]; } MtxFx33;
typedef struct MtxFx43 { fx32 aM[12]; } MtxFx43;
typedef struct MtxFx44 { fx32 aM[16]; } MtxFx44;
typedef struct NNSG3dResMdl {
    u32 size, ofsSbc, ofsMat, ofsShp, ofsEvpMtx;
} NNSG3dResMdl;
typedef struct NNSG3dResEvpMtx {
    MtxFx43 invPosition;
    MtxFx33 invVector;
} NNSG3dResEvpMtx;
typedef struct NNSG3dNodeMixCacheEntry {
    MtxFx44 clip;
    MtxFx33 vector;
} NNSG3dNodeMixCacheEntry;
typedef struct NNSG3dNodeMixResult {
    MtxFx43 position;
    MtxFx33 vector;
} NNSG3dNodeMixResult;
typedef struct NNSG3dSbcNodeMixEntry {
    u8 matrixIndex, nodeId, weight;
} NNSG3dSbcNodeMixEntry;
typedef struct NNSG3dSbcNodeMix {
    u8 opcode, destinationIndex, numEntries;
    NNSG3dSbcNodeMixEntry entries[1];
} NNSG3dSbcNodeMix;
typedef struct NNSG3dRenderObj {
    u32 flags;
    NNSG3dResMdl *pResMdl;
} NNSG3dRenderObj;
typedef struct NNSG3dRenderState {
    u8 *pSbc;
    NNSG3dRenderObj *pRenderObj;
    u32 flags;
    u8 pad00c_0cc[0xc0];
    volatile u32 nodeMixCacheValid[2];
} NNSG3dRenderState;

extern NNSG3dNodeMixCacheEntry data_0205bf64[];
extern MtxFx33 data_0205bfa4;
extern void func_01ff8740(u32 value, void *destination, u32 size);
extern void func_01ff80e4(void);
extern void G3_MultMtx43_01ffa18c(const MtxFx43 *matrix);
extern void G3_MultMtx33_01ffa1a8(const MtxFx33 *matrix);
extern void G3_LoadMtx43_01ffa170(const MtxFx43 *matrix);
extern int G3X_GetClipMtx_02006b90(MtxFx44 *destination);
extern int G3X_GetVectorMtx_02006bc0(MtxFx33 *destination);

#pragma inline_max_size(1300)
static inline void AddVector(MtxFx33 *sum, const MtxFx33 *matrix, s64 weight)
{
#define ADD_V(n) sum->aM[n] += ((weight * matrix->aM[n]) >> 12)
    ADD_V(0); ADD_V(1); ADD_V(2);
    ADD_V(3); ADD_V(4); ADD_V(5);
    ADD_V(6); ADD_V(7); ADD_V(8);
#undef ADD_V
}

void NNSi_G3dFuncSbcNODEMIX_01ffec28(NNSG3dRenderState *state, u32 option)
{
    s64 weight;
    const NNSG3dSbcNodeMixEntry *entry;
    NNSG3dNodeMixCacheEntry *cache;
    MtxFx33 *previousVector;
    const NNSG3dSbcNodeMix *command;
    const NNSG3dResMdl *model;
    const NNSG3dResEvpMtx *inverse;
    u32 count;
    NNSG3dNodeMixResult accum;
    u32 i;
    volatile G3MatrixRegisters *registers = (volatile G3MatrixRegisters *)0x04000440;
    model = state->pRenderObj->pResMdl;
    command = (const NNSG3dSbcNodeMix *)state->pSbc;
    count = command->numEntries;
    inverse = (const NNSG3dResEvpMtx *)((const u8 *)model + model->ofsEvpMtx);
    entry = command->entries;
    weight = 0;

    func_01ff8740(0, &accum, sizeof(accum));
    func_01ff80e4();
    registers->mode = 0;
    registers->store = 1;
    registers->identity = 0;
    registers->mode = 2;
    for (i = 0; i < count; ++i) {
        u32 cached;
        s32 cacheOffset;
        u32 nodeId = entry->nodeId;
        cacheOffset = (s16)nodeId * (s32)sizeof(NNSG3dNodeMixCacheEntry);
        cached = state->nodeMixCacheValid[nodeId >> 5] &
                     (1U << (nodeId & 31));
        cache =
            (NNSG3dNodeMixCacheEntry *)((u8 *)data_0205bf64 + cacheOffset);
        if (!cached) {
            volatile u32 *restoreRegister = (volatile u32 *)0x04000450;
            state->nodeMixCacheValid[nodeId >> 5] |= 1U << (nodeId & 31);
            *restoreRegister = entry->matrixIndex;
            registers->mode = 1;
            G3_MultMtx43_01ffa18c(&inverse[nodeId].invPosition);
        }
        if (i != 0) {
            AddVector(&accum.vector, previousVector, weight);
        }
        if (!cached) {
            while (G3X_GetClipMtx_02006b90(&cache->clip) != 0) {
            }
            registers->mode = 2;
            G3_MultMtx33_01ffa1a8(&inverse[nodeId].invVector);
        }
        weight = (fx32)(entry->weight << 4);
#define ADD_P(dst,src) accum.position.aM[dst] += (((s64)weight * cache->clip.aM[src]) >> 12)
        ADD_P(0,0); ADD_P(1,1); ADD_P(2,2);
        ADD_P(3,4); ADD_P(4,5); ADD_P(5,6);
        ADD_P(6,8); ADD_P(7,9); ADD_P(8,10);
        ADD_P(9,12); ADD_P(10,13); ADD_P(11,14);
#undef ADD_P
        ++entry;
        previousVector = (MtxFx33 *)((u8 *)&data_0205bfa4 + cacheOffset);
        if (!cached) {
            while (G3X_GetVectorMtx_02006bc0(previousVector) != 0) {
            }
        }
    }
    AddVector(&accum.vector, previousVector, weight);
    G3_LoadMtx43_01ffa170((const MtxFx43 *)&accum.vector);
    registers->mode = 1;
    G3_LoadMtx43_01ffa170(&accum.position);
    registers->mode = 0;
    registers->restore = 1;
    registers->mode = 2;
    registers->store = state->pSbc[1];
    state->pSbc += (state->pSbc[2] + 1) * 3;
}
