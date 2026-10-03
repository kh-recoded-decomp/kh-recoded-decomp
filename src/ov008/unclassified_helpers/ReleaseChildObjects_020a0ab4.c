#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x24];
    u32 flags;
    u8 pad_28[0x30];
    u32 attached;
    void *link;
} OwnerBody;

typedef struct {
    u8 pad_00[0x10];
    OwnerBody body;
} OwnerEntry;

typedef struct {
    u8 pad_00[0x10];
    u8 base[1];
} ChildObject;

typedef struct {
    u32 unk_00;
    ChildObject *object;
    u8 pad_08[0x10];
} ChildSlot;

typedef struct {
    u8 pad_00[0xc];
    OwnerEntry *entry;
    u8 pad_10[0x4c];
    void *buffer;
    u8 pad_60[0x8];
    ChildSlot children[24];
} ChildOwner;

extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *ptr);
extern void ActorSlot_Unlink_02035c48(ChildObject *object);
extern void Obj_ShutdownBase_02035554(void *base);
extern void ReleaseOwnerResource_0207f20c(ChildOwner *owner, void *arg);

void ReleaseChildObjects_020a0ab4(ChildOwner *owner, void *arg)
{
    OwnerBody *body = &owner->entry->body;
    int i;

    if (owner->buffer != NULL) {
        if (body->link == NULL) {
            body->flags &= ~1;
        }
        body->attached = 0;
        NNSi_FndFreeFromDefaultHeap_0202a1c4(owner->buffer);
        owner->buffer = NULL;
    }
    for (i = 0; i < 24; i++) {
        ChildSlot *slot = &owner->children[i];

        if (slot->object != NULL) {
            ActorSlot_Unlink_02035c48(slot->object);
            Obj_ShutdownBase_02035554(slot->object->base);
            NNSi_FndFreeFromDefaultHeap_0202a1c4(slot->object);
            slot->object = NULL;
        }
    }
    ReleaseOwnerResource_0207f20c(owner, arg);
}
