#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Actor Actor;
typedef void (*ActorChangeStateFunc)(Actor *actor, s32 state);
typedef void (*ActorNotifyFunc)(Actor *actor, s32 value);

struct Actor {
    u8 pad_0000[0x1fc];
    ActorNotifyFunc onFollowUp;
    u8 pad_0200[0x234 - 0x200];
    u32 inputFlags;
    u8 pad_0238[0x760 - 0x238];
    fx32 animFrame;
    u8 pad_0764[4];
    BOOL animationEnded;
    u8 pad_076C[0x928 - 0x76c];
    u64 statusFlags;
    u8 playerIndex;
    u8 pad_0931[0x970 - 0x931];
    VecFx32 velocity;
    VecFx32 moveTarget;
    u8 pad_0988[0x1808 - 0x988];
    ActorChangeStateFunc changeState;
};

extern const VecFx32 data_02053438;

extern void func_ov059_020cce10(Actor *actor, VecFx32 *target);
extern void *func_ov001_0206db78(u32 playerIndex);
extern BOOL AlarmCallback_020a7504(void *record);
extern BOOL func_ov021_020a751c(void *record, u16 mask);
extern BOOL func_ov059_020cb910(Actor *actor);
extern void func_ov059_020c997c(Actor *actor);

void func_ov059_020c9728(Actor *actor)
{
    BOOL finished = FALSE;
    void *record;
    u64 followUpQueued;
    VecFx32 target;

    actor->velocity = data_02053438;
    if (!(actor->inputFlags & 4)) {
        actor->changeState(actor, 3);
        return;
    }
    func_ov059_020cce10(actor, &target);
    actor->moveTarget = target;
    record = func_ov001_0206db78(actor->playerIndex);
    if (actor->animFrame >= 0x9000 && !(actor->statusFlags & 2) && AlarmCallback_020a7504(record) &&
        func_ov021_020a751c(record, 0x800) && func_ov059_020cb910(actor)) {
        actor->statusFlags |= 2;
    }
    func_ov059_020c997c(actor);
    followUpQueued = actor->statusFlags & 2;
    if (followUpQueued) {
        if (actor->animFrame >= 0xf000) {
            finished = TRUE;
        }
    } else {
        if (actor->animFrame >= 0x12000) {
            finished = TRUE;
        }
    }
    if (actor->animationEnded || finished) {
        if (followUpQueued) {
            actor->changeState(actor, 5);
            if (actor->onFollowUp != NULL) {
                actor->onFollowUp(actor, 0);
            }
        } else {
            actor->changeState(actor, 1);
        }
    }
}
