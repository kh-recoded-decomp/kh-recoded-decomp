#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

typedef struct ActorNode {
    u8 pad_00[0x80];
    u16 heading;
} ActorNode;

typedef struct ChannelBuffer {
    u8 pad_00[0x44];
    s32 rotationX;
    s32 rotationY;
    u8 pad_4c[0x98 - 0x4c];
    s32 state;
} ChannelBuffer;

typedef struct CollisionEntry {
    u8 pad_00[0x8];
    VecFx32 position;
} CollisionEntry;

typedef struct ScriptContext ScriptContext;

extern const VecFx32 data_02053438;
extern ScriptOperand *ScriptVm_ResolveOperand_02025d08(ScriptContext *context, ScriptOperand *operand);
extern int ScriptVm_ReadOperandInt_02025de4(ScriptContext *context, ScriptOperand *operand);
extern fx32 ScriptVm_ReadOperandFx32_02025df8(ScriptContext *context, ScriptOperand *operand);
extern int ScriptCmd_ReturnValue_02025960(ScriptContext *context, int value);
extern void *func_02025dac(ScriptContext *context, ScriptOperand *operand);
extern CollisionEntry *FindWorldCollisionEntry_02036548(void *name);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
extern ChannelBuffer *ActorChannel_SelectBuffer_0208bd04(void);
extern void ActorChannel_SetStateFields_0208b870(u32 state, u32 value);
extern ActorNode *func_02036240(u16 actorId);
extern void func_ov001_0208babc(int actorId, int mode, fx32 speed, int roll, VecFx32 *position, VecFx32 *rotation);

int ScriptCmd_StartChannelTransform_0208d274(ScriptContext *context, ScriptOperand *args)
{
    VecFx32 position = data_02053438;
    VecFx32 rotation = data_02053438;
    int roll = 0;
    fx32 speed;
    int mode;
    int actorId;
    ScriptOperand *operand;
    int angle;
    CollisionEntry *entry;

    speed = ScriptVm_ReadOperandFx32_02025df8(context, &args[2]);
    mode = ScriptVm_ReadOperandInt_02025de4(context, &args[1]);
    actorId = 0;
    position.x = ScriptVm_ReadOperandFx32_02025df8(context, &args[3]);
    position.y = ScriptVm_ReadOperandFx32_02025df8(context, &args[4]);
    position.z = ScriptVm_ReadOperandFx32_02025df8(context, &args[5]);

    operand = ScriptVm_ResolveOperand_02025d08(context, &args[0]);
    switch (operand->type) {
    case 1:
        if (operand->value != -1) {
            actorId = ScriptCmd_ReturnValue_02025960(context, operand->value);
        } else {
            actorId = -1;
        }
        break;
    case 2:
        entry = FindWorldCollisionEntry_02036548(func_02025dac(context, operand));
        actorId = -1;
        VEC_Add_01ff9e0c(&position, &entry->position, &position);
        break;
    }

    if (ActorChannel_SelectBuffer_0208bd04()->state == 8) {
        rotation.x = func_02036240(actorId)->heading;
        ActorChannel_SetStateFields_0208b870(3, 0);
    } else {
        operand = ScriptVm_ResolveOperand_02025d08(context, &args[6]);
        if (operand->type != 0) {
            rotation.x = ScriptVm_ReadOperandInt_02025de4(context, operand) * 0xb6;
        } else {
            rotation.x = ActorChannel_SelectBuffer_0208bd04()->rotationX;
        }
    }

    operand = ScriptVm_ResolveOperand_02025d08(context, &args[7]);
    if (operand->type == 1) {
        angle = ScriptVm_ReadOperandInt_02025de4(context, operand);
        if (angle > 360) {
            angle = -(angle - 360);
        }
        rotation.y = angle * 0xb6;
    } else {
        rotation.y = ActorChannel_SelectBuffer_0208bd04()->rotationY;
    }

    operand = ScriptVm_ResolveOperand_02025d08(context, &args[8]);
    if (operand->type == 1) {
        rotation.z = ScriptVm_ReadOperandInt_02025de4(context, operand) * 0xb6;
    }

    operand = ScriptVm_ResolveOperand_02025d08(context, &args[9]);
    if (operand->type == 1) {
        roll = ScriptVm_ReadOperandInt_02025de4(context, operand) * 0xb6;
    }

    func_ov001_0208babc(actorId, mode, speed, roll, &position, &rotation);
    return 1;
}
