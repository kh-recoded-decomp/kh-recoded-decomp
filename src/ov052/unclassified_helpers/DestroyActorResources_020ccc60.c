#include "nitro/types.h"

typedef struct {
    u32 flags;
    u8 pad_04[0x30];
    int pending;
    int active;
} RenderState;

typedef struct {
    u8 pad_00[0x24];
    RenderState render;
} ActorModel;

typedef struct {
    u8 pad_000[0x230];
    ActorModel *model;
    u8 pad_234[0x694 - 0x234];
    u8 record[0x6b8 - 0x694];
    void *buffer;
    u8 pad_6bc[0x76c - 0x6bc];
    u8 sharedStates[6][0x2c];
    u8 animSelector[0xb2c - 0x874];
    u8 recordLists[0xb68 - 0xb2c];
    u8 parts[2][0x230];
} ActorBase;

extern void ClearSbcCallback_020188b8(RenderState *render);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);
extern void ReleaseSharedRecordState_020a9084(void *state);
extern void ReleaseEffectBank_020aa1f4(void *bank);
extern void ReleaseModelSet_020a9928(void *part);
extern void FreeEntriesAndStateLists_020ad600(void *container);
extern void FreeRecordListsAndBuffer_020a7f00(void *lists);
extern void ReleaseResourceSlotArray_020ca2e4(ActorBase *actor, void *block);
extern void TeardownBigObj_020ac8cc(void *selector);
extern void func_02036b7c(void *record);
extern void ReleaseBigObj_020ab7b0(void *object);
extern void func_020368a4(int index);

void DestroyActorResources_020ccc60(ActorBase *actor)
{
    RenderState *render;
    int i;

    ClearSbcCallback_020188b8(&actor->model->render);
    render = &actor->model->render;
    if (render->active == 0) {
        render->flags &= ~1;
    }
    render->pending = 0;
    NNSi_FndFreeFromDefaultHeap_0202a1c4(actor->buffer);
    for (i = 0; i < 6; i++) {
        ReleaseSharedRecordState_020a9084(actor->sharedStates[i]);
    }
    ReleaseEffectBank_020aa1f4((u8 *)actor + 0xfc8);
    for (i = 0; i < 2; i++) {
        ReleaseModelSet_020a9928(actor->parts[i]);
    }
    FreeEntriesAndStateLists_020ad600((u8 *)actor + 0x1070);
    FreeRecordListsAndBuffer_020a7f00(actor->recordLists);
    ReleaseResourceSlotArray_020ca2e4(actor, (u8 *)actor + 0x105c);
    TeardownBigObj_020ac8cc(actor->animSelector);
    func_02036b7c(actor->record);
    ReleaseBigObj_020ab7b0((u8 *)actor + 0x1108);
    func_020368a4(*((u8 *)actor + 0x9b4));
}
