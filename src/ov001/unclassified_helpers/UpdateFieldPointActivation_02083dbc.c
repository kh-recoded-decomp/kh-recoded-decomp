#include "nitro/types.h"

typedef struct FieldPoint {
    u8 pad_00[0x38];
    u8 actorIndex;
    u8 pad_39[0x15];
    u16 flags;
} FieldPoint;

extern BOOL IsPointInCurrentArea_020836d8(FieldPoint *point);
extern BOOL IsActorFlag8Set_02036164(int actorIndex);
extern void SetActorFlag8_02036120(int actorIndex, BOOL enable);
extern u32 func_ov001_02063838(void);
extern BOOL IsLeadActorNearPoint_02083d98(FieldPoint *point);
extern void ConfigureChannelSlot_0206ca68(int kind, int value, int index);

void UpdateFieldPointActivation_02083dbc(FieldPoint *point)
{
    if (IsPointInCurrentArea_020836d8(point)) {
        if (!IsActorFlag8Set_02036164(point->actorIndex)) {
            SetActorFlag8_02036120(point->actorIndex, TRUE);
            point->flags |= 0x10;
            point->flags |= 0x20;
        }
    } else {
        if (IsActorFlag8Set_02036164(point->actorIndex)) {
            SetActorFlag8_02036120(point->actorIndex, FALSE);
            point->flags &= ~0x10;
            point->flags &= ~0x20;
        }
    }
    if (IsActorFlag8Set_02036164(point->actorIndex) && func_ov001_02063838() == 0 &&
        IsLeadActorNearPoint_02083d98(point)) {
        ConfigureChannelSlot_0206ca68(0, 1, 0);
    }
}
