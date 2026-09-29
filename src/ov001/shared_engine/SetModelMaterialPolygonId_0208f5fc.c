#include "nitro/types.h"
#include "nitro/hw.h"
#include "nnsys/g3d.h"

typedef struct ModelInstance {
    u8 pad_00[0x78];
    NNSG3dResMdl *resMdl;
} ModelInstance;

inline void *NNS_G3dGetResDataByIdx(const NNSG3dResDict *dict, u32 idx)
{
    NNSG3dResDictEntryHeader *hdr;
    if (dict != NULL && idx < dict->numEntry) {
        hdr = (NNSG3dResDictEntryHeader *)((u8 *)dict + dict->ofsEntry);
        return (void *)(&hdr->data[0] + hdr->sizeUnit * idx);
    } else {
        return NULL;
    }
}

inline NNSG3dResMat *NNS_G3dGetMat(const NNSG3dResMdl *mdl)
{
    if (mdl && mdl->ofsMat != 0)
        return (NNSG3dResMat *)((u8 *)mdl + mdl->ofsMat);
    else
        return NULL;
}

inline NNSG3dResMatData *NNS_G3dGetMatDataByIdx(const NNSG3dResMat *mat, u32 idx)
{
    NNSG3dResDictMatData *data;
    if (mat) {
        data = (NNSG3dResDictMatData *)NNS_G3dGetResDataByIdx(&mat->dict, idx);
        if (data) {
            return (NNSG3dResMatData *)((u8 *)mat + data->offset);
        }
    }
    return NULL;
}

void SetModelMaterialPolygonId_0208f5fc(ModelInstance *model, u32 matId, int polygonId)
{
    NNSG3dResMdl *resMdl = model->resMdl;
    NNSG3dResMatData *matData;

    if (matId >= resMdl->info.numMat) {
        return;
    }
    matData = NNS_G3dGetMatDataByIdx(NNS_G3dGetMat(resMdl), matId);
    if (matData != NULL) {
        matData->polyAttr = (matData->polyAttr & ~REG_G3_POLYGON_ATTR_ID_MASK) |
                            (polygonId << REG_G3_POLYGON_ATTR_ID_SHIFT);
    }
}
