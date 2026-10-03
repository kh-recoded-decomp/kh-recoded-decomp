#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u32 flags;
    u8 node[0x20];
    u32 renderFlags;
} ActorModel;

typedef struct {
    u8 pad_000[0x230];
    ActorModel *model;
    u8 pad_234[0x9ac - 0x234];
    u64 stateFlags;
    u8 pool;
    u8 pad_9b5[0xa00 - 0x9b5];
    VecFx32 attachPosition;
    u8 pad_a0c[0xb68 - 0xa0c];
    u8 parts[2][0x230];
    u8 pad_fc8[0x105c - 0xfc8];
    u8 pendingRequest[0x14];
    u8 members[0x98];
    u8 marker[4];
} DrawnActor;

extern void SceneNode_Draw_01ffb12c(void *node);
extern VecFx32 GetSlot3WorldPosition_020cbfdc(DrawnActor *actor);
extern void DrawPendingSlotModel_020d13f0(DrawnActor *actor, void *request);
extern void DrawModelWithAttachment_020a9af0(void *part);
extern void DrawSlotMarker_020ab898(void *marker);
extern void UpdateActorShadow_020cbe7c(DrawnActor *actor);
extern void InvokeMemberDrawCallbacks_020ad714(void *members);
extern void DrawAllGroupSlots_020a8b44(int pool);

void DrawActor_020ccd24(DrawnActor *actor)
{
    u32 mask = 1;
    int i;

    if ((actor->stateFlags & 0x40000) != 0) {
        mask |= 2;
    }
    actor->model->renderFlags |= mask;
    if (!(actor->model->flags & 0x20)) {
        SceneNode_Draw_01ffb12c(actor->model->node);
    }
    actor->model->renderFlags &= ~mask;
    actor->attachPosition = GetSlot3WorldPosition_020cbfdc(actor);
    if ((actor->stateFlags & 0x40000) == 0) {
        DrawPendingSlotModel_020d13f0(actor, actor->pendingRequest);
        for (i = 0; i < 2; i++) {
            DrawModelWithAttachment_020a9af0(actor->parts[i]);
        }
        DrawSlotMarker_020ab898(actor->marker);
        UpdateActorShadow_020cbe7c(actor);
    }
    InvokeMemberDrawCallbacks_020ad714(actor->members);
    DrawAllGroupSlots_020a8b44(actor->pool);
}
