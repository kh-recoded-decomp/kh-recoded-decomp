#include "nitro/types.h"

typedef struct Actor {
    u8 pad_000[0x930];
    u8 playerIndex;
    u8 pad_931[0x944 - 0x931];
    s32 state;
} Actor;

typedef struct HitEvent {
    u8 pad_00[0x24];
    s8 kind;
} HitEvent;

extern void *func_ov001_0206db78(u32 playerIndex);
extern BOOL func_ov059_020c99ec(Actor *actor);
extern void Actor_UpdateChargeCommand(Actor *actor, void *record);

BOOL func_ov059_020ca31c(Actor *actor, HitEvent *event)
{
    void *record = func_ov001_0206db78(actor->playerIndex);
    BOOL result = FALSE;

    if (actor->state != 8) {
        switch (event->kind) {
        case 1:
        case 2:
            result = func_ov059_020c99ec(actor);
            break;
        case 3:
            break;
        }
    }
    Actor_UpdateChargeCommand(actor, record);
    return result;
}
