#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Actor Actor;
typedef int (*ActorGetStateFunc)(Actor *actor);
typedef void (*ActorChangeStateFunc)(Actor *actor, s32 state);

typedef struct DriftState {
    u8 pad_00[4];
    s32 count;
    u8 flags;
    u8 pad_09[3];
    u16 angle;
} DriftState;

typedef struct InputRecord {
    u16 current;
    u16 previous;
} InputRecord;

struct Actor {
    u8 pad_0000[0x1dc];
    int state;
    u8 pad_01e0[0x22c - 0x1e0];
    ActorGetStateFunc getState;
    u8 pad_0230[4];
    u32 flags;
    u8 pad_0238[0x930 - 0x238];
    u8 playerIndex;
    u8 pad_0931[0x970 - 0x931];
    VecFx32 velocity;
    VecFx32 position;
    u8 pad_0988[0x16f0 - 0x988];
    DriftState drift;
    u8 pad_1700[0x1808 - 0x1700];
    ActorChangeStateFunc changeState;
};

extern const VecFx32 data_0205344c;
extern const s16 data_02053580[];
extern InputRecord *GetPlayerControlState(u32 playerIndex);
extern void Actor_UpdateJump(Actor *actor, int x, int y);
extern BOOL func_ov021_020a7524(InputRecord *record);
extern BOOL HasFlagsAt0xc(InputRecord *record, u16 mask);
extern int func_0202a9e4(u32 mask);
extern fx32 FX_Mul(fx32 a, fx32 b);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);

void Actor_UpdateDrift(Actor *actor)
{
    InputRecord *record = GetPlayerControlState(actor->playerIndex);
    DriftState *drift = &actor->drift;
    u32 moving = actor->flags & 4;
    int state;
    BOOL pressed;
    int angle;
    VecFx32 offset;

    if (moving == 0) {
        Actor_UpdateJump(actor, 0, 0);
    } else {
        actor->velocity = data_0205344c;
    }
    if (actor->getState != NULL) {
        state = actor->getState(actor);
    } else {
        state = actor->state;
    }
    if (state != 2) {
        actor->changeState(actor, 8);
        return;
    }
    if (moving == 0) {
        return;
    }
    pressed = FALSE;
    angle = -1;
    if (func_ov021_020a7524(record)) {
        if (record->previous != record->current) {
            pressed = TRUE;
        }
    } else if (HasFlagsAt0xc(record, 0xc03)) {
        pressed = TRUE;
    }
    if (pressed) {
        drift->count++;
        if (!(drift->flags & 8)) {
            angle = func_0202a9e4(0xffff);
        }
    }
    if (pressed && angle != -1) {
        drift->flags |= 8;
        drift->angle = angle + 0x8000;
    } else if (drift->flags & 8) {
        drift->flags &= 0xf7;
        angle = drift->angle;
    }
    if (angle >= 0) {
        int index = (u16)angle >> 4;
        offset.x = -data_02053580[index];
        offset.z = -data_02053580[(0x400 - index) & 0xfff];
        offset.x = FX_Mul(offset.x, 0x133);
        offset.z = FX_Mul(offset.z, 0x133);
        offset.y = 0;
        VEC_Add(&actor->position, &offset, &actor->position);
    }
}
