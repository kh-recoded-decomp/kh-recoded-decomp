#include "nitro/types.h"
#include "nnsys/g3d.h"

static inline void *GetResDataByIdx(const NNSG3dResDict *dict, u32 idx)
{
    NNSG3dResDictEntryHeader *hdr;
    if (dict != NULL && idx < dict->numEntry) {
        hdr = (NNSG3dResDictEntryHeader *)((u8 *)dict + dict->ofsEntry);
        return (void *)(&hdr->data[0] + hdr->sizeUnit * idx);
    } else {
        return NULL;
    }
}

static inline NNSG3dResMat *GetMat(const NNSG3dResMdl *mdl)
{
    if (mdl && mdl->ofsMat != 0)
        return (NNSG3dResMat *)((u8 *)mdl + mdl->ofsMat);
    else
        return NULL;
}

static inline NNSG3dResMatData *GetMatDataByIdx(const NNSG3dResMat *mat, u32 idx)
{
    NNSG3dResDictMatData *data;
    if (mat) {
        data = (NNSG3dResDictMatData *)GetResDataByIdx(&mat->dict, idx);
        if (data) {
            return (NNSG3dResMatData *)((u8 *)mat + data->offset);
        }
    }
    return NULL;
}

void SetAllMaterialsPolyAttrMask_0201a3c4(NNSG3dResMdl *mdl, BOOL enable, u32 mask)
{
    u32 numMat = mdl->info.numMat;
    NNSG3dResMat *mat = GetMat(mdl);
    u32 matID;

    for (matID = 0; matID < numMat; matID++) {
        NNSG3dResMatData *data = GetMatDataByIdx(mat, matID);
        if (enable) {
            data->polyAttrMask |= mask;
        } else {
            data->polyAttrMask &= ~mask;
        }
    }
}
