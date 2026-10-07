#include "nitro/types.h"

typedef struct ModelNode {
    u8 pad_00[0x78];
    void *resource;
    u8 pad_7c[0x88];
} ModelNode;

typedef struct ModelOwner {
    u8 pad_00[0x84];
    ModelNode nodes[4];
} ModelOwner;

extern void ReleaseResourceAndDetach_0202eee8(ModelNode *node);

#pragma opt_propagation off

void ReleaseAttachedModels_020822ac(ModelOwner *owner)
{
    int i;

    if (owner->nodes[0].resource != NULL) {
        for (i = 0; i < 4; i++) {
            ReleaseResourceAndDetach_0202eee8(&owner->nodes[i]);
        }
    }
}
