#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 locked;
    u8 variant;
} HitState;

typedef struct {
    u8 pad_000[0x194];
    HitState state;
} HitOwner;

typedef struct {
    HitOwner *owner;
    u8 pad_04[0x2c - 0x04];
    s32 height;
} HitOwnerRef;

typedef struct {
    HitOwnerRef *ref;
    int kind;
} HitSource;

typedef struct {
    HitSource *source;
    int type;
} HitInfo;

typedef struct {
    u8 pad_00[0x38];
    VecFx32 position;
    u8 pad_44[0x77 - 0x44];
    u8 mode;
    u8 pad_78[0xc0 - 0x78];
    u32 flags;
    u8 pad_c4[0xcc - 0xc4];
    VecFx32 velocity;
    fx32 resistance;
} FieldObject;

typedef struct {
    int obj;
    int arg1;
    int arg2;
    int arg3;
} HitContext;

extern VecFx32 *func_ov001_0206dc4c(int arg);
extern BOOL IsMovingAgainstDirection_02086618(FieldObject *object, int entryIndex, const VecFx32 *direction);
extern fx32 FX_Div_01ff9c84(fx32 numer, fx32 denom);
extern void func_01ff9f88(const VecFx32 *src, VecFx32 *dst);
extern void ScaleVecFx32InPlace_0204a5e4(VecFx32 *v, fx32 scale);
extern void OnFieldUnitPushedUp_020a566c(void *self, u16 other, const VecFx32 *push, HitInfo *hit, int context, int arg1, int arg2, int arg3);

void OnMode7FieldObjectHit_020a4694(void *self, u16 other, const VecFx32 *push, HitInfo *hit, HitContext context)
{
    FieldObject *obj = (FieldObject *)context.obj;
    VecFx32 direction;
    VecFx32 velocity;
    HitState *state;
    VecFx32 *playerPos;
    fx32 scale;

    if (obj->mode == 7 && !(obj->flags & 0x30000) && hit != NULL && hit->type == 2 && hit->source->kind == 0) {
        state = &hit->source->ref->owner->state;
        if (state->locked == 0 && state->variant == 0) {
            playerPos = func_ov001_0206dc4c(state->variant);
            if (IsMovingAgainstDirection_02086618(obj, state->variant, push) && obj->resistance < 0x800 &&
                (push->y <= 0 || push->x != 0 || push->z != 0) &&
                (push->y >= 0 || (push->y < 0 && hit->source->ref->height != (s32)0x80000000)) &&
                playerPos->y - obj->position.y < 0x1599) {
                direction = *push;
                scale = (fx32)(((s64)FX_Div_01ff9c84(0x1000 - obj->resistance, 0x1000) * 0x119a + 0x800) >> 12);
                if (direction.y > 0) {
                    direction.y = 1;
                    func_01ff9f88(&direction, &direction);
                }
                velocity = direction;
                ScaleVecFx32InPlace_0204a5e4(&velocity, scale);
                obj->velocity = velocity;
                obj->flags |= 0x10000;
                if (obj->resistance == 0) {
                    obj->resistance = 0x1000;
                }
            }
        }
    }
    OnFieldUnitPushedUp_020a566c(self, other, push, hit, context.obj, context.arg1, context.arg2, context.arg3);
}
