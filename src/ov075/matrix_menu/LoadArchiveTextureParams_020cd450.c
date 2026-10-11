#include "nitro/types.h"
#include "nnsys/g3d.h"

typedef struct TextureDrawParams {
    u16 width;
    u16 height;
    u32 imageParam;
    u32 paletteBase;
} TextureDrawParams;

extern void *func_0202c48c(u32 fileId, u32 mode);
extern s32 func_0202d098(void *resource, void *heap);
extern NNSG3dResTex *FindTextureResourceBlock_0201ac70(const void *header);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);

static inline void *GetResDataByIdx(const NNSG3dResDict *dict, u32 idx)
{
    const NNSG3dResDictEntryHeader *entries;

    if (dict != NULL && idx < dict->numEntry) {
        entries = (const NNSG3dResDictEntryHeader *)((u8 *)dict + dict->ofsEntry);
        return (void *)((u8 *)entries->data + entries->sizeUnit * idx);
    }
    return NULL;
}

static inline const NNSG3dResDictTexData *GetTexDataByIdx(const NNSG3dResTex *tex, u32 idx)
{
    if (tex != NULL) {
        return GetResDataByIdx(&tex->dict, idx);
    }
    return NULL;
}

static inline BOOL DictHasIndex(const NNSG3dResDict *dict, u32 idx)
{
    return idx < dict->numEntry;
}

void LoadArchiveTextureParams_020cd450(int archive, u32 index, TextureDrawParams *params)
{
    void *file;
    const NNSG3dResDictTexData *texData;
    const NNSG3dResDictPlttData *plttData;
    u32 plttKey;
    u32 plttOffset;
    NNSG3dResTex *tex;
    u32 texKey;
    const NNSG3dResDict *dict;
    const NNSG3dResDictEntryHeader *entries;

    file = func_0202c48c(0x80000000 | (((archive + 0x8000) & 0xfffffc) << 7) | (index & 0x1ff), 0xe);
    func_0202d098(file, NULL);
    tex = FindTextureResourceBlock_0201ac70(file);
    texData = GetTexDataByIdx(tex, 0);
    if (tex != NULL && tex->plttInfo.ofsDict != 0) {
        dict = (const NNSG3dResDict *)((u8 *)tex + tex->plttInfo.ofsDict);
        if (dict != NULL && DictHasIndex(dict, 0)) {
            entries = (const NNSG3dResDictEntryHeader *)((u8 *)dict + dict->ofsEntry);
            plttData = (const NNSG3dResDictPlttData *)entries->data;
        } else {
            plttData = NULL;
        }
    } else {
        plttData = NULL;
    }
    plttOffset = plttData->offset;
    plttKey = (u16)tex->plttInfo.vramKey;
    if ((u8)((texData->texImageParam & 0x1c000000) >> 26) == 5) {
        texKey = (u16)tex->tex4x4Info.vramKey;
    } else {
        texKey = (u16)tex->texInfo.vramKey;
    }
    if ((plttData->flag & 1) == 0) {
        plttOffset = (plttOffset << 15) >> 16;
        plttKey = (plttKey << 15) >> 16;
    }
    params->width = texData->extraParam & 0x7ff;
    params->height = (texData->extraParam >> 11) & 0x7ff;
    params->imageParam = (texData->texImageParam + texKey) | 0x20000000;
    params->paletteBase = (u16)(plttOffset + plttKey);
    NNSi_FndFreeFromDefaultHeap_0202a1c4(file);
}
