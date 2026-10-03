#include "nitro/types.h"

typedef struct Owner {
    u8 pad_00[0x64];
    s16 groupId;
    u8 pad_66[2];
    void *resource;
} Owner;

typedef struct Actor {
    u8 pad_00[4];
    Owner *owner;
    u8 pad_08[0x40];
    void *resource;
} Actor;

void ReleaseResourceAndDetach_0202eee8(void *resource);
void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *ptr);
void func_ov021_020a8a68(int groupId);

void ReleaseOwnerResources_020a272c(Actor *self)
{
    Owner *owner = self->owner;
    if (owner->resource != NULL) {
        ReleaseResourceAndDetach_0202eee8(owner->resource);
        NNSi_FndFreeFromDefaultHeap_0202a1c4(owner->resource);
        owner->resource = NULL;
    }
    if (self->resource != NULL) {
        ReleaseResourceAndDetach_0202eee8(self->resource);
        NNSi_FndFreeFromDefaultHeap_0202a1c4(self->resource);
        self->resource = NULL;
    }
    if (owner->groupId != -1) {
        func_ov021_020a8a68(owner->groupId);
        owner->groupId = -1;
    }
}
