#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct MotionActor MotionActor;
typedef void (*ActorEventFunc)(MotionActor *actor, int event);

struct MotionActor {
    u8 pad_000[0x768];
    int eventFlag;
    u8 pad_76c[0x9ac - 0x76c];
    u64 stateFlags;
    u8 pad_9b4[0x9c4 - 0x9b4];
    fx32 speed;
    VecFx32 velocity;
    u8 pad_9d4[0x10ec - 0x9d4];
    ActorEventFunc onEvent;
};

extern BOOL func_ov052_020c7dc4(MotionActor *actor);
extern void func_ov052_020ce9d4(MotionActor *actor, VecFx32 *delta);
extern VecFx32 *func_ov052_020ceb54(MotionActor *actor);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void func_ov052_020ceb60(MotionActor *actor, VecFx32 *position);

void ApplyRootMotion_020cae20(MotionActor *actor)
{
    VecFx32 delta;
    VecFx32 position;

    if (actor->speed >= 0xf000 && func_ov052_020c7dc4(actor)) {
        return;
    }
    if (actor->eventFlag != 0) {
        actor->onEvent(actor, 4);
        return;
    }
    func_ov052_020ce9d4(actor, &delta);
    if (actor->speed >= 0x5000) {
        if (delta.y != 0) {
            actor->velocity.y = delta.y;
        }
        actor->velocity.x += delta.x;
        actor->velocity.z += delta.z;
        return;
    }
    actor->stateFlags |= 1;
    VEC_Add_01ff9e0c(func_ov052_020ceb54(actor), &delta, &position);
    func_ov052_020ceb60(actor, &position);
}
