#pragma opt_propagation off
#include "nitro/types.h"

typedef struct ResDict {
    u8 revision;
    u8 numEntry;
    u16 sizeDictBlk;
    u16 dummy;
    u16 ofsEntry;
} ResDict;

typedef struct ResTex {
    u8 pad_00[8];
    u32 texVramKey;
    u8 pad_0c[0x20];
    u32 plttVramKey;
    u8 pad_30[4];
    u16 ofsPlttDict;
    u8 pad_36[6];
    ResDict texDict;
} ResTex;

typedef struct TexImageEntry {
    u32 texImageParam;
    u32 extraParam;
} TexImageEntry;

typedef struct ModelResource {
    u8 pad_00[0x10];
    ResTex *texture;
} ModelResource;

typedef struct ModelDrawObject {
    u8 pad_00[0x74];
    ModelResource *resource;
} ModelDrawObject;

extern void QueueOrSendGeometryCommand_01ffa37c(u32 op, const void *args, u32 numWords);

static inline const TexImageEntry *GetTexDataByIdx(const ResTex *tex, u32 index) {
    const ResDict *dict = &tex->texDict;
    if (dict != NULL) {
        if (index < tex->texDict.numEntry) {
            return (const TexImageEntry *)((const u8 *)dict + tex->texDict.ofsEntry + 4);
        }
    }
    return NULL;
}

static inline const u16 *GetPlttDataByIdx(const ResDict *dict, u32 index) {
    if (dict != NULL) {
        if (index < dict->numEntry) {
            dict = (const ResDict *)((const u8 *)dict + dict->ofsEntry + 4);
            return (const u16 *)dict;
        }
    }
    return NULL;
}

void SetModelFirstTexture_01fff8b0(ModelDrawObject *object, s32 *width, s32 *height) {
    ResTex *tex = object->resource->texture;
    const TexImageEntry *texEntry;
    u32 pltt;
    u32 params[2];
    u32 plttBase;
    u32 texParam;
    u32 plttKey;

    if (tex != NULL) {
        texEntry = GetTexDataByIdx(tex, 0);
    } else {
        texEntry = NULL;
    }
    if (tex != NULL && tex->ofsPlttDict != 0) {
        pltt = (u32)GetPlttDataByIdx((const ResDict *)((const u8 *)tex + tex->ofsPlttDict), 0);
    } else {
        pltt = 0;
    }
    pltt = *(const u16 *)pltt;
    plttKey = (u16)tex->plttVramKey;
    texParam = (texEntry->texImageParam + (u16)tex->texVramKey) | 0x30000;
    plttBase = (u16)((pltt >> 1) + (plttKey >> 1));
    params[1] = plttBase;
    params[0] = texParam;
    *width = (texEntry->extraParam & 0x7ff) << 12;
    *height = ((texEntry->extraParam >> 11) & 0x7ff) << 12;
    QueueOrSendGeometryCommand_01ffa37c(0x2b2a, params, 2);
}
