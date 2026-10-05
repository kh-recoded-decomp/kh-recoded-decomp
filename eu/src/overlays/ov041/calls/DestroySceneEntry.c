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
extern void ActorSlot_Unlink(void *slot);
extern void ShutdownRecordSlotByIndex(int slot);
extern void ZeroHalfThenFree(u32 value);
extern void NNSi_FndFreeFromDefaultHeap(void *block);
extern void Obj_ConditionalShutdown(void *object, int mask);
extern void DestroyDisplayObject(SceneEntry *entry);
extern void ReleaseEmbeddedObject(SceneEntry *entry);

void DestroySceneEntry(int index) {
    SceneEntry *entry;
    Work *work;

    work = *(Work **)(data_ov035_020bc4e0 + 0xb8);
    entry = &work->entries[index];

    if (entry->kind == 0xff) {
        ActorSlot_Unlink(work->actorSlot);
        ShutdownRecordSlotByIndex(work->recordSlot);
        ZeroHalfThenFree(work->heapHandle);
        ActorSlot_Unlink(work->mainActor);
        ShutdownRecordSlotByIndex(work->mainActor->recordSlot);
        NNSi_FndFreeFromDefaultHeap(work->mainActor);
    }
    if (entry->kind == 0xfd) {
        ActorSlot_Unlink(work->subActor);
        ShutdownRecordSlotByIndex(work->subActor->recordSlot);
        NNSi_FndFreeFromDefaultHeap(work->subActor);
    }
    if (entry->linkedObject != NULL) {
        ActorSlot_Unlink(entry->linkedObject);
        Obj_ConditionalShutdown(entry->linkedObject, 0xffff);
        NNSi_FndFreeFromDefaultHeap(entry->linkedObject);
    }
    ActorSlot_Unlink(entry->actorSlot);
    ShutdownRecordSlotByIndex(entry->recordSlot);
    if (entry->kind >= 0x1b) {
        ZeroHalfThenFree(*entry->heapHandle);
        NNSi_FndFreeFromDefaultHeap(entry->heapHandle);
        entry->heapHandle = NULL;
    }
    if (entry->buffer != NULL) {
        NNSi_FndFreeFromDefaultHeap(entry->buffer);
        entry->buffer = NULL;
    }
    DestroyDisplayObject(entry);
    ReleaseEmbeddedObject(entry);
}
