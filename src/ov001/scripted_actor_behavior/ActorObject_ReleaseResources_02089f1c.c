#include "nitro/types.h"

typedef void (*ActorCallback)(u8 *actor, int arg1, int arg2);

extern void ZeroHalfThenFree_0202cd78(void *block);
extern void ActorSlot_UnlinkByIndex_02035c28(int index);
extern void func_ov001_02088b58(u8 *work);
extern void ClearSbcCallback_020188b8(void *model);
extern u8 *GetBoundedEntryField_0206db5c(int index);
extern int func_ov001_02063a38(void);
extern void Actor_InitNodeCaptureCallback_020cd254(u8 *actor);
extern void func_ov052_020d071c(u8 *actor);
extern void CommitPendingAnimationSwap_0202f5c8(void *anim);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);
extern void func_0202eaf4(void *resource);
extern int func_02036810(int index);
extern int func_02036588(int index);
extern void func_020367d0(int index, int value);
extern void Obj_ConditionalShutdown_020368c8(void *object, int index);
extern void ReleaseResourceAndDetach_0202eee8(void *object);

typedef struct {
    s16 id;
    u8 pad[0x2a];
} SlotEntry;

typedef struct {
    u8 pad0[0xd4];
    SlotEntry slots[6][5];
} SlotWork;

void ActorObject_ReleaseResources_02089f1c(u8 *work)
{
    int i;
    int j;
    u8 *actor;
    u8 *model;
    ActorCallback callback;

    if (*(void **)(work + 0xd20) != NULL) {
        ZeroHalfThenFree_0202cd78(*(void **)(work + 0xd20));
        *(void **)(work + 0xd20) = NULL;
    }
    if (*(u32 *)(work + 0xef4) == 0) {
        return;
    }
    if (*(u32 *)(work + 0xef4) & 0x200) {
        for (i = 0; i < 6; i++) {
            for (j = 0; j < 5; j++) {
                if (((SlotWork *)work)->slots[i][j].id == -2) {
                    ActorSlot_UnlinkByIndex_02035c28((u16)*(u32 *)(work + 0xf00));
                    goto done_search;
                }
            }
        }
    }
done_search:
    if (!(*(u32 *)(work + 0xef4) & 0x4000)) {
        func_ov001_02088b58(work);
        if (**(u8 ***)(work + 0xd18) != NULL) {
            ClearSbcCallback_020188b8(**(u8 ***)(work + 0xd18) + 0x24);
            if (*(int *)(work + 0xf00) < 3) {
                actor = GetBoundedEntryField_0206db5c(*(int *)(work + 0xf00));
                if (func_ov001_02063a38() == 7) {
                    Actor_InitNodeCaptureCallback_020cd254(actor);
                    if (*(int *)(actor + 0x75c) == 0x12) {
                        callback = *(ActorCallback *)(actor + 0x1f8);
                        if (callback != NULL) {
                            callback(actor, 0, 0);
                        }
                    }
                } else {
                    func_ov052_020d071c(actor);
                    model = **(u8 ***)(work + 0xd18);
                    if (*(u16 *)(model + 4) & 4) {
                        CommitPendingAnimationSwap_0202f5c8(model + 4);
                    }
                    if ((*(u64 *)(actor + 0x9ac) & 0x800) == 0 && *(int *)(actor + 0x75c) != 0) {
                        callback = *(ActorCallback *)(actor + 0x1f8);
                        if (callback != NULL) {
                            callback(actor, 0, 0);
                        }
                    }
                }
            }
        }
    }
    if (!(*(u32 *)(work + 0xef4) & 0x4000) && !(*(u32 *)(work + 0xef4) & 0x8000)) {
        NNSi_FndFreeFromDefaultHeap_0202a1c4(*(void **)(work + 0xd18));
        *(void **)(work + 0xd18) = NULL;
    }
    if (*(u8 **)(work + 0xd1c) != NULL) {
        for (i = 0; i < 5; i++) {
            u8 *resource = *(u8 **)(work + 0xd1c) + i * 0x24;
            if (*(int *)(resource + 0xc) != 0) {
                func_0202eaf4(resource);
            }
        }
        NNSi_FndFreeFromDefaultHeap_0202a1c4(*(void **)(work + 0xd1c));
        *(void **)(work + 0xd1c) = NULL;
    }
    if (func_02036810((u16)*(u32 *)(work + 0xf00))) {
        if (func_02036588((u16)*(u32 *)(work + 0xf00))) {
            func_020367d0((u16)*(u32 *)(work + 0xf00), 0x1000);
        }
        if (!(*(u32 *)(work + 0xef4) & 0x10000)) {
            Obj_ConditionalShutdown_020368c8(work + 0xd24, (u16)*(u32 *)(work + 0xf00));
        }
    }
    if (*(int *)(work + 0xc78) != 0) {
        ReleaseResourceAndDetach_0202eee8(work + 0xc04);
    }
    *(u32 *)(work + 0xef4) = 0;
}
