#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

typedef struct {
    ScriptOperand operands[2];
} ScriptCommand;

extern int ScriptVm_ReadOperandInt(void *context, ScriptOperand *operand);
extern fx32 ScriptVm_ReadOperandFx32(void *context, ScriptOperand *operand);
extern u32 GetCurrentRecordPosition(void);
extern void SetFields30And34(u32 a, u32 b);

int func_ov001_0206595c(void *context, ScriptCommand *command)
{
    int useCurrent = ScriptVm_ReadOperandInt(context, &command->operands[0]);
    fx32 amount = ScriptVm_ReadOperandFx32(context, &command->operands[1]);

    SetFields30And34(useCurrent != 0 ? GetCurrentRecordPosition() : 0, amount);
    return 1;
}
