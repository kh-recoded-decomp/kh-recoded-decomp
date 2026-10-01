#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct {
    u8 pad_00[4];
    u32 surfaceType : 4;
    u32 unk_04_bits : 28;
    u32 unk_08_low : 22;
    u32 lockCount : 10;
    u8 pad_0c[0x1d4];
} FieldObject;

typedef struct {
    u8 pad_00[0xcc];
    FieldObject *objects;
} FieldContext;

typedef struct {
    u8 pad_00[8];
    u32 jumpPending : 1;
    u32 rising : 1;
    u32 facingFlip : 1;
    u32 unk_08_bit3 : 1;
    u32 ledgeFound : 1;
    u32 unk_08_rest : 27;
    s16 turnTimer;
    s16 idleTimer;
    int bounceCount;
    u8 pad_14[4];
    VecFx32 ledgePosition;
    u8 pad_24[0xc];
    int canClimb;
} HopState;

typedef struct {
    u8 pad_00[4];
    int solid;
} CollisionHit;

extern u32 random_next_scaled_0202aa04(u32 upperBound);
extern int func_ov032_020bcbe0(FieldObject *object, HopState *state);
extern void func_ov032_020bc69c(VecFx32 *out, VecFx32 *velocity, int speed);
extern CollisionHit *func_ov032_020bcaa4(VecFx32 *position, int mask, int arg, VecFx32 *move, VecFx32 *outMove);
extern fx32 func_ov032_020bc634(VecFx32 *velocity, VecFx32 *move);
extern void func_01ffaff4(VecFx32 *in, VecFx32 *out);
extern void func_0204a5e4(VecFx32 *vec, fx32 scale);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern BOOL func_ov032_020bc6fc(VecFx32 *position, fx32 radius, VecFx32 *out);
extern s32 func_ov032_020bbbfc(void *context, s32 index);
extern s32 func_ov032_020bbbf0(void *context, s32 index);
extern int func_ov032_020bc190(void *context, s32 index);

BOOL UpdateHopMovement_020bcc44(FieldContext *context, int index, HopState *state, VecFx32 *position, VecFx32 *velocity, int collisionArg, VecFx32 *outMove, BOOL *outStopped)
{
    FieldObject *object = &context->objects[index];
    VecFx32 move;
    VecFx32 probe;
    VecFx32 offset;
    VecFx32 direction;
    BOOL landed;
    fx32 alignment;
    CollisionHit *hit;
    s32 idleLimit;
    s32 turnLimit;
    fx32 bottomY;
    fx32 groundY;

    if (state->jumpPending) {
        velocity->y = random_next_scaled_0202aa04(0x596) + 0x2cb;
        state->jumpPending = 0;
        state->rising = 1;
        state->bounceCount = 8;
    } else {
        velocity->y -= 0x8f;
    }
    if (state->rising && velocity->y <= 0) {
        state->rising = 0;
    }
    func_ov032_020bc69c(&move, velocity, func_ov032_020bcbe0(object, state));
    if (move.y < 0 && state->bounceCount > 0) {
        velocity->y = 0;
        move.y = 0;
        state->bounceCount--;
    }
    hit = func_ov032_020bcaa4(position, 7, collisionArg, &move, &move);
    if (hit != NULL && hit->solid != 0) {
        landed = TRUE;
    } else {
        landed = FALSE;
    }
    if (landed) {
        velocity->y = 0;
    }
    alignment = FX32_ONE - func_ov032_020bc634(velocity, &move);
    if (state->canClimb != 0 && ((move.x == 0 && move.y == 0 && move.z == 0) || ((alignment ^ (alignment >> 31)) - (alignment >> 31)) > 0x80)) {
        direction = *velocity;
        func_01ffaff4(&direction, &direction);
        func_0204a5e4(&direction, 0x1800);
        offset = direction;
        VEC_Add_01ff9e0c(position, &offset, &probe);
        probe.y += 0x1e000;
        if (object->surfaceType != 3 && landed && func_ov032_020bc6fc(&probe, 0x1800 >> 1, &probe) && probe.y > 0) {
            state->ledgeFound = 1;
            state->ledgePosition = probe;
            state->idleTimer = 0;
        } else {
            *outStopped = TRUE;
            *outMove = move;
            state->turnTimer = 0;
        }
    } else {
        *outStopped = FALSE;
        *outMove = move;
    }
    if (*outStopped) {
        state->idleTimer = 0;
    }
    idleLimit = func_ov032_020bbbfc(context, index);
    turnLimit = func_ov032_020bbbf0(context, index);
    if (object->lockCount != 0) {
        state->idleTimer = 0;
    }
    if (state->idleTimer < idleLimit) {
        state->idleTimer++;
    } else if (state->idleTimer == idleLimit && landed) {
        *outStopped = TRUE;
        state->idleTimer = 0;
    }
    if (state->turnTimer < turnLimit) {
        state->turnTimer++;
    } else if (state->turnTimer == turnLimit && landed) {
        state->facingFlip = func_ov032_020bc190(context, index);
        state->turnTimer = 0;
    }
    bottomY = outMove->y;
    groundY = position->y;
    bottomY += groundY;
    if (bottomY < 0) {
        velocity->y = 0;
        outMove->y = -groundY;
    }
    return landed;
}
