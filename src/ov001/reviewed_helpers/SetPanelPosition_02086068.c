#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad[0x64];
    s16 primaryId;
} Slots;

typedef struct {
    u8 pad_00[8];
    Slots *slots;
    u8 pad_0c[0x38 - 0xc];
    u8 actorId;
    u8 pad_39[0x40 - 0x39];
    VecFx32 position;
    u8 pad_4c[2];
    u16 flags;
} Panel;

extern void *func_02036240(u32 actorId);
extern void Obj_SetPosition_0203569c(void *entity, const VecFx32 *position);

void SetPanelPosition_02086068(Panel *panel, const VecFx32 *position) {
    panel->position = *position;
    if ((panel->flags & 4) && panel->slots->primaryId >= 0) {
        Obj_SetPosition_0203569c(func_02036240(panel->actorId), &panel->position);
    }
}
