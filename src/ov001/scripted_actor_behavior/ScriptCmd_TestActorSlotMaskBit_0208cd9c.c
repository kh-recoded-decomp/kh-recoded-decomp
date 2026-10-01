#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

typedef struct ActorNode {
    u8 pad_00[4];
    u16 flags;
} ActorNode;

typedef struct ScriptContext ScriptContext;

extern int ScriptVm_ReadOperandInt_02025de4(ScriptContext *context, ScriptOperand *operand);
extern int ScriptCmd_ReturnValue_02025960(ScriptContext *context, int value);
extern ActorNode *func_02036240(u16 actorId);
extern s16 func_020367f0(u16 actorId);
extern u32 BuildSlotMask_0202f034(void *slotList, int offset);

int ScriptCmd_TestActorSlotMaskBit_0208cd9c(ScriptContext *context, ScriptOperand *operands)
{
    int actorId;
    int bit;
    ActorNode *node;

    actorId = ScriptVm_ReadOperandInt_02025de4(context, operands);
    bit = ScriptVm_ReadOperandInt_02025de4(context, operands + 1);
    actorId = ScriptCmd_ReturnValue_02025960(context, actorId);
    node = func_02036240(actorId);
    if ((node->flags & 4) == 0) {
        if ((BuildSlotMask_0202f034(&node->flags, func_020367f0(actorId) << 1) & (1 << bit)) != 0) {
            return 1;
        }
    }
    return 0;
}
