#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt_02025de4(void *context, ScriptOperand *operand);
extern ScriptOperand *ScriptVm_ResolveOperand_02025d08(void *context, ScriptOperand *operand);
extern char *func_02025dac(void *context, ScriptOperand *operand);
extern char *strcpy_02021e60(char *dst, const char *src);

void Script_ResolveMotionNameAndId_0208cc38(void *context, ScriptOperand *operands, int actorId,
                                            int *outMotionId, char *outMotionName)
{
    ScriptOperand *first;
    ScriptOperand *second;

    ScriptVm_ReadOperandInt_02025de4(context, &operands[1]);
    ScriptVm_ReadOperandInt_02025de4(context, &operands[4]);
    first = ScriptVm_ResolveOperand_02025d08(context, &operands[2]);
    second = ScriptVm_ResolveOperand_02025d08(context, &operands[3]);
    if (first->type == 2) {
        strcpy_02021e60(outMotionName, func_02025dac(context, first));
        *outMotionId = ScriptVm_ReadOperandInt_02025de4(context, second);
        return;
    }
    if (second->type == 2) {
        strcpy_02021e60(outMotionName, func_02025dac(context, second));
        *outMotionId = ScriptVm_ReadOperandInt_02025de4(context, first);
        return;
    }
    *outMotionId = ScriptVm_ReadOperandInt_02025de4(context, second);
}
