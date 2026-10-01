#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ResDict {
    u8 revision;
    u8 numEntry;
    u16 sizeDictBlk;
    u16 dummy;
    u16 ofsEntry;
} ResDict;

typedef struct ResDictEntryHeader {
    u16 sizeUnit;
    u16 sizeName;
    u8 data[4];
} ResDictEntryHeader;

typedef struct ResMdlSet {
    u32 header[2];
    ResDict dict;
} ResMdlSet;

typedef struct ModelResList {
    u8 pad_00[8];
    void *texSet;
} ModelResList;

typedef struct ModelInstance {
    u16 flags;
    s16 animId[5];
    void *anim[5];
    u8 renderObj[0x54];
    ModelResList *resList;
    void *resMdl;
    u16 frame;
    u16 frameSpeed;
    fx32 rotation[9];
    VecFx32 translation;
    VecFx32 scale;
    VecFx32 offset;
    s16 jointId;
    s16 animSlot;
    u8 pad_cc[4];
    int userA;
    int userB;
    u8 animBlock[0xc];
    int animCount;
} ModelInstance;

extern void func_0202c690(int useDefault);
extern void *func_0202c940(ModelResList *list, int texFlag, int fileId);
extern void func_0202d3fc(void *file, void *texSet, int texSource);
extern void *func_0202d3e0(void *archive, int memberIndex, int subIndex);
extern ResMdlSet *NNS_G3dGetMdlSet_0201ac60(void *header);
extern void InitializeRenderObject_020185ec(void *renderObj, void *resMdl);
extern void BindModelAnimations_0202e854(void *animBlock, ModelInstance *inst, void *archive, int texSource);
extern void func_01ff90ec(fx32 *matrix);

static inline void *GetResDataByIdx(const ResDict *dict, u32 idx)
{
    if (dict != 0 && idx < dict->numEntry) {
        const ResDictEntryHeader *hdr = (const ResDictEntryHeader *)((u8 *)dict + dict->ofsEntry);
        return (void *)&hdr->data[idx * hdr->sizeUnit];
    }
    return 0;
}

static inline void *GetMdlByIdx(const ResMdlSet *mdlSet, u32 idx)
{
    if (mdlSet) {
        const u32 *data = GetResDataByIdx(&mdlSet->dict, idx);
        if (data) {
            return (u8 *)mdlSet + *data;
        }
    }
    return 0;
}

BOOL InitModelInstance_0202eb84(ModelInstance *inst, int texFlag, int hasTexSource, int fileId, int texSource)
{
    void *file;
    int i;

    if (texFlag != 0 || (hasTexSource != 0 && fileId != 0)) {
        func_0202c690(0);
    }
    file = func_0202c940(inst->resList, texFlag, fileId);
    if (texFlag == 0) {
        if (hasTexSource != 0) {
            if (fileId != 0) {
                func_0202c690(1);
            }
            func_0202d3fc(file, inst->resList->texSet, texSource);
        }
    } else {
        func_0202c690(1);
    }
    inst->resMdl = GetMdlByIdx(NNS_G3dGetMdlSet_0201ac60(func_0202d3e0(file, 7, 0)), 0);
    InitializeRenderObject_020185ec(inst->renderObj, inst->resMdl);
    inst->animCount = 0;
    BindModelAnimations_0202e854(inst->animBlock, inst, file, texSource);
    for (i = 0; i < 5; i++) {
        inst->animId[i] = -1;
        inst->anim[i] = 0;
    }
    inst->animSlot = -1;
    inst->frame = 0;
    inst->frameSpeed = 0;
    func_01ff90ec(inst->rotation);
    inst->translation.x = inst->translation.y = inst->translation.z = 0;
    inst->scale.x = inst->scale.y = inst->scale.z = 0x1000;
    inst->flags = 0;
    inst->offset.x = inst->offset.y = inst->offset.z = 0;
    inst->jointId = -1;
    inst->userA = 0;
    inst->userB = 0;
    return TRUE;
}
