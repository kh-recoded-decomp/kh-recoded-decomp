#include "nitro/types.h"

typedef struct ScriptOperand {
    u8 data[8];
} ScriptOperand;

typedef struct TimerTarget {
    int value;
    int target;
} TimerTarget;

extern int ScriptVm_ReadOperandInt_02025de4(void *vm, void *operand);
extern int func_02025dac(void *vm, void *operand);
extern void func_ov001_02069370(int id, BOOL repeat, int unused, BOOL paused, BOOL silent, TimerTarget *target);

int ScriptOp_StartFieldTimer_02065178(void *vm, ScriptOperand *operands)
{
    int repeat = ScriptVm_ReadOperandInt_02025de4(vm, &operands[0]);
    int id = ScriptVm_ReadOperandInt_02025de4(vm, &operands[1]);
    TimerTarget target;
    int paused;
    int silent;

    target.value = ScriptVm_ReadOperandInt_02025de4(vm, &operands[2]);
    paused = ScriptVm_ReadOperandInt_02025de4(vm, &operands[3]);
    silent = ScriptVm_ReadOperandInt_02025de4(vm, &operands[4]);
    target.target = func_02025dac(vm, &operands[5]);
    func_ov001_02069370(id, repeat != 0, 0, paused != 0, silent != 0, &target);
    return 1;
}
