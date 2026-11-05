#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

typedef struct {
    ScriptOperand operands[3];
} ScriptCommand;

extern int ScriptVm_ReadOperandInt(void *context, ScriptOperand *operand);
extern void ReleaseOrDisableStageEvent(u32 value, s32 hasValue, s32 flag);
extern int LookupStagePairValue(int value);
extern void ActorSlot_AddPriorityByIndex(u16 id, int delta);

int ScriptCmd_ReleaseOrDisableStageEvent(void *context, ScriptCommand *command)
{
    int value = ScriptVm_ReadOperandInt(context, &command->operands[0]);
    int hasValue = ScriptVm_ReadOperandInt(context, &command->operands[1]);
    int flag = ScriptVm_ReadOperandInt(context, &command->operands[2]);

    ReleaseOrDisableStageEvent(value, hasValue, flag);
    if (hasValue != 0)
    {
        value = LookupStagePairValue(value);
    }
    if (value >= 0)
    {
        ActorSlot_AddPriorityByIndex(value, -1);
    }
    return 1;
}
