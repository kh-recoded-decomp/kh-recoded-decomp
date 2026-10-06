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
extern u16 SharedObject_GetId(void *record);
extern BOOL HasFlagsAt0xe(void *record, u16 mask);
extern BOOL IsWaitTargetReady(LinkSlot *link);
extern void func_ov001_0207f8ac(void *target, LinkRequest *request);
extern void Actor_MarkGuardBreakInState3(Actor *actor);
extern void OpenFieldMenuMode(s32 mode);

s32 func_ov059_020c98a0(Actor *actor)
{
    void *record = func_ov001_0206db78(actor->playerIndex);
    u32 heldFlag = actor->inputFlags & 4;
    s32 state;
    LinkRequest request;

    switch (SharedObject_GetId(record)) {
    case 1:
        if (!HasFlagsAt0xe(record, 0x400) && !actor->pending) {
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
        if (state != 3 && IsWaitTargetReady(link) && link->kind == 2) {
            request.playerIndex = actor->playerIndex;
            request.flags = 0;
            func_ov001_0207f8ac(link->target, &request);
        }
        Actor_MarkGuardBreakInState3(actor);
        break;
    }
    case 4:
        if (heldFlag) {
            actor->statusFlags |= 0x20;
            OpenFieldMenuMode(1);
        }
        break;
    }
    return 0;
}
