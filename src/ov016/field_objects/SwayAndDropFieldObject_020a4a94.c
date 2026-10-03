#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CollisionBox {
    VecFx32 max;
    VecFx32 min;
} CollisionBox;

typedef struct FieldActor {
    u8 pad_00[0x134];
    CollisionBox baseBox;
    int kind;
    VecFx32 velocity;
    CollisionBox sweptBox;
} FieldActor;

typedef struct FieldObject {
    u8 pad_00[0x32];
    u8 actorId;
    u8 pad_33[0x5];
    VecFx32 position;
    u8 pad_44[0x2C];
    u16 unk_70_lo : 5;
    u16 landed : 1;
    u16 unk_70_mid : 3;
    u16 phase : 3;
    u16 unk_70_hi : 4;
    u8 pad_72[0x42];
    int waitFrames;
    fx32 floorY;
    u8 pad_BC[0x4];
    u32 flags;
    u8 pad_C4[0x2C];
    fx32 baseX;
    fx32 timer;
} FieldObject;

extern const s16 data_0205356c[];
extern FieldActor *func_02036240(int actorId);
extern fx32 FX_Div_01ff9c84(fx32 numerator, fx32 denominator);
extern int FixedPointMultiply12(int left, int right);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void OffsetBoxByDelta_0203ac70(CollisionBox *src, CollisionBox *dst, VecFx32 *delta);
extern void Obj_SetPosition_0203569c(FieldActor *actor, VecFx32 *position);
extern void func_ov016_020a4a64(FieldObject *object);
extern void func_ov016_020a2558(FieldObject *object);

void SwayAndDropFieldObject_020a4a94(FieldObject *object)
{
    if (!(object->flags & 0x200)) {
        FieldActor *actor = func_02036240(object->actorId);
        VecFx32 delta = {0, 0, 0};
        VecFx32 target = object->position;

        switch (object->phase) {
        case 0:
            return;
        case 1:
            object->timer += 0x1000;
            if (object->timer < object->waitFrames * 30) {
                return;
            }
            object->phase = 2;
            object->timer = 0;
            return;
        case 2:
            object->timer += 0x1000;
            if (object->timer >= 0x14000) {
                target.x = object->baseX;
                object->phase = 3;
            } else {
                int angle = FixedPointMultiply12(FX_Div_01ff9c84(object->timer, 0x14000), 0x3244);
                angle = (((s64)(angle * 5) << 16) / 0x6488) & 0xffff;
                angle >>= 4;
                target.x = object->baseX + FixedPointMultiply12(0x19A, data_0205356c[angle]);
            }
            break;
        case 3:
            target.y -= 0x666;
            if (target.y < object->floorY) {
                object->phase = 4;
                target.y = object->floorY;
                func_ov016_020a4a64(object);
            }
            break;
        case 4:
            object->flags |= 0x200;
            object->landed = 1;
            break;
        }
        VEC_Subtract_01ff9e3c(&target, &object->position, &delta);
        actor->velocity = delta;
        OffsetBoxByDelta_0203ac70(&actor->baseBox, &actor->sweptBox, &actor->velocity);
        Obj_SetPosition_0203569c(actor, &target);
        VEC_Add_01ff9e0c(&object->position, &actor->velocity, &object->position);
        func_ov016_020a2558(object);
    }
}
