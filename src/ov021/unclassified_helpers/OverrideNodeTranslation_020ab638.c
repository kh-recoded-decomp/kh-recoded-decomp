#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct {
    u8 pad_00[0x40];
    u8 nodeDict[4];
} ModelResource;

typedef struct {
    u8 pad_00[4];
    ModelResource *resMdl;
    u8 pad_08[0x24];
    void *ptrUser;
} RenderObject;

typedef struct {
    u8 *code;
    RenderObject *renderObj;
    u32 flag;
    void (*callbacks[32])(void *rs);
    u8 callbackTiming[32];
    u8 currentNode;
    u8 currentMat;
    u8 currentNodeDesc;
} RenderState;

typedef struct {
    u8 pad_000[0x134];
    VecFx32 basePosition;
} SlotMarker;

extern const u8 data_ov021_020b4fc8[];

extern int FindResourceIndexByName_0201aafc(const void *dict, const void *name);
extern void CaptureGeometryMatrices_02019d00(MtxFx43 *posMtx, MtxFx33 *vecMtx);
extern void QueueOrSendGeometryCommand_01ffa37c(u32 op, const void *args, u32 numWords);

static inline void GeCommand1(u32 op, u32 param)
{
    QueueOrSendGeometryCommand_01ffa37c(op, &param, 1);
}

void OverrideNodeTranslation_020ab638(RenderState *rs)
{
    SlotMarker *marker = rs->renderObj->ptrUser;
    ModelResource *model = rs->renderObj->resMdl;
    void *dict = model != NULL ? model->nodeDict : NULL;
    int nodeIndex = dict != NULL ? FindResourceIndexByName_0201aafc(dict, data_ov021_020b4fc8) : -1;
    int currentNode = (rs->flag & 0x10) ? rs->currentNodeDesc : -1;

    if (currentNode == nodeIndex) {
        MtxFx33 vecMtx;
        MtxFx43 posMtx;
        VecFx32 *trans;

        CaptureGeometryMatrices_02019d00(&posMtx, &vecMtx);
        trans = &marker->basePosition;
        posMtx._30 = trans->x;
        posMtx._31 = trans->y;
        posMtx._32 = trans->z;
        GeCommand1(0x10, 2);
        QueueOrSendGeometryCommand_01ffa37c(0x17, &vecMtx, 12);
        GeCommand1(0x10, 1);
        QueueOrSendGeometryCommand_01ffa37c(0x17, &posMtx, 12);
        GeCommand1(0x10, 2);
        rs->callbacks[6] = NULL;
        rs->callbackTiming[6] = 0;
    }
}
