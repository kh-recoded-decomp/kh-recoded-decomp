#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct PushWork {
    u8 pad_00[0x84];
    u32 soundHandle;
    BOOL pushStarted;
} PushWork;

typedef struct PushObject {
    u8 pad_00[0x08];
    PushWork *work;
    u8 pad_0C[0x34];
    VecFx32 soundPosition;
    u8 pad_4C[0x1b];
    u8 triggered : 1;
    u8 pushed : 1;
    u8 pad_67_2 : 6;
    u8 pad_68[0x04];
    VecFx32 position;
} PushObject;

typedef struct PushTarget {
    u8 pad_00[0x68];
    PushObject *object;
    int kind;
} PushTarget;

typedef struct PushContext {
    PushTarget *target;
    int state;
} PushContext;

typedef struct PushMotion {
    fx32 speed;
    VecFx32 direction;
} PushMotion;

extern int func_ov046_020c0d68(void);
extern VecFx32 *Camera_GetFocusPosition_020c1780(void);
extern VecFx32 *func_ov001_0206dc4c(int playerIndex);
extern void func_ov001_02063d4c(int id, int value);
extern void func_ov001_0207d45c(int value);
extern BOOL func_0204dc3c(u32 handle);
extern s8 GetCtxModeByte_02068084(void);
extern u32 func_0204da8c(s32 seqArcId, s32 soundId, VecFx32 *position, u32 flags);
extern void FieldObject_SetSavedValue_0207f9c8(PushObject *object, u32 value);
extern void func_01ff9f88(const VecFx32 *src, VecFx32 *dst);
extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);
extern fx32 FX_Div_01ff9c84(fx32 numer, fx32 denom);
extern int FixedPointMultiply12(int left, int right);
extern void func_0204a5e4(VecFx32 *vec, fx32 scale);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void NegateVecFx32_0204aa40(VecFx32 *vec);
extern s64 func_02023d9c(s64 left, s64 right);

BOOL FieldObject_HandlePush_0208334c(PushContext *context, PushMotion *motion, PushObject *object)
{
    PushWork *work = object->work;

    if (context->state == 4 && context->target->kind == 1) {
        if (func_ov046_020c0d68() != 1) {
            if (func_ov046_020c0d68() == 0 &&
                Camera_GetFocusPosition_020c1780() != func_ov001_0206dc4c(0)) {
                goto done;
            }
            func_ov001_02063d4c(6, 0x2000);
            if (!object->triggered) {
                object->triggered = 1;
                func_ov001_0207d45c(1);
                if (work->soundHandle == 0 || !func_0204dc3c(work->soundHandle)) {
                    if (work->pushStarted != 0 || GetCtxModeByte_02068084() != 4) {
                        work->soundHandle = func_0204da8c(0x47, 0, &object->soundPosition, 0);
                    }
                }
            }
            work->pushStarted = 1;
            object->pushed = 1;
            FieldObject_SetSavedValue_0207f9c8(object, 1);
        }
    done:
        return FALSE;
    }

    if (motion->direction.x == 0 && motion->direction.z == 0) {
        return FALSE;
    }
    {
        VecFx32 previous = motion->direction;
        fx32 dot;

        motion->direction.y = 0;
        func_01ff9f88(&motion->direction, &motion->direction);
        dot = VEC_DotProduct_01ff9e6c(&motion->direction, &previous);
        if ((dot < 0 ? -dot : dot) > 0x10) {
            motion->speed = FX_Div_01ff9c84(motion->speed, dot);
        }
    }
    if (context->state == 4 && context->target->kind == 0x15) {
        fx32 ratio = FX_Div_01ff9c84(motion->speed, 0x199a);
        motion->speed = FixedPointMultiply12((fx32)((func_02023d9c(ratio, ratio) + 0x800) >> 12), 0x266);
        {
            VecFx32 step;
            VecFx32 back;
            VecFx32 scaled;
            VecFx32 delta;
            VecFx32 negated;

            scaled = motion->direction;
            func_0204a5e4(&scaled, motion->speed);
            *(VecFx32 *)&delta = scaled;
            step = scaled;
            VEC_Add_01ff9e0c(&object->position, &step, &object->position);
            negated = delta;
            NegateVecFx32_0204aa40(&negated);
            back = negated;
            VEC_Add_01ff9e0c(&context->target->object->position, &back, &context->target->object->position);
        }
        return FALSE;
    }
    return TRUE;
}
