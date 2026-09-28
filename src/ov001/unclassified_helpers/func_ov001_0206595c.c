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

extern int ScriptVm_ReadOperandInt_02025de4(void *context, ScriptOperand *operand);
extern fx32 ScriptVm_ReadOperandFx32_02025df8(void *context, ScriptOperand *operand);
extern u32 func_ov031_020bc720(void);
extern void SetFields30And34_020bc008(u32 a, u32 b);

int func_ov001_0206595c(void *context, ScriptCommand *command)
{
    int useCurrent = ScriptVm_ReadOperandInt_02025de4(context, &command->operands[0]);
    fx32 amount = ScriptVm_ReadOperandFx32_02025df8(context, &command->operands[1]);

    SetFields30And34_020bc008(useCurrent != 0 ? func_ov031_020bc720() : 0, amount);
    return 1;
}
