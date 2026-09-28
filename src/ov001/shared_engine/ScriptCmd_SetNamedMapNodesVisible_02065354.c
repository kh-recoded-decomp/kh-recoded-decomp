#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern const char *func_02025dac(void *context, ScriptOperand *operand);
extern int ScriptVm_ReadOperandInt_02025de4(void *context, ScriptOperand *operand);
extern int Strlen_02021e44(const char *str);
extern void func_ov001_020680fc(const char *name, int nameLength, BOOL visible);

int ScriptCmd_SetNamedMapNodesVisible_02065354(void *context, ScriptOperand *operands)
{
    const char *name;
    int visible;

    name = func_02025dac(context, operands);
    visible = ScriptVm_ReadOperandInt_02025de4(context, operands + 1);
    func_ov001_020680fc(name, Strlen_02021e44(name), visible != 0);
    return 1;
}
