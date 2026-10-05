#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct HitSurface {
    u8 pad_00[0x6c];
    s32 kind;
} HitSurface;

typedef struct HitInfo {
    u8 pad_00[0x10];
    HitSurface *surface;
} HitInfo;

struct MoveActor;

typedef struct MoveCallbacks {
    u8 pad_00[0x24];
    BOOL (*checkGround)(struct MoveActor *actor, VecFx32 *move, VecFx32 *delta, VecFx32 *hitPos);
    void (*onHit)(struct MoveActor *actor, VecFx32 *move, VecFx32 *hitPos, HitInfo *hit);
    BOOL (*checkFloor)(struct MoveActor *actor, VecFx32 *move, VecFx32 *hitPos);
    BOOL (*checkCeiling)(struct MoveActor *actor, VecFx32 *move, VecFx32 *hitPos);
} MoveCallbacks;

typedef struct MoveActor {
    u8 pad_000[0x1d0];
    u8 sequencer[0x26c - 0x1d0];
    u32 flags : 31;
    u32 unk_26c_31 : 1;
    u8 pad_270[0x278 - 0x270];
    MoveCallbacks *callbacks;
    u16 active;
    u8 pad_27e[0x288 - 0x27e];
    u16 unk_288_0 : 5;
    u16 landed : 1;
    u16 onFloor : 1;
    u16 onSurface : 1;
    u16 unk_288_8 : 5;
    u16 locked : 1;
    u16 rising : 1;
    u16 unk_288_15 : 1;
    u8 pad_28a[2];
    u16 unk_28c_0 : 15;
    u16 forceLand : 1;
    u8 pad_28e[2];
    fx32 floorY;
    fx32 fallSpeed;
    fx32 gravity;
    u8 pad_29c[0x2c0 - 0x29c];
    VecFx32 position;
    u8 pad_2cc[0x2ee - 0x2cc];
    u16 keepHeight : 1;
    u16 grounded : 1;
    u16 wasGrounded : 1;
    u16 unk_2ee_3 : 13;
    u8 pad_2f0[0x364 - 0x2f0];
    s32 frozen;
    u8 pad_368[0x36c - 0x368];
    fx32 verticalSpeed;
    u8 pad_370[0x374 - 0x370];
    VecFx32 pushOffset;
    u8 pad_380[0x38c - 0x380];
    VecFx32 extraMove;
} MoveActor;

extern const VecFx32 data_02053438;

extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *dst);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_Mag_01ff9f28(const VecFx32 *v);
extern HitInfo *func_ov001_02091658(MoveActor *actor, VecFx32 *position, VecFx32 *delta, VecFx32 *hitPos);
extern void RunOverrideTrack_020b4b9c(void *sequencer, u16 overrideId);
extern BOOL Session_Exists_02063a24(void);
extern int func_ov001_02063a38(void);
extern void ClearActorMotionState_02091194(MoveActor *actor);
extern fx32 GetGlobalScaleValue_0209c3cc(void);
extern fx32 FixedPointMultiply12(fx32 a, fx32 b);

static inline int GetSessionMode(void)
{
    int mode;

    if (Session_Exists_02063a24()) {
        mode = func_ov001_02063a38();
    } else {
        mode = 0;
    }
    return mode;
}

void ApplyActorMovementCollision_0208fda4(MoveActor *actor, VecFx32 *move)
{
    BOOL clearMotion;
    BOOL hitCeiling;
    HitInfo *hit;
    BOOL landed;
    VecFx32 delta;
    VecFx32 hitPos;
    VecFx32 ceilingPos;
    VecFx32 floorPos;

    clearMotion = FALSE;
    hitCeiling = FALSE;
    landed = FALSE;
    if (actor->active == 0) {
        return;
    }
    actor->wasGrounded = actor->grounded;
    actor->landed = 0;
    actor->onFloor = 0;
    actor->forceLand = 0;
    actor->keepHeight = 0;
    VEC_Add_01ff9e0c(&actor->pushOffset, move, move);
    if (VEC_Mag_01ff9f28(&actor->extraMove) != 0) {
        VEC_Add_01ff9e0c(move, &actor->extraMove, move);
        actor->extraMove = data_02053438;
    }
    VEC_Subtract_01ff9e3c(move, &actor->position, &delta);
    delta.y = 0;
    VEC_Mag_01ff9f28(&delta);
    if (!(actor->flags & 0x20)) {
        BOOL wasRising;

        hitPos = actor->position;
        hit = func_ov001_02091658(actor, &actor->position, &delta, &hitPos);
        if (hit != NULL || actor->forceLand) {
            landed = TRUE;
            if (!(actor->flags & 0x100000) && actor->callbacks->onHit != NULL) {
                actor->callbacks->onHit(actor, move, &hitPos, hit);
            }
            if (hit != NULL && hit->surface != NULL) {
                s32 kind = hit->surface->kind;
                BOOL solid = FALSE;

                if (kind == 1) {
                    solid = TRUE;
                } else if (kind == 2) {
                    solid = TRUE;
                }
                if (solid) {
                    actor->onSurface = 1;
                    if (actor->flags & 0x80) {
                        landed = FALSE;
                    }
                }
            } else if (hit == NULL && actor->onSurface && (actor->flags & 0x80)) {
                landed = FALSE;
            }
        }
        wasRising = actor->rising;
        if (landed) {
            actor->landed = 1;
            RunOverrideTrack_020b4b9c(actor->sequencer, 4);
        }
        if (!actor->landed) {
            actor->extraMove = data_02053438;
        }
        if (actor->onSurface && !wasRising && !actor->locked && !(actor->flags & 0x80)) {
            clearMotion = TRUE;
        }
    }
    if (!(actor->flags & 8) && (GetSessionMode() == 4 || GetSessionMode() == 10)) {
        if (actor->callbacks->checkGround != NULL && !actor->callbacks->checkGround(actor, move, &delta, &hitPos)) {
            clearMotion = TRUE;
        }
    }
    if (clearMotion) {
        ClearActorMotionState_02091194(actor);
    }
    if (actor->frozen == 0 && !(actor->flags & 8)) {
        fx32 scale = GetGlobalScaleValue_0209c3cc();

        if (actor->fallSpeed > 0) {
            move->y -= FixedPointMultiply12(actor->fallSpeed, scale);
        }
        actor->fallSpeed += FixedPointMultiply12(actor->gravity / 20, scale);
        if (actor->fallSpeed >= 0x1000) {
            actor->fallSpeed = 0x1000;
        }
    }
    if (!(actor->flags & 0x80000)) {
        ceilingPos = hitPos;
        if (actor->callbacks->checkCeiling != NULL && actor->callbacks->checkCeiling(actor, move, &ceilingPos)) {
            move->y = ceilingPos.y;
            hitCeiling = TRUE;
        }
    }
    landed = FALSE;
    if (!(actor->flags & 0x40)) {
        floorPos = hitPos;
        if (actor->callbacks->checkFloor != NULL) {
            landed = actor->callbacks->checkFloor(actor, move, &floorPos);
        }
        if (!landed) {
            if (GetSessionMode() == 4) {
                actor->floorY = -0x3000;
            } else {
                actor->floorY = 0;
            }
        }
    }
    if (move->y <= actor->floorY) {
        if (!(actor->flags & 0x40)) {
            move->y = actor->floorY;
            actor->verticalSpeed = 0;
            actor->fallSpeed = 0;
        }
        actor->onFloor = 1;
        RunOverrideTrack_020b4b9c(actor->sequencer, 3);
    }
    if (!actor->keepHeight && hitCeiling && actor->onFloor) {
        move->y = actor->position.y;
    }
}
