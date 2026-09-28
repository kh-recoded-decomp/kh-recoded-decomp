#include "nitro/types.h"

extern int ScriptVm_ReadOperandInt_02025de4(void *vm, void *operand);
extern void func_ov001_02064d1c(void);
extern void func_ov001_02064d44(void);

int ScriptCmd_ToggleSessionBit15_02065e74(void *vm, void *operand) {
    if (ScriptVm_ReadOperandInt_02025de4(vm, operand) != 0) {
        func_ov001_02064d1c();
    } else {
        func_ov001_02064d44();
    }
    return 1;
}
