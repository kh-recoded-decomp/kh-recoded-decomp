#include "nitro/types.h"

typedef struct {
    u32 type;
    u32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt_02025de4(void *vm, ScriptOperand *operand);
extern void func_ov035_020baf10(u32 count, s16 *values, u8 a, u8 b);

BOOL ScriptCmd_PlayValueSequence_020a06b4(void *vm, ScriptOperand *op) {
    u8 first = ScriptVm_ReadOperandInt_02025de4(vm, op++);
    u8 second = ScriptVm_ReadOperandInt_02025de4(vm, op++);
    int count = ScriptVm_ReadOperandInt_02025de4(vm, op++);
    s16 values[32];
    int i;

    for (i = 0; i < count; i++) {
        values[i] = ScriptVm_ReadOperandInt_02025de4(vm, op++);
    }
    func_ov035_020baf10(count, values, first, second);
    return TRUE;
}
