#include "nitro/types.h"

typedef struct {
    u32 flags;
    u16 dirtyFlags;
    u8 pad_06[0x80 - 6];
    u16 state;
} Actor;

typedef struct {
    u8 pad[0x64];
    s16 primaryId;
} Slots;

typedef struct {
    u8 pad_00[8];
    Slots *slots;
    u8 pad_0c[0x38 - 0xc];
    u8 actorId;
    u8 pad_39[0x4c - 0x39];
    u16 state;
    u16 flags;
} Panel;

extern Actor *func_02036240(u32 actorId);

void SetPanelActorState_0207f7c0(Panel *panel, u16 state) {
    Actor *actor;
    panel->state = state;
    if ((panel->flags & 4) && panel->slots->primaryId >= 0) {
        actor = func_02036240(panel->actorId);
        if (!(actor->flags & 0x20)) {
            actor->state = state;
            actor->dirtyFlags |= 0x20;
        }
    }
}
