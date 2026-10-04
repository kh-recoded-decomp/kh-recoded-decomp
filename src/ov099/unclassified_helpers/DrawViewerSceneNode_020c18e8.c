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

typedef struct GeometryCommandCache {
    u8 pad_00[0xd4];
    u32 flags;
} GeometryCommandCache;

extern void QueueOrSendGeometryCommand_01ffa37c(u32 op, const void *args, u32 numWords);
extern void MTX_RotY33_01ff923c(MtxFx33 *mtx, fx32 sinVal, fx32 cosVal);
extern void func_02019188(void);
extern void setMaterialColorScale_01fff67c(int packedRgb);
extern void func_01ffe1bc(void *renderObj);
extern BOOL RestoreNodeGeometryMatrix_02019d8c(void *renderObj, MtxFx43 *pos, MtxFx33 *nrm, u32 nodeID);
extern void ApplyQuaternionCorrectionToMatrix_020c183c(MtxFx33 *mtx);

extern VecFx32 data_0205a9e8;
extern const s16 data_0205356c[];
extern MtxFx43 data_0205a9b8;
extern GeometryCommandCache data_0205a924;
extern SceneNode *data_ov099_020c28e4;

void DrawViewerSceneNode_020c18e8(SceneNode *node)
{
    SceneNode *child;

    if (node->displayList != NULL) {
        QueueOrSendGeometryCommand_01ffa37c(0x17, &node->matrix, 0xc);
    } else {
        data_0205a9e8 = node->position;
        if (node->flags & 0x20) {
            int index = node->angleY >> 4;
            MTX_RotY33_01ff923c((MtxFx33 *)&node->matrix, data_0205356c[index],
                                data_0205356c[(0x400 - index) & 0xfff]);

            if (node->angleX != 0) {
                fx32 sine;
                fx32 cosine;

                index = node->angleX >> 4;
                cosine = data_0205356c[(0x400 - index) & 0xfff];
                sine = data_0205356c[index];
                node->matrix._11 = cosine;
                node->matrix._01 = sine;
                node->matrix._10 = (fx32)(((s64)-sine * node->matrix._00) >> 12);
                node->matrix._00 = (fx32)(((s64)cosine * node->matrix._00) >> 12);
                node->matrix._12 = (fx32)(((s64)-sine * node->matrix._02) >> 12);
                node->matrix._02 = (fx32)(((s64)cosine * node->matrix._02) >> 12);
            }
            node->flags &= ~0x20;
        }

        data_0205a9b8 = node->matrix;
        data_0205a924.flags &= ~0xa4;
        func_02019188();
    }

    if (node->child != NULL) {
        data_ov099_020c28e4 = node;
    }

    if (node->flags & 0x40) {
        setMaterialColorScale_01fff67c(node->colorScale);
    }
    func_01ffe1bc(node->renderObj);

    child = node->child;
    if (child == NULL) {
        return;
    }

    while (child != NULL) {
        RestoreNodeGeometryMatrix_02019d8c(node->renderObj, &child->matrix, NULL, child->jointId);
        ApplyQuaternionCorrectionToMatrix_020c183c((MtxFx33 *)&child->matrix);
        child = child->next;
    }
}
