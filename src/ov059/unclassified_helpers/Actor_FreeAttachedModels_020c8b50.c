#include "nitro/types.h"

typedef struct AttachedModel {
    u8 data[0x104];
} AttachedModel;

typedef struct Actor {
    u8 pad_0000[0x1700];
    AttachedModel *attachedModels;
} Actor;

extern void ReleaseResourceAndDetach_0202eee8(AttachedModel *model);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);

void Actor_FreeAttachedModels_020c8b50(Actor *actor)
{
    int i;

    for (i = 0; i < 4; i++) {
        ReleaseResourceAndDetach_0202eee8(&actor->attachedModels[i]);
    }
    NNSi_FndFreeFromDefaultHeap_0202a1c4(actor->attachedModels);
}
