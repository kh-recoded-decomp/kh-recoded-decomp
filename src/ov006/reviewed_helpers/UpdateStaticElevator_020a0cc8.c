#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct {
    u8 pad_00[0x8c];
    s16 waitTime;
    u8 pad_8E[6];
    s8 riders;
} ElevatorClassData;

typedef struct {
    u8 pad_00[8];
    ElevatorClassData *classData;
    u8 pad_0C[0x2c];
    u8 actorSlot;
    u8 pad_39[0x15];
    u16 flags;
    u8 pad_50[3];
    s8 state;
    u8 pad_54[0x14];
    fx32 frame;
    s8 cooldown;
    u8 pad_6D;
    s8 load;
    s8 count;
    s16 timer;
} ElevatorObject;

typedef struct {
    u8 pad_00[4];
    u8 anim[4];
} ActorNode;

extern const s8 data_ov006_020a1834[];

extern ActorNode *func_02036240(u16 actorId);
extern BOOL func_ov001_020645c8(int bitId);
extern BOOL ActorSlot_IsFlag8SetByIndex_02036164(int index);
extern void ActorSlot_SetFlag8ByIndex_02036120(int index, BOOL enable);
extern BOOL AdvanceAnimFrame_02080a38(void *anim, fx32 step, BOOL loop, fx32 length, fx32 *frame);
extern BOOL func_ov001_02063838(void);
extern void func_ov006_020a06e8(ElevatorObject *object);
extern u16 FieldObject_GetSavedValue_0207f9a8(ElevatorObject *object);
extern void FieldObject_SetSavedValue_0207f9c8(ElevatorObject *object, u16 value);

int UpdateStaticElevator_020a0cc8(ElevatorObject *object) {
    ElevatorClassData *data;
    ActorNode *actor;
    BOOL done;

    data = object->classData;
    done = FALSE;
    actor = func_02036240(object->actorSlot);

    if (func_ov001_020645c8(0x3717)) {
        return done;
    }
    if (object->cooldown > 0) {
        object->cooldown--;
    }
    if (ActorSlot_IsFlag8SetByIndex_02036164(object->actorSlot)) {
        fx32 length = data_ov006_020a1834[object->state] << 12;

        done = length <= object->frame + FX32_ONE;
        AdvanceAnimFrame_02080a38(actor->anim, 0x1000, FALSE, length, &object->frame);
    } else if (data->riders < 12 && object->timer > 0) {
        if (!func_ov001_02063838() && --object->timer == 0) {
            object->state = 3;
            func_ov006_020a06e8(object);
            object->load = 6;
            data->riders -= object->load;
            ActorSlot_SetFlag8ByIndex_02036120(object->actorSlot, TRUE);
            FieldObject_SetSavedValue_0207f9c8(object, FieldObject_GetSavedValue_0207f9a8(object) & ~4);
        }
        return 0;
    }
    switch (object->state) {
    case 0:
        break;
    case 1:
        if (done) {
            if (--object->count == 0) {
                if (object->load == 0) {
                    object->state = 2;
                } else {
                    object->state = 0;
                }
            }
            func_ov006_020a06e8(object);
        }
        break;
    case 2:
        if (done) {
            object->timer = data->waitTime;
            ActorSlot_SetFlag8ByIndex_02036120(object->actorSlot, FALSE);
        }
        break;
    case 3:
        if (done) {
            object->state = 0;
            func_ov006_020a06e8(object);
            object->flags |= 0x10;
        }
        break;
    }
    return 0;
}



