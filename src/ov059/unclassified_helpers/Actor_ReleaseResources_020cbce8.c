#include "nitro/types.h"

typedef struct {
    u32 flags;
    u8 pad_04[0x34 - 0x04];
    s32 callbackTiming;
    void *callback;
} RenderObj;

typedef struct {
    u8 pad_00[0x24];
    RenderObj renderObj;
} ModelState;

typedef struct {
    u8 bytes[0x2c];
} SharedRecord;

typedef struct {
    u8 bytes[0x230];
} ModelSet;

typedef struct {
    u8 pad_0000[0x230];
    ModelState *model;
    u8 pad_0234[0x694 - 0x234];
    u8 stepState[0x6b8 - 0x694];
    void *workBuffer;
    u8 pad_06bc[0x76c - 0x6bc];
    SharedRecord records[3];
    u8 bigObj[0x930 - 0x7f0];
    u8 recordSlot;
    u8 pad_0931[0x998 - 0x931];
    u8 recordLists[0x9d4 - 0x998];
    ModelSet modelSets[2];
    u8 effectBank[0xec4 - 0xe34];
    u8 effectSet[0x1524 - 0xec4];
    u8 bufferSlots[0x16f0 - 0x1524];
    u8 attachedModels[0x1744 - 0x16f0];
    void *extraBuffer;
    u8 pad_1748[0x1824 - 0x1748];
    void *halfBuffer;
} Actor;

extern void ClearSbcCallback_020188b8(void *renderObj);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);
extern void ReleaseSharedRecordState_020a9084(void *record);
extern void ReleaseEffectBank_020aa1f4(void *bank);
extern void ReleaseModelSet_020a9928(void *set);
extern void EffectSet_Release_020cf1d8(void *set);
extern void BufferSlotSet_FreeAll_020cf9d0(void *slots);
extern void FreeRecordListsAndBuffer_020a7f00(void *lists);
extern void Actor_FreeAttachedModels_020c8b50(Actor *actor, void *models);
extern void TeardownBigObj_020ac8cc(void *obj);
extern int func_02036b7c(void *state);
extern void func_020368a4(int slot);
extern void DestroyAllPools_020a892c(void);
extern int ZeroHalfThenFree_0202cd78(void *buffer);
extern void RemoveTaggedListEntries_0206c720(void *tag);
extern void func_ov059_020cbe80(void);

void Actor_ReleaseResources_020cbce8(Actor *actor)
{
    RenderObj *renderObj;
    int i;

    ClearSbcCallback_020188b8(&actor->model->renderObj);
    renderObj = &actor->model->renderObj;
    if (renderObj->callback == NULL) {
        renderObj->flags &= ~1;
    }
    renderObj->callbackTiming = 0;
    NNSi_FndFreeFromDefaultHeap_0202a1c4(actor->workBuffer);
    for (i = 0; i < 3; i++) {
        ReleaseSharedRecordState_020a9084(&actor->records[i]);
    }
    ReleaseEffectBank_020aa1f4(actor->effectBank);
    for (i = 0; i < 2; i++) {
        ReleaseModelSet_020a9928(&actor->modelSets[i]);
    }
    EffectSet_Release_020cf1d8(actor->effectSet);
    BufferSlotSet_FreeAll_020cf9d0(actor->bufferSlots);
    FreeRecordListsAndBuffer_020a7f00(actor->recordLists);
    Actor_FreeAttachedModels_020c8b50(actor, actor->attachedModels);
    NNSi_FndFreeFromDefaultHeap_0202a1c4(actor->extraBuffer);
    TeardownBigObj_020ac8cc(actor->bigObj);
    func_02036b7c(actor->stepState);
    func_020368a4(actor->recordSlot);
    DestroyAllPools_020a892c();
    ZeroHalfThenFree_0202cd78(actor->halfBuffer);
    RemoveTaggedListEntries_0206c720(func_ov059_020cbe80);
}
