#include "nitro/types.h"

extern int ScriptVm_ReadOperandFx32_02025df8(void *vm, void *cmd);
extern s64 LongMultiply_02023d9c(s64 left, s64 right);
extern s64 LongDivide_02023ba4(s64 numerator, s64 denominator);
extern void func_ov043_020bca50(int angle);

BOOL ScriptCmd_SetAngleDegrees_0206598c(void *vm, void *cmd)
{
    int degrees = ScriptVm_ReadOperandFx32_02025df8(vm, cmd);

    func_ov043_020bca50(LongDivide_02023ba4(LongMultiply_02023d9c(degrees, 0x3244), 0xb4000));
    return TRUE;
}
