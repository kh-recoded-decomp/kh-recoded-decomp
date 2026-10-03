#include "nitro/types.h"

typedef struct {
    u32 flags;
    u8 anim[4];
} BodyModel;

typedef struct {
    u8 pad0[0x230];
    BodyModel *body;
    u8 pad234[0x874 - 0x234];
    u8 stateMachine[0x9ac - 0x874];
    u64 flags;
} Actor;

extern void func_0202f4d8(void *anim);
extern void func_0202f4e8(void *anim);
extern void SetPaused_020aca0c(void *obj, int paused);
extern void SetObjectAnimationEnabled_020a9d28(void *obj, int enabled);

void SetActorPaused_020d12f0(Actor *actor, int paused)
{
    int i;
    if (paused) {
        if (!(actor->body->flags & 0x20)) {
            func_0202f4d8(actor->body->anim);
        }
        actor->flags |= 0x200;
    } else {
        if (!(actor->body->flags & 0x20)) {
            func_0202f4e8(actor->body->anim);
        }
        actor->flags &= ~(u64)0x200;
    }
    SetPaused_020aca0c(actor->stateMachine, paused);
    for (i = 0; i < 2; i++) {
        SetObjectAnimationEnabled_020a9d28((u8 *)actor + 0xb68 + i * 0x230, paused);
    }
}
