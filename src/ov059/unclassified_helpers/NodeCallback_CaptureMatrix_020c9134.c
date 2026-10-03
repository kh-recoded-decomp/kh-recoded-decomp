#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x2c];
    void *actor;
} RenderOwner;

typedef struct {
    u8 pad_00[4];
    RenderOwner *owner;
} RenderContext;

extern void Actor_CaptureNodeMatrix_020cd280(void *actor, RenderContext *renderState);

void NodeCallback_CaptureMatrix_020c9134(RenderContext *context)
{
    Actor_CaptureNodeMatrix_020cd280(context->owner->actor, context);
}
