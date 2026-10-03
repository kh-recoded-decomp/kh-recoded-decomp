#include "nitro/types.h"

typedef void (*ActorCallback)(void);

typedef struct Actor {
    u8 pad_000[0x1e0];
    ActorCallback onFree;
    u8 pad_1e4[0x1f8 - 0x1e4];
    ActorCallback onUpdate;
    u8 pad_1fc[0x20c - 0x1fc];
    ActorCallback onResetMotion;
    u8 pad_210[0x218 - 0x210];
    ActorCallback onDraw;
    u8 pad_21c[0x6bc - 0x21c];
    int targetIds[4];
    u8 pad_6cc[0x928 - 0x6cc];
    int counter928;
    int counter92c;
    u8 variant;
    u8 pad_931[0x93c - 0x931];
    int state;
    u8 pad_940[0x1804 - 0x940];
    ActorCallback onEnter;
    ActorCallback onStep;
    ActorCallback onExit;
    u8 pad_1810[0x182c - 0x1810];
    int counter182c;
} Actor;

extern void FreeWorkBuffer_020c766c(void);
extern void func_ov059_020c782c(void);
extern void Actor_ResetMotion_020c7960(void);
extern void func_ov059_020c799c(void);
extern void func_ov059_020c79d8(void);
extern void func_ov059_020c7590(void);
extern void func_ov059_020c7684(void);
extern void func_ov059_020cbef8(Actor *actor);

void Actor_InitVariantCallbacks_020c7474(Actor *actor, u8 variant) {
    int i;

    actor->variant = variant;
    actor->state = 3;
    actor->counter928 = 0;
    actor->counter92c = 0;
    actor->counter182c = 0;
    for (i = 0; i < 4; i++) {
        actor->targetIds[i] = -1;
    }
    actor->targetIds[1] = -2;
    func_ov059_020cbef8(actor);
    actor->onFree = FreeWorkBuffer_020c766c;
    actor->onUpdate = func_ov059_020c782c;
    actor->onResetMotion = Actor_ResetMotion_020c7960;
    actor->onDraw = func_ov059_020c799c;
    actor->onStep = func_ov059_020c79d8;
    actor->onEnter = func_ov059_020c7590;
    actor->onExit = func_ov059_020c7684;
}
