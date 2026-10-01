#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

typedef struct ActorNode {
    u32 flags;
    u16 dirtyFlags;
    u8 pad_06[0x7a];
    u16 rotationY;
} ActorNode;

extern int ScriptVm_ReadOperandInt_02025de4(void *context, ScriptOperand *operand);
extern s32 ScriptCmd_ReturnValue_02025960(void *context, s32 value);
extern int ScriptVm_ReadOperandFx32_02025df8(void *context, ScriptOperand *operand);
extern char *func_02025dac(void *context, ScriptOperand *operand);
extern void func_020359f8(u16 index, char *name, VecFx32 *position);
extern ActorNode *func_02036240(u16 index);
extern void ActorSlot_SetFlag8ByIndex_02036120(u16 index, BOOL enable);
extern void ScriptActor_DispatchAndMarkFlag_0208c2c4(void *context, char *name, VecFx32 *position, u32 actorId);

int ScriptCmd_PlaceActor_0208c7e8(void *context, ScriptOperand *operands)
{
    u32 actorId;
    VecFx32 position;
    char *name;
    u16 angle;
    ActorNode *actor;

    actorId = ScriptCmd_ReturnValue_02025960(context, ScriptVm_ReadOperandInt_02025de4(context, operands));
    position.x = ScriptVm_ReadOperandFx32_02025df8(context, operands + 2);
    position.y = ScriptVm_ReadOperandFx32_02025df8(context, operands + 3);
    position.z = ScriptVm_ReadOperandFx32_02025df8(context, operands + 4);
    if (operands[1].type == 0) {
        name = NULL;
        angle = (ScriptVm_ReadOperandInt_02025de4(context, operands + 5) << 16) / 360;
        func_020359f8(actorId, NULL, &position);
        actor = func_02036240(actorId);
        if (!(actor->flags & 0x20)) {
            actor->rotationY = angle;
            actor->dirtyFlags |= 0x20;
        }
    } else {
        name = func_02025dac(context, operands + 1);
        func_020359f8(actorId, name, &position);
    }
    ActorSlot_SetFlag8ByIndex_02036120(actorId, TRUE);
    ScriptActor_DispatchAndMarkFlag_0208c2c4(context, name, &position, actorId);
    return 1;
}
