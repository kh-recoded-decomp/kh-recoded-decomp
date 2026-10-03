#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct FallActor FallActor;
typedef void (*ActorEventFunc)(FallActor *actor, int event);
typedef void (*ActorModeFunc)(FallActor *actor, int mode, int arg);
typedef void (*ActorScaleFunc)(FallActor *actor, fx32 scale);
typedef void (*StateHandler)(void);

struct FallActor {
    u8 pad_000[0x1f8];
    ActorModeFunc onMode;
    ActorScaleFunc onScale;
    u8 pad_200[0x234 - 0x200];
    u32 modelFlags;
    u8 pad_238[0x9ac - 0x238];
    u64 stateFlags;
    u8 pad_9b4[0x9cc - 0x9b4];
    fx32 velocityY;
    u8 pad_9d0[0x10ec - 0x9d0];
    ActorEventFunc onEvent;
};

extern BOOL func_ov052_020d10f0(FallActor *actor);
extern void func_ov052_020d083c(void);
extern void func_ov052_020d0df0(void);

StateHandler SelectFallStateHandler_020d1238(FallActor *actor, int *nextState)
{
    BOOL falling = FALSE;
    StateHandler handler = NULL;

    if (actor->modelFlags & 4) {
        if (func_ov052_020d10f0(actor)) {
            actor->onEvent(actor, 3);
            *nextState = 2;
            handler = func_ov052_020d083c;
            actor->stateFlags |= 0x1000000000ULL;
        }
    } else {
        falling = TRUE;
    }
    if (falling) {
        if (actor->onMode != NULL) {
            actor->onMode(actor, 12, -1);
        }
        if (actor->onScale != NULL) {
            actor->onScale(actor, 0xf000);
        }
        actor->velocityY -= 0x380;
        actor->stateFlags |= 0x80000;
        handler = func_ov052_020d0df0;
        *nextState = 28;
    }
    return handler;
}
