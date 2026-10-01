#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ActorNode {
    u32 flags;
    u8 node[0x20];
    u32 renderFlags;
    u8 pad_28[0x28];
    void *owner;
} ActorNode;

typedef struct ShadowOwner {
    u8 pad_000[0x1a8];
    VecFx32 shadowPosition;
} ShadowOwner;

typedef struct ShadowedActor {
    u8 pad_00[0xc];
    ShadowOwner *owner;
    u8 pad_10[0x28];
    u8 actorId;
    u8 pad_39[0x4b];
    u16 animFlags;
    u8 pad_86[0x1e];
    u8 renderObj[0xdc];
    u16 colorScale;
    u8 pad_182[0xa];
    u32 geometryArgs[3];
} ShadowedActor;

extern ActorNode *func_02036240(u32 id);
extern void ClearSbcCallback_020188b8(void *renderObj);
extern void RegisterSbcCallback_020188a4(void *renderObj, void *func, u8 *arg, u8 cmd, int timing);
extern void SceneNode_Draw_01ffb12c(void *node);
extern signed char GetCtxModeByte_02068084(void);
extern u16 AdvanceAnimationTracks_0202ef24(void *state, fx32 delta);
extern void func_02019188(void);
extern void setMaterialColorScale_01fff67c(int packedRgb);
extern void QueueOrSendGeometryCommand_01ffa37c(u32 op, const u32 *args, u32 numWords);
extern void func_01ffe1bc(void *renderObj);
extern void func_ov001_020847e4(ShadowedActor *actor, VecFx32 *out);
extern void ShadowVolume_Draw_02036b80(void *shadow);
extern void func_ov001_02084798();

void DrawActorWithShadow_020848a0(ShadowedActor *actor)
{
    ActorNode *node;
    VecFx32 position;

    node = func_02036240(actor->actorId);
    node->owner = actor;
    ClearSbcCallback_020188b8(&node->renderFlags);
    RegisterSbcCallback_020188a4(&node->renderFlags, func_ov001_02084798, NULL, 6, 3);
    node->renderFlags |= 1;
    if (!(node->flags & 0x20)) {
        SceneNode_Draw_01ffb12c(node->node);
    }
    node->renderFlags &= ~1;
    if (GetCtxModeByte_02068084() != 7) {
        AdvanceAnimationTracks_0202ef24(&actor->animFlags, 0x1000);
        func_02019188();
        if (actor->animFlags & 0x40) {
            setMaterialColorScale_01fff67c(actor->colorScale);
        }
        QueueOrSendGeometryCommand_01ffa37c(0x17, actor->geometryArgs, 0xc);
        func_01ffe1bc(actor->renderObj);
    }
    func_ov001_020847e4(actor, &position);
    actor->owner->shadowPosition = position;
    ShadowVolume_Draw_02036b80(&actor->owner->shadowPosition);
}
