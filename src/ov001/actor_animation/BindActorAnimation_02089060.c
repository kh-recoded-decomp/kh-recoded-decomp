#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ActorAnimation {
    u8 pad0[0x20];
    u32 flags;
    u8 pad24[0x30];
    void *owner;
    u8 pad58[0x1c];
    void *resource;
    u8 pad78[0x60];
    u8 blendTable[0x2c];
    VecFx32 offset;
} ActorAnimation;

typedef struct AnimatedActor {
    u8 pad[0x370];
    ActorAnimation animation;
} AnimatedActor;

extern const VecFx32 data_02053438;
extern void ReleaseResourceAndDetach_0202eee8(void *object);
extern void func_0202edd8(void *dst, int a, void *info, int b);
extern void selectJointAnimationBlend_0202f2cc(void *anim, u16 trackIndex, void *blendTable, short blendIndex);

void BindActorAnimation_02089060(AnimatedActor *actor, int animationId, int blendIndex) {
    if (actor->animation.resource != NULL) {
        ReleaseResourceAndDetach_0202eee8(&actor->animation);
    }
    func_0202edd8(&actor->animation, animationId, NULL, 0xd);
    selectJointAnimationBlend_0202f2cc(&actor->animation, 0, actor->animation.blendTable, blendIndex);
    actor->animation.owner = actor;
    actor->animation.flags |= 2;
    actor->animation.offset = data_02053438;
}
