#include "nitro/types.h"

typedef struct ScriptOperand {
    u32 type;
    u32 value;
} ScriptOperand;

extern s32 ScriptVm_ConsumeOperandInt_020a1de0(void *vm, ScriptOperand **cursor);
extern int func_ov001_02087204(void);
extern unsigned int func_ov001_02087214(int index);
extern void SetGroupMembersFlag21_020a6cfc(unsigned int group, BOOL enable);

BOOL ScriptCmd_SetGroupFlag21_020a21e8(void *vm, ScriptOperand *operands)
{
    ScriptOperand *cursor = operands;
    int index;
    BOOL enable;

    index = ScriptVm_ConsumeOperandInt_020a1de0(vm, &cursor);
    enable = ScriptVm_ConsumeOperandInt_020a1de0(vm, &cursor) != 0;
    if (func_ov001_02087204() > 0) {
        SetGroupMembersFlag21_020a6cfc(func_ov001_02087214(index), enable);
    }
    return TRUE;
}
