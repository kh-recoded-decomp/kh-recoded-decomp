#include "nitro/types.h"

typedef struct Actor Actor;
typedef s32 (*ActorGetStateFunc)(Actor *actor);

typedef struct LinkSlot {
    u8 kind;
    u8 pad_01[3];
    void *target;
} LinkSlot;

typedef struct LinkRequest {
    u8 playerIndex;
    u8 flags;
} LinkRequest;

struct Actor {
    u8 pad_0000[0x1dc];
    s32 state;
    u8 pad_01E0[0x22c - 0x1e0];
    ActorGetStateFunc getState;
    u8 pad_0230[4];
    u32 inputFlags;
    u8 pad_0238[0x928 - 0x238];
    u64 statusFlags;
    u8 playerIndex;
    u8 pad_0931[3];
    s32 pending : 8;
    s32 pendingPad : 24;
    u8 triggered : 8;
    u8 pad_0939[0xeb0 - 0x939];
    LinkSlot link;
    u8 pad_0EB8[0x1704 - 0xeb8];
    s32 triggerTimer;
};

extern void *func_ov001_0206db78(u32 playerIndex);
extern u16 GetId10_020a755c(void *record);
extern BOOL func_ov021_020a752c(void *record, u16 mask);
extern BOOL func_ov001_0206c3a4(LinkSlot *link);
extern void func_ov001_0207f884(void *target, LinkRequest *request);
extern void func_ov059_020cd224(Actor *actor);
extern void func_ov001_020641d4(s32 mode);

s32 func_ov059_020c9880(Actor *actor)
{
    void *record = func_ov001_0206db78(actor->playerIndex);
    u32 heldFlag = actor->inputFlags & 4;
    s32 state;
    LinkRequest request;

    switch (GetId10_020a755c(record)) {
    case 1:
        if (!func_ov021_020a752c(record, 0x400) && !actor->pending) {
            actor->pending = 1;
            actor->triggered = 1;
            actor->triggerTimer = 0;
        }
        break;
    case 2:
    case 3: {
        LinkSlot *link = &actor->link;

        if (actor->getState != NULL) {
            state = actor->getState(actor);
        } else {
            state = actor->state;
        }
        if (state != 3 && func_ov001_0206c3a4(link) && link->kind == 2) {
            request.playerIndex = actor->playerIndex;
            request.flags = 0;
            func_ov001_0207f884(link->target, &request);
        }
        func_ov059_020cd224(actor);
        break;
    }
    case 4:
        if (heldFlag) {
            actor->statusFlags |= 0x20;
            func_ov001_020641d4(1);
        }
        break;
    }
    return 0;
}
