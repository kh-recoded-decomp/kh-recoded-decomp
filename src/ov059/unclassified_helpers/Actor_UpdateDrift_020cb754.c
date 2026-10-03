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

extern const VecFx32 data_02053438;
extern const s16 data_0205356c[];

extern InputRecord *func_ov001_0206db78(u32 playerIndex);
extern void func_ov059_020ca33c(Actor *actor, int x, int y);
extern BOOL AlarmCallback_020a7504(InputRecord *record);
extern BOOL HasFlagsAt0xc_020a751c(InputRecord *record, u16 mask);
extern int func_0202a9d0(u32 mask);
extern fx32 FixedPointMultiply12(fx32 a, fx32 b);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);

void Actor_UpdateDrift_020cb754(Actor *actor)
{
    InputRecord *record = func_ov001_0206db78(actor->playerIndex);
    DriftState *drift = &actor->drift;
    u32 moving = actor->flags & 4;
    int state;
    BOOL pressed;
    int angle;
    VecFx32 offset;

    if (moving == 0) {
        func_ov059_020ca33c(actor, 0, 0);
    } else {
        actor->velocity = data_02053438;
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
    if (AlarmCallback_020a7504(record)) {
        if (record->previous != record->current) {
            pressed = TRUE;
        }
    } else if (HasFlagsAt0xc_020a751c(record, 0xc03)) {
        pressed = TRUE;
    }
    if (pressed) {
        drift->count++;
        if (!(drift->flags & 8)) {
            angle = func_0202a9d0(0xffff);
        }
    }
    if (pressed && angle != -1) {
        drift->flags |= 8;
        drift->angle = angle + 0x8000;
    } else if (drift->flags & 8) {
        drift->flags &= ~8;
        angle = drift->angle;
    }
    if (angle >= 0) {
        int index = (u16)angle >> 4;
        offset.x = -data_0205356c[index];
        offset.z = -data_0205356c[(0x400 - index) & 0xfff];
        offset.x = FixedPointMultiply12(offset.x, 0x133);
        offset.z = FixedPointMultiply12(offset.z, 0x133);
        offset.y = 0;
        VEC_Add_01ff9e0c(&actor->position, &offset, &actor->position);
    }
}
