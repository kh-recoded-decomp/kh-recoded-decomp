#include "nitro/types.h"

typedef struct ReleasableActor {
    u8 pad_000[0x14];
    u8 animationModel[0xd8];
    u8 animationSet[0xe4];
    u8 motionController[0xac];
    u16 typeId;
    u8 pad_27e[0x2];
    u16 unk_280;
    u8 pad_282[0x8];
    u16 unk_28A_0 : 14;
    u16 ownsAnimationSet : 1;
    u16 unk_28A_15 : 1;
    u8 pad_28c[0x120];
    u16 unk_3AC;
    u16 unk_3AE;
    u8 pad_3b0[0x14];
    void *extraBuffer;
} ReleasableActor;

extern void ReleaseLinkedActors_02091400(ReleasableActor *actor);
extern void ReleaseAttachedObjects_02091570(ReleasableActor *actor);
extern void ReleaseActorEffect_02091ac0(ReleasableActor *actor, u16 groupId, u16 effectId, int mode);
extern void func_ov021_020b4b60(void *controller);
extern void ReleaseActorAnimationSet_0209bfdc(void *animationSet, void *model);
extern void func_ov001_0209bf54(ReleasableActor *actor);
extern void func_02036874(ReleasableActor *actor);
extern int ZeroHalfThenFree_0202cd78(void *buffer);

BOOL ReleaseActorResources_02090240(ReleasableActor *actor)
{
    actor->unk_3AC = 0;
    actor->unk_3AE = 0;
    actor->unk_280 = 0;
    if (actor->typeId != 0) {
        ReleaseLinkedActors_02091400(actor);
        ReleaseAttachedObjects_02091570(actor);
        ReleaseActorEffect_02091ac0(actor, 0xffff, 0xffff, 0);
        func_ov021_020b4b60(actor->motionController);
        if (actor->ownsAnimationSet) {
            ReleaseActorAnimationSet_0209bfdc(actor->animationSet, actor->animationModel);
        }
        func_ov001_0209bf54(actor);
        if (actor->typeId != 0xffff) {
            func_02036874(actor);
        }
        if (actor->extraBuffer != NULL) {
            ZeroHalfThenFree_0202cd78(actor->extraBuffer);
            actor->extraBuffer = NULL;
            actor->ownsAnimationSet = FALSE;
        }
        actor->typeId = 0;
    }
    return TRUE;
}
