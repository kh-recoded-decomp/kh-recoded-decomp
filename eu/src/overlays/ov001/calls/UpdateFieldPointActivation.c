#include "nitro/types.h"

typedef struct FieldPoint {
    u8 pad_00[0x38];
    u8 actorIndex;
    u8 pad_39[0x15];
    u16 flags;
} FieldPoint;

extern BOOL DetachFromLeaderQuadTree(FieldPoint *point);
extern BOOL ActorSlot_IsFlag8SetByIndex(int actorIndex);
extern void ActorSlot_SetFlag8ByIndex(int actorIndex, BOOL enable);
extern u32 func_ov001_02063838(void);
extern BOOL IsLeadActorNearPoint(FieldPoint *point);
extern void ConfigureChannelSlot(int kind, int value, int index);

void UpdateFieldPointActivation(FieldPoint *point)
{
    if (DetachFromLeaderQuadTree(point)) {
        if (!ActorSlot_IsFlag8SetByIndex(point->actorIndex)) {
            ActorSlot_SetFlag8ByIndex(point->actorIndex, TRUE);
            point->flags |= 0x10;
            point->flags |= 0x20;
        }
    } else {
        if (ActorSlot_IsFlag8SetByIndex(point->actorIndex)) {
            ActorSlot_SetFlag8ByIndex(point->actorIndex, FALSE);
            point->flags &= ~0x10;
            point->flags &= ~0x20;
        }
    }
    if (ActorSlot_IsFlag8SetByIndex(point->actorIndex) && func_ov001_02063838() == 0 &&
        IsLeadActorNearPoint(point)) {
        ConfigureChannelSlot(0, 1, 0);
    }
}
