#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct SceneNode SceneNode;

struct SceneNode {
    u16 flags;
    u8 pad_02[0x1e];
    u8 renderObj[0x5c];
    u16 angleY;
    u16 angleX;
    MtxFx43 matrix;
    VecFx32 position;
    void *displayList;
    SceneNode *child;
    SceneNode *next;
    s16 jointId;
    u8 pad_ca[0x32];
    u16 colorScale;
};

typedef struct GeometryGlobalState {
    u8 pad_00[0x94];
    MtxFx33 prmBaseRot;
    VecFx32 prmBaseTrans;
    VecFx32 prmBaseScale;
    u32 prmTexImageParam;
    u32 flag;
} GeometryGlobalState;

extern void NNS_G3dGeBufferOP_N(u32 op, const void *args, u32 numWords);
extern void MTX_RotY33_(MtxFx33 *mtx, fx32 sinVal, fx32 cosVal);
extern void NNS_G3dGlbFlushP(void);
extern void func_01fff67c(int packedRgb);
extern void NNS_G3dDraw(void *renderObj);
extern BOOL NNS_G3dGetResultMtx(void *renderObj, MtxFx43 *pos, MtxFx33 *nrm, u32 nodeID);
extern void ApplyQuaternionCorrectionToMatrix_020c185c(MtxFx33 *mtx);

extern const s16 data_02053580[];
extern GeometryGlobalState NNS_G3dGlb;
extern SceneNode *data_ov099_020c2904;

void DrawViewerSceneNode(SceneNode *node)
{
    SceneNode *child;

    if (node->displayList != NULL) {
        NNS_G3dGeBufferOP_N(0x17, &node->matrix, 0xc);
    } else {
        NNS_G3dGlb.prmBaseScale = node->position;
        if (node->flags & 0x20) {
            int index = node->angleY >> 4;
            MTX_RotY33_((MtxFx33 *)&node->matrix, data_02053580[index],
                                data_02053580[(0x400 - index) & 0xfff]);

            if (node->angleX != 0) {
                fx32 sine;
                fx32 cosine;

                index = node->angleX >> 4;
                cosine = data_02053580[(0x400 - index) & 0xfff];
                sine = data_02053580[index];
                node->matrix._11 = cosine;
                node->matrix._01 = sine;
                node->matrix._10 = (fx32)(((s64)-sine * node->matrix._00) >> 12);
                node->matrix._00 = (fx32)(((s64)cosine * node->matrix._00) >> 12);
                node->matrix._12 = (fx32)(((s64)-sine * node->matrix._02) >> 12);
                node->matrix._02 = (fx32)(((s64)cosine * node->matrix._02) >> 12);
            }
            node->flags &= ~0x20;
        }

        *(MtxFx43 *)&NNS_G3dGlb.prmBaseRot = node->matrix;
        NNS_G3dGlb.flag &= ~0xa4;
        NNS_G3dGlbFlushP();
    }

    if (node->child != NULL) {
        data_ov099_020c2904 = node;
    }

    if (node->flags & 0x40) {
        func_01fff67c(node->colorScale);
    }
    NNS_G3dDraw(node->renderObj);

    child = node->child;
    if (child == NULL) {
        return;
    }

    while (child != NULL) {
        NNS_G3dGetResultMtx(node->renderObj, &child->matrix, NULL, child->jointId);
        ApplyQuaternionCorrectionToMatrix_020c185c((MtxFx33 *)&child->matrix);
        child = child->next;
    }
}
