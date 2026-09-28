#include "nitro/types.h"

typedef struct {
    void *headObject;
    void *tailObject;
    u16 objectCount;
    u16 linkOffset;
} ObjectList;

typedef struct {
    void *state;
    u8 pad_04[4];
    u32 ownsState;
} SingleStateNode;

typedef struct {
    u8 pad_00[8];
    u32 ownsState;
    void *primaryState;
    void *secondaryState;
} DualStateNode;

typedef struct {
    void **entries;
    s32 entryCount;
    u8 pad_08[8];
    s32 overlayId;
    s32 entryContext;
    u8 pad_18[0x34];
    ObjectList singleStateList;
    ObjectList dualStateList;
} EntryOwner;

extern void *NNS_FndGetNextListObject_02012a38(ObjectList *list, void *object);
extern void RemoveIntrusiveListObject_020129d8(ObjectList *list, void *object);
extern void func_02029f98(s32 processor, s32 overlayId);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);
extern void ReleaseSharedRecordState_020a9084(void *state);
extern void func_ov021_020acd8c(void *entry, s32 context);

void FreeEntriesAndStateLists_020ad600(EntryOwner *owner)
{
    s32 i;
    SingleStateNode *single;
    SingleStateNode *nextSingle;
    DualStateNode *dual;
    DualStateNode *nextDual;

    if (owner->entryCount <= 0) {
        return;
    }
    for (i = 0; i < owner->entryCount; i++) {
        if (owner->entries[i] != NULL) {
            func_ov021_020acd8c(owner->entries[i], owner->entryContext);
            NNSi_FndFreeFromDefaultHeap_0202a1c4(owner->entries[i]);
        }
    }
    NNSi_FndFreeFromDefaultHeap_0202a1c4(owner->entries);
    if (owner->overlayId != -1) {
        func_02029f98(0, owner->overlayId);
        owner->overlayId = -1;
    }

    single = NNS_FndGetNextListObject_02012a38(&owner->singleStateList, NULL);
    while (single != NULL) {
        nextSingle = NNS_FndGetNextListObject_02012a38(&owner->singleStateList, single);
        if (single->ownsState != 0) {
            ReleaseSharedRecordState_020a9084(single->state);
            NNSi_FndFreeFromDefaultHeap_0202a1c4(single->state);
        }
        RemoveIntrusiveListObject_020129d8(&owner->singleStateList, single);
        NNSi_FndFreeFromDefaultHeap_0202a1c4(single);
        single = nextSingle;
    }

    dual = NNS_FndGetNextListObject_02012a38(&owner->dualStateList, NULL);
    while (dual != NULL) {
        nextDual = NNS_FndGetNextListObject_02012a38(&owner->dualStateList, dual);
        if (dual->ownsState != 0) {
            ReleaseSharedRecordState_020a9084(dual->primaryState);
            NNSi_FndFreeFromDefaultHeap_0202a1c4(dual->primaryState);
            if (dual->secondaryState != NULL) {
                ReleaseSharedRecordState_020a9084(dual->secondaryState);
                NNSi_FndFreeFromDefaultHeap_0202a1c4(dual->secondaryState);
            }
        }
        RemoveIntrusiveListObject_020129d8(&owner->dualStateList, dual);
        NNSi_FndFreeFromDefaultHeap_0202a1c4(dual);
        dual = nextDual;
    }
}
