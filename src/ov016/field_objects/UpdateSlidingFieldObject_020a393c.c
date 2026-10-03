#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct FieldUnit {
    u8 pad_00[0x59];
    u8 group;
} FieldUnit;

typedef struct FieldObject {
    u8 pad_00[0x4];
    FieldUnit *owner;
    u8 pad_08[0x32 - 0x8];
    u8 actorId;
    u8 pad_33[0x38 - 0x33];
    VecFx32 position;
    u8 pad_44[0x60 - 0x44];
    int progress;
    int duration;
    u8 pad_68[0x76 - 0x68];
    s8 motion;
    u8 mode;
    u8 pad_78[0xbe - 0x78];
    u8 unk_be_lo : 4;
    u8 state : 4;
    s8 nextMotion;
    u8 pad_c0[0xcc - 0xc0];
    VecFx32 velocity;
    VecFx32 lastDelta;
    s16 stuckFrames;
    u16 targetId : 14;
    u16 alongX : 1;
    u16 settle : 1;
} FieldObject;

extern const VecFx32 data_02053438;
extern void func_02036240(int actorId);
extern FieldObject *func_ov001_02087224(int group, int id);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern u16 FixedPointAtan2_020062bc(fx32 y, fx32 x);
extern void DivideVecFx32ByScalar_0204a700(VecFx32 *vec, int divisor);
extern void func_ov016_020a6cc4(FieldObject *object, VecFx32 *position);
extern void func_ov001_02086434(FieldObject *object, int mode);
extern void func_ov016_020a2b38(FieldObject *object, fx32 speed, u16 angle);
extern void SpawnSoundSlot_0204da8c(int bank, int id, VecFx32 *position, int flags);
extern void func_ov016_020a29a4(FieldObject *object);
extern void func_ov016_020a34fc(FieldObject *object, int arg);

int UpdateSlidingFieldObject_020a393c(FieldObject *object)
{
    func_02036240(object->actorId);
    switch (object->state) {
    case 1: {
        FieldObject *target = func_ov001_02087224(object->owner->group, object->targetId);
        VecFx32 delta;
        VecFx32 velocity = data_02053438;
        BOOL done;

        VEC_Subtract_01ff9e3c(&target->position, &object->position, &delta);
        if (object->alongX) {
            delta.x = delta.x * 6 / 10;
            velocity.x += delta.x;
            done = TRUE;
            if (delta.x != 0) {
                done = FALSE;
            }
            delta.x = 0;
        } else {
            delta.z = delta.z * 6 / 10;
            velocity.z += delta.z;
            done = TRUE;
            if (delta.z != 0) {
                done = FALSE;
            }
        }
        if (delta.x == object->lastDelta.x && delta.y == object->lastDelta.y && delta.z == object->lastDelta.z) {
            object->stuckFrames++;
            if (object->stuckFrames > 5) {
                done = TRUE;
            }
        } else {
            object->lastDelta = delta;
        }
        if (done) {
            if (object->settle) {
                VecFx32 middle;
                u16 angle = FixedPointAtan2_020062bc(delta.x, delta.z);

                VEC_Add_01ff9e0c(&object->position, &target->position, &middle);
                DivideVecFx32ByScalar_0204a700(&middle, 2);
                func_ov016_020a6cc4(object, &middle);
                func_ov001_02086434(object, 2);
                func_ov016_020a2b38(object, 0x1000, angle);
                SpawnSoundSlot_0204da8c(0, 0x3e, &object->position, 0);
                object->state = 2;
            } else {
                func_ov016_020a29a4(object);
            }
        }
        object->velocity = velocity;
        break;
    }
    case 2:
        object->velocity = data_02053438;
        if (object->progress >= object->duration / 2) {
            object->state = 3;
        }
        break;
    case 3:
        if (object->progress >= object->duration) {
            object->state = 0;
            object->velocity.y -= 0x333;
            if (object->mode == 12 || object->mode == 13) {
                object->nextMotion = 1;
            } else {
                object->nextMotion = 3;
            }
            object->motion = object->nextMotion;
        }
        break;
    }
    func_ov016_020a34fc(object, 1);
    return 0;
}
