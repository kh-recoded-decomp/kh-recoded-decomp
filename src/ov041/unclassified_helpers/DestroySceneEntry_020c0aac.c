#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x1d0];
    u8 recordSlot;
} LinkedActor;

typedef struct {
    u8 kind;
    u8 pad_001[0x10b];
    void *buffer;
    u8 pad_110[0x4c];
    u8 actorSlot[0x1d0];
    u8 recordSlot;
    u8 pad_32d[3];
    u32 *heapHandle;
    void *linkedObject;
    u8 pad_338[0x17c];
} SceneEntry;

typedef struct {
    u8 pad_000[0x14];
    SceneEntry *entries;
    u8 pad_018[0xe0];
    u8 actorSlot[0x1d0];
    u8 recordSlot;
    u8 pad_2c9[0x3b];
    u32 heapHandle;
    u8 pad_308[0x44];
    LinkedActor *mainActor;
    LinkedActor *subActor;
} Work;

extern int data_ov035_020bc4e0;
extern void ActorSlot_Unlink_02035c48(void *slot);
extern void func_020368a4(int slot);
extern void ZeroHalfThenFree_0202cd78(u32 value);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);
extern void Obj_ConditionalShutdown_020368c8(void *object, int mask);
extern void DestroyDisplayObject_020c37b4(SceneEntry *entry);
extern void ReleaseEmbeddedObject_020c277c(SceneEntry *entry);

void DestroySceneEntry_020c0aac(int index) {
    SceneEntry *entry;
    Work *work;

    work = *(Work **)(data_ov035_020bc4e0 + 0xb8);
    entry = &work->entries[index];

    if (entry->kind == 0xff) {
        ActorSlot_Unlink_02035c48(work->actorSlot);
        func_020368a4(work->recordSlot);
        ZeroHalfThenFree_0202cd78(work->heapHandle);
        ActorSlot_Unlink_02035c48(work->mainActor);
        func_020368a4(work->mainActor->recordSlot);
        NNSi_FndFreeFromDefaultHeap_0202a1c4(work->mainActor);
    }
    if (entry->kind == 0xfd) {
        ActorSlot_Unlink_02035c48(work->subActor);
        func_020368a4(work->subActor->recordSlot);
        NNSi_FndFreeFromDefaultHeap_0202a1c4(work->subActor);
    }
    if (entry->linkedObject != NULL) {
        ActorSlot_Unlink_02035c48(entry->linkedObject);
        Obj_ConditionalShutdown_020368c8(entry->linkedObject, 0xffff);
        NNSi_FndFreeFromDefaultHeap_0202a1c4(entry->linkedObject);
    }
    ActorSlot_Unlink_02035c48(entry->actorSlot);
    func_020368a4(entry->recordSlot);
    if (entry->kind >= 0x1b) {
        ZeroHalfThenFree_0202cd78(*entry->heapHandle);
        NNSi_FndFreeFromDefaultHeap_0202a1c4(entry->heapHandle);
        entry->heapHandle = NULL;
    }
    if (entry->buffer != NULL) {
        NNSi_FndFreeFromDefaultHeap_0202a1c4(entry->buffer);
        entry->buffer = NULL;
    }
    DestroyDisplayObject_020c37b4(entry);
    ReleaseEmbeddedObject_020c277c(entry);
}
