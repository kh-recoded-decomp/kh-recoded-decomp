#include "nitro/types.h"

typedef void (*ActorCallback)(void);

typedef struct Actor {
    u8 pad_000[0x1e0];
    ActorCallback onFree;
    ActorCallback onUpdate;
    ActorCallback onDraw;
    ActorCallback callback1ec;
    ActorCallback callback1f0;
    u8 pad_1f4[0x1f8 - 0x1f4];
    ActorCallback callback1f8;
    ActorCallback callback1fc;
    ActorCallback callback200;
    u8 pad_204[0x208 - 0x204];
    ActorCallback callback208;
    ActorCallback callback20c;
    ActorCallback callback210;
    ActorCallback onAddVelocity;
    u8 pad_218[0x21c - 0x218];
    ActorCallback onGetReadyFlags;
    ActorCallback callback220;
    ActorCallback callback224;
    u8 pad_228[0x930 - 0x228];
    u8 variant;
    u8 pad_931[0x1804 - 0x931];
    ActorCallback onEnter;
    ActorCallback onStep;
    ActorCallback onExit;
} Actor;

extern void func_ov021_020a75a4(Actor *actor, int kind, int variant);
extern void Actor_Update_020cbe98(void);
extern void func_ov059_020cbce8(void);
extern void Actor_Draw_020cbde0(void);
extern void func_ov059_020cce7c(void);
extern void func_ov059_020cc814(void);
extern void func_ov059_020cc860(void);
extern void func_ov059_020ccae8(void);
extern void func_ov059_020cca14(void);
extern void Actor_GetReadyFlags_020ccc68(void);
extern void func_ov059_020cccec(void);
extern void Actor_AddExtraVelocity_020cbfd0(void);
extern void func_ov059_020cd0fc(void);
extern void func_ov059_020c90c8(void);
extern void func_ov059_020cbfec(void);
extern void func_ov059_020c8f9c(void);
extern void func_ov059_020cbff8(void);

void Actor_InstallCallbacks_020cbef8(Actor *actor)
{
    func_ov021_020a75a4(actor, 0, actor->variant);
    actor->onUpdate = Actor_Update_020cbe98;
    actor->onFree = func_ov059_020cbce8;
    actor->onDraw = Actor_Draw_020cbde0;
    actor->callback1ec = func_ov059_020cce7c;
    actor->callback1f8 = func_ov059_020cc814;
    actor->callback1fc = func_ov059_020cc860;
    actor->callback208 = func_ov059_020ccae8;
    actor->callback1f0 = func_ov059_020cca14;
    actor->onGetReadyFlags = Actor_GetReadyFlags_020ccc68;
    actor->callback20c = func_ov059_020cccec;
    actor->onAddVelocity = Actor_AddExtraVelocity_020cbfd0;
    actor->callback210 = func_ov059_020cd0fc;
    actor->callback220 = func_ov059_020c90c8;
    actor->callback224 = func_ov059_020cbfec;
    actor->callback200 = func_ov059_020c8f9c;
    actor->onStep = func_ov059_020cbff8;
    actor->onEnter = NULL;
    actor->onExit = NULL;
}
