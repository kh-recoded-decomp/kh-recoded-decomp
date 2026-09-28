#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

typedef struct {
    ScriptOperand operands[3];
} ScriptCommand;

extern int ScriptVm_ReadOperandInt_02025de4(void *context, ScriptOperand *operand);
extern void func_ov001_020688d4(u32 value, s32 hasValue, s32 flag);
extern int func_ov001_02068850(int value);
extern void func_02036828(u16 id, int delta);

int func_ov001_02065388(void *context, ScriptCommand *command)
{
    int value = ScriptVm_ReadOperandInt_02025de4(context, &command->operands[0]);
    int hasValue = ScriptVm_ReadOperandInt_02025de4(context, &command->operands[1]);
    int flag = ScriptVm_ReadOperandInt_02025de4(context, &command->operands[2]);

    func_ov001_020688d4(value, hasValue, flag);
    if (hasValue != 0)
    {
        value = func_ov001_02068850(value);
    }
    if (value >= 0)
    {
        func_02036828(value, -1);
    }
    return 1;
}
